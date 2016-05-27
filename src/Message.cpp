#include <stdexcept>
#include <sstream>

#include "Message.h"
#include "Utils.h"

/**
 * @brief Creates an empty message
 */
Message::Message() : idDevice(0), sizeBuffer(0), sizeData(0), opCode(0), crc(0)
{
    listBuffer = reinterpret_cast<Buffer *>(new char[0 * sizeof(Buffer)]);
    LOG(1, "Message() \n");
}

/**
 * @brief Creates a message with list of buffers with opcode and sizeLeft
 * @param size of the message
 * @param code operation code
 */
Message::Message(int id, int sizeBuff, uint16_t size, uint8_t code) :
    idDevice(id), sizeBuffer(sizeBuff), sizeData(size), opCode(code), crc(0)
{
    int n = this->NbBuffers();

    listBuffer = reinterpret_cast<Buffer *>(new char[n * sizeof(Buffer)]);
    
    for (int i = 0; i < n; i++)
        new(&listBuffer[i]) Buffer(sizeBuff);

    listBuffer[0].setHeader(1);
    
    for (int i = 0; i < n; i++) {
        listBuffer[i].setID(id);
        listBuffer[i].setOpCode(code);
        listBuffer[i].setSizeLeft(size - i * (SIZE_BUFFER - DATA_INDEX - SIZE_CRC));
        }
    LOG(1, "Message(idDevice, sizeBuffer, sizeMessage, opCode)");
}

/**
 * @brief Constructor by copy
 */
Message::Message(const Message& M) {
    sizeBuffer= M.getSizeBuffer();
    sizeData = M.getSizeData();
    opCode = M.getOpCode();
    crc = M.getCrc();
    idDevice = M.getID();
    int n = M.NbBuffers();
    
    listBuffer = reinterpret_cast<Buffer *>(new char[n*sizeof(Buffer)]);
    
    for (int i = 0; i<n; i++)
        listBuffer[i] = M.getBuffer()[i];
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
    if ((sizeData % (sizeBuffer - DATA_INDEX - SIZE_CRC)) == 0)
        return sizeData/(sizeBuffer - DATA_INDEX - SIZE_CRC);
    else
        return sizeData/(sizeBuffer - DATA_INDEX - SIZE_CRC) + 1;
}


/**
 * @brief Fills the buffers with the data
 * @param data to encode
 */
void Message::encode(uint8_t *dataToEncode)
{
    int j = 0; int k= 0; int n = NbBuffers();
    uint8_t *entireBuffer = new uint8_t [this->sizeBuffer];
    uint8_t *tab = new uint8_t[2];
    
    for (int i = 0; i < n; i ++) {
        while (j < (sizeBuffer - DATA_INDEX - SIZE_CRC)) {
            if (k < sizeData)
                listBuffer[i].setData(j, dataToEncode[k]);
            else
                listBuffer[i].setData(j,0);
            j++; k++;
        }
        j = 0;
        entireBuffer[0] = listBuffer[i].getHeader();
        entireBuffer[1] = listBuffer[i].getID();
        entireBuffer[2] = listBuffer[i].getOpCode();
        convert16to8(listBuffer[i].getSizeBuffer(), tab);
        entireBuffer[3] = tab[0];
        entireBuffer[4] = tab[1];
        for (int ii = DATA_INDEX; ii < (this->sizeBuffer - SIZE_CRC); ii++)
            entireBuffer[ii] = listBuffer[i].getData()[ii-DATA_INDEX];

        uint16_t crcComputed = computeCRC(entireBuffer,
                                          sizeof(uint8_t)*(sizeBuffer - SIZE_CRC));
        listBuffer[i].setCrc(crcComputed);
    }
    delete [] entireBuffer;
    delete [] tab;
}

/**
 * @brief Finds a buffer based on its index
 * @param index
 * @return buffer desired
 */
Buffer* Message::getBuffer() const
{
    return (this->listBuffer); //Can throw out_of_range exception
}

/**
 * @brief Finds a buffer based on its opCode and sizeLeft
 * @param opCode 
 * @param sizeLeft
 * @return buffer desired
 */

Buffer Message::getBuffer(uint8_t opCode, uint16_t sizeLeft) const{
    for (int i = 0; i < NbBuffers(); i++) {
        if (listBuffer[i].getOpCode() == opCode && listBuffer[i].getSizeLeft() == sizeLeft)
            return listBuffer[i];
        else
            throw std::out_of_range("Buffer not found\n");                
    }
    return Buffer();
}

/**
 * @brief Returns the size of the buffers created
 */
int Message::getSizeBuffer() const {
    return this->sizeBuffer;
}

/**
 * @brief Returns the size of the data
 */
uint16_t Message::getSizeData() const {
    return this->sizeData;
}

/**
 * @brief Returns the opCode
 */
uint8_t Message::getOpCode() const {
    return this->opCode;
}

/**
 * @brief Returns the crc
 */
uint16_t Message::getCrc() const {
    return this->crc;
}

/**
 * @brief Returns the id of the device
 */
int Message::getID() const {
    return this->idDevice;
}

/*
 * @brief Prints the message
 * @return string
 */
std::string Message::toStringDebug()
{
    std::ostringstream convert;
    convert << "Message :" << std::endl;
    int n = NbBuffers();
    for (int i = 0; i < n; i++)
        convert << getBuffer()[i].toStringDebug(i);

    return convert.str();
}
