#include <stdexcept>
#include <sstream>
#include <string.h>

#include "Message.h"
#include "Utils.h"

    /*!
     * \brief Constructor
     *
     * Creates a message
     *
     * \param id device's ID
     * \param sizeBuff the buffers' size
     * \param size the size of the data to encode
     * \param code the message's operation code
     */    
Message::Message(uint8_t id, int sizeBuff, uint16_t size, uint8_t code) :
    idDevice(id), sizeBuffer(sizeBuff), sizeData(size), opCode(code)
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

    /*!
     * \brief Constructor by copie
     *
     * Creates a message by copying another one
     *
     * \param M the other message which will be unchanged
     */        
Message::Message(const Message& M)
{
    sizeBuffer= M.getSizeBuffer();
    sizeData = M.getSizeData();
    opCode = M.getOpCode();
    idDevice = M.getID();
    int n = M.NbBuffers();
    
    listBuffer = reinterpret_cast<Buffer *>(new char[n*sizeof(Buffer)]);
    
    for (int i = 0; i<n; i++)
        listBuffer[i] = M.getListBuffer()[i];
    LOG(1, "Message(const &message)");
}

/*!
 * \brief Destructor
 */
Message::~Message()
{
    int n = this->NbBuffers();

    for (int i = 0; i < n; i++)
        listBuffer[i].Buffer::~Buffer();

    delete[] reinterpret_cast<char *>(listBuffer);
    LOG(1, "~Message()");
}

    /*!
     * \fn int NbBuffers() const
     * \brief Calculates the number of buffers necessary to encode a message
     * \return the number of buffers needed
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

    /*!
     * \fn void encode(uint8_t *dataToEncode)
     * \brief Fills the buffers with the data and calculates and sets the crc
     * 
     *  Fills the buffers with the data
     * if size(dataToEncode) > sizeData,
     * only the first sizeData values of dataToEncode will be encoded
     *
     * \param dataToEncode 
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

    /*!
     * \fn Buffer *getListBuffer() const
     * \brief Accessor to the list of buffers
     * \return list of buffers
     */
Buffer* Message::getListBuffer() const
{
    return (this->listBuffer); //Can throw out_of_range exception
}

    /*!
     * \fn Buffer *getBuffer(uint8_t opCode, uint16_t sizeLeft) const
     * \brief Accessor to one specific buffer
     * \param opCode operation code
     * \param sizeLeft the size left of the buffer
     * \return a buffer
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

    /*!
     * \fn int getSizeBuffer() const
     * \brief Gets the buffers' size
     * \return the size
     */
int Message::getSizeBuffer() const
{
    return this->sizeBuffer;
}

    /*!
     * \fn uint16_t getSizeData() const
     * \brief Gets the data's size
     * \return the size 
     */
uint16_t Message::getSizeData() const
{
    return this->sizeData;
}

    /*!
     * \fn uint8_t getOpCode() const
     * \brief Gets the operation code
     * \return the opCode
     */
uint8_t Message::getOpCode() const
{
    return this->opCode;
}

    /*!
     * \fn uint8_t getID() const
     * \brief Gets the device's ID
     * \return ID
     */
uint8_t Message::getID() const
{
    return this->idDevice;
}

    /*!
     * \fn std::string toStringDebug() const
     * \brief Prints for debug purposes
     * \return string
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

