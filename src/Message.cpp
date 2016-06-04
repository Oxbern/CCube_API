#include <stdexcept>
#include <sstream>
#include <string.h>

#include "Message.h"
#include "Utils.h"



/**
 * @brief Creates a message with list of buffers with opcode and sizeLeft
 * @param size of the message
 * @param code operation code
 */
Message::Message(uint8_t id, int sizeBuff, uint16_t size, uint8_t code) :
    idDevice(id), sizeBuffer(sizeBuff), sizeData(size), opCode(code), crc(0)
{
    int nbBuff = this->NbBuffers();

    listBuffer = reinterpret_cast<Buffer *>(new char[nbBuff * sizeof(Buffer)]);

    for (int i = 0; i < nbBuff; i++)
        new(&listBuffer[i]) Buffer(sizeBuff);

    //First buffer first bit should be 1 and others 0
    listBuffer[0].setHeader(1);


    for (int i = 0; i < nbBuff; i++) {
        listBuffer[i].setID(id);
        listBuffer[i].setOpCode(code);
        listBuffer[i].setSizeLeft(size - i * (SIZE_BUFFER - DATA_INDEX - SIZE_CRC));
    }
    LOG(1, "Message(id, sizeBuff, size, code)");
    LOG(2, "Message(ID = " + std::to_string(id)
           + ", OPCODE = " + std::to_string(code)
           + ", SIZEBUFF = " + std::to_string(sizeBuff)
           + ", SIZEDATA = " + std::to_string(size)  + ")");
}

/**
 * @brief Constructor by copy
 */
Message::Message(const Message& M)
{
    sizeBuffer= M.getSizeBuffer();
    sizeData = M.getSizeData();
    opCode = M.getOpCode();
    crc = M.getCrc();
    idDevice = M.getID();
    int n = M.NbBuffers();
    
    listBuffer = reinterpret_cast<Buffer *>(new char[n*sizeof(Buffer)]);
    
    for (int i = 0; i<n; i++)
        listBuffer[i] = M.getListBuffer()[i];
    LOG(1, "Message(const &message)");
}

/**
 * @brief Destructor
 */
Message::~Message()
{
    int n = this->NbBuffers();

    for (int i = 0; i < n; i++)
        listBuffer[i].Buffer::~Buffer();

    delete[] reinterpret_cast<char *>(listBuffer);
    LOG(1, "~Message()");
}

/**
 * @brief Calculates the number of buffers necessary to create a message
 * @return number of buffers needed
 */
int Message::NbBuffers() const
{
    if (sizeData == 0)
        return 1;    
    else if ((sizeData % (sizeBuffer - DATA_INDEX - SIZE_CRC)) == 0)
        return sizeData/(sizeBuffer - DATA_INDEX - SIZE_CRC);
    else
        return sizeData/(sizeBuffer - DATA_INDEX - SIZE_CRC) + 1;
}


/**
 * @brief Fills the buffers with the data
 *        if size(dataToEncode) > sizeData, 
 *        only the first sizeData values of dataToEncode will be encoded           
 * @param data to encode
 */
void Message::encode(uint8_t *dataToEncode)
{
    LOG(2, "Message encoding :");

    //Header, DeviceID, Opcode already set in the constructor
    int j = 0; int k= 0; int n = NbBuffers();

    //Fills the buffers with the data
    for (int i = 0; i < n; i ++) {
        while (j < (listBuffer[i].getDataSize())) {
            if (k < sizeData) {
                listBuffer[i].setData(j, dataToEncode[k]);
            }
            else {
                listBuffer[i].setData(j,0);
            }
            j++; k++;
        }
        j = 0;

        //Sets CRC computed on the entire buffer
        listBuffer[i].crcEncoding();
        
        LOG(2, "[ENCODING] Buffer N° " + std::to_string(i)
            + ": DATA = "
            + uint8ArrayToString(listBuffer[i].getData(), listBuffer[i].getDataSize())
            + " | CRC = " + std::to_string(listBuffer[i].getCrc()));
    }
}

/**
 * @brief todo
 * @return xx
 */
Buffer* Message::getListBuffer() const
{
    return (this->listBuffer); //Can throw out_of_range exception
}

/**
 * @brief Finds a buffer based on its opCode and sizeLeft
 * @param opCode 
 * @param sizeLeft
 * @return buffer desired
 */

Buffer* Message::getBuffer(uint8_t opCode, uint16_t sizeLeft) const
{
    LOG(2, "getBuffer Method : ");
    LOG(2, "Buffer searched :  OPCODE = " + std::to_string(opCode)
           + " | SIZELEFT = " + std::to_string(sizeLeft));

    /* Research a buffer with the same opCode and the same sizeLeft
       in the message */
    for (int i = 0; i < NbBuffers(); i++) {
        if (listBuffer[i].getOpCode() == opCode
            && listBuffer[i].getSizeLeft() == sizeLeft) {
            LOG(1, "Buffer found \n");
            return &listBuffer[i];
        }
    }
    LOG(2, "Buffer not found \n");
    return NULL;
}

/**
 * @brief Returns the size of the buffers created
 */
int Message::getSizeBuffer() const
{
    return this->sizeBuffer;
}

/**
 * @brief Returns the size of the data
 */
uint16_t Message::getSizeData() const
{
    return this->sizeData;
}

/**
 * @brief Returns the opCode
 */
uint8_t Message::getOpCode() const
{
    return this->opCode;
}

/**
 * @brief Returns the crc
 */
uint16_t Message::getCrc() const
{
    return this->crc;
}

/**
 * @brief Returns the id of the device
 */
uint8_t Message::getID() const
{
    return this->idDevice;
}

/*
 * @brief Prints the message
 * @return string
 */
std::string Message::toStringDebug() const
{
    std::ostringstream convert;
    convert << "---------- Message (DEBUG) : ----------" << std::endl;
    int n = NbBuffers();
    for (int i = 0; i < n; i++)
        convert << getListBuffer()[i].toStringDebug(i);
    convert << "---------- End Message (DEBUG) : ----------" << std::endl;
    return convert.str();
}

