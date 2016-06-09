#include <sstream>
#include <string.h>

#include "Buffer.h"
#include "Utils.h"
#include "Debug.h"

/*! 
 * \brief Constructor
 *
 * Creates a buffer
 *
 */
Buffer::Buffer() :
    header(0), idDevice(0), sizeBuffer(0), opCode(0), sizeLeft(0), crc(0)
{
    data = new uint8_t[0]();
    LOG(1, "Buffer()");
}

/*! 
 * \brief Constructor
 *
 * Creates a buffer by setting its size
 *
 * \param sizeBuff the buffer's size desired
 */    
Buffer::Buffer(int sizeBuff) :
    header(0), idDevice(0), sizeBuffer(sizeBuff), opCode(0), sizeLeft(0), crc(0)
{
    data = new uint8_t[sizeBuff-DATA_INDEX - SIZE_CRC]();
    LOG(1, "Buffer(sizeBuffer)");
}


/**
 * @brief Constructor by copy
 * 
 * \param B
 */
Buffer::Buffer(const Buffer& B)
{
    header = B.getHeader();
    idDevice = B.getID();
    sizeBuffer = B.getSizeBuffer();
    opCode = B.getOpCode();
    sizeLeft = B.getSizeLeft();
    crc = B.getCrc();
    data = new uint8_t[getDataSize()];

    for (int i = 0; i < getDataSize(); i++)
        data[i] = B.getData()[i];

    LOG(1, "Buffer(const &Buffer) Constructor by copy");

    LOG(2, "Detail of buffer constructed by copy : " + this->toStringDebug(-1));
}

/*!
 * \brief Destructor
 *
 */    
Buffer::~Buffer()
{
    if (data != NULL) {
        delete[] data;
    }
    data = NULL;
    LOG(1, "~Buffer()");
}

/*!
 * \brief Sets the header of a buffer
 *
 * Setter
 *
 * \param head header (1 or 0)
 */        
void Buffer::setHeader(uint8_t head)
{
    this->header = head;
}

/*!
 * \brief Sets the device ID of a buffer
 *
 * Setter
 *
 * \param id device's ID
 */
void Buffer::setID(uint8_t id)
{
    this->idDevice = id;
}

/*!
 * \brief Sets the operation code of a buffer
 *
 * Setter
 *
 * \param code operation code
 */        
void Buffer::setOpCode(uint8_t code)
{
    this->opCode = code;
}

/*!
 * \brief Sets the SizeLeft of a buffer
 *
 * Setter
 *
 * \param size the size left in a message
 */
void Buffer::setSizeLeft(uint16_t size)
{
    this->sizeLeft = size;
}

/*!
 * \brief Sets the crc of a buffer
 *
 * Setter
 *
 * \param crcCheck the crc
 */    
void Buffer::setCrc(uint16_t crcCheck)
{
    this->crc = crcCheck;
}

/*!
 * \brief Sets data[index]
 *
 * Setter
 *
 * \param index the position in data
 * \param dataIndex the value to set
 */
void Buffer::setData(int index, uint8_t dataIndex)
{
    this->data[index] = dataIndex;
}

/*!
 * \brief Returns the header
 *
 * Getter
 *
 * \return the header of a buffer (1 or 0)
 */    
uint8_t Buffer::getHeader() const
{
    return this->header;
}

/*!
 * \brief Returns the operation code
 *
 * Getter
 *
 * \return the operation code of a buffer
 */      
uint8_t Buffer::getOpCode() const
{
    return this->opCode;
}

/*!
 * \brief Returns the left size of a message
 *
 * Getter
 *
 * \return the size left of a buffer
 */
uint16_t Buffer::getSizeLeft() const
{
    return this->sizeLeft;
}

/*!
 * \brief Returns the data contained in a buffer
 *
 * Getter
 *
 * \return the data contained in a buffer
 */    
uint8_t *Buffer::getData() const
{
    return this->data;
}

/*!
 * \brief Returns the crc
 *
 * Getter
 *
 * \return the crc of a buffer
 */    
uint16_t Buffer::getCrc() const
{
    return this->crc;
}

/*!
 * \brief Returns the size of the buffer
 *
 * Getter
 *
 * \return the size of the entire buffer
 */        
int Buffer::getSizeBuffer() const
{
    return this->sizeBuffer;
}

/*!
 * \brief Returns the ID of the device which this buffer is from or for
 *
 * Getter
 *
 * \return the device ID
 */            
uint8_t Buffer::getID() const
{
    return this->idDevice;
}

/*!
 * \brief Comparaison operator == between two buffers
 *
 * \param b the buffer to compare with
 *
 * \return the result of the comparaison
 */                
bool Buffer::operator==(Buffer b)
{
    bool ret = (this->header == b.header &&
                this->opCode == b.opCode &&
                this->sizeLeft == b.sizeLeft &&
                this->crc == b.crc &&
                this->sizeBuffer == b.sizeBuffer);
    if (ret) {
        for (int i = 0; i < (this->sizeBuffer - DATA_INDEX - SIZE_CRC); i ++) {
            ret = (this->data[i] == b.getData()[i]);
        }
    }
    return ret;
}

/*!
 * \brief Converts a buffer into an array
 *
 * 
 *
 * \param buffLinear the filled array
 */    
void Buffer::toArray(uint8_t* buffLinear)
{
    if (buffLinear != NULL) {
        buffLinear[HEADER_INDEX] = header;
        buffLinear[ID_INDEX] = idDevice;
        buffLinear[OPCODE_INDEX] = opCode;
        uint8_t tab[2];
        convert16to8(sizeLeft, tab);
        buffLinear[SIZE_INDEX] = tab[0];
        buffLinear[SIZE_INDEX + 1] = tab[1];

        //Convert data
        for (int i = 0; i < getDataSize(); i++)
            buffLinear[DATA_INDEX + i] = data[i];

        //split crc into two uint8_t
        int indexCrc = crcIndex(sizeBuffer);
        convert16to8(crc, tab);
        memcpy(&buffLinear[indexCrc], tab, 2);
        LOG(1, "Buffer.toArray() : "
               + uint8ArrayToString(buffLinear, SIZE_BUFFER));
    }
}

/*!
 * \brief Prints a buffer 
 *
 * Method to string
 *
 */        
std::string Buffer::toString()
{
    std::ostringstream convert;
    uint8_t tab[2];
    convert << (int) header;
    convert << (int) idDevice;
    convert << (int) opCode;

    //split sizeLeft into two uint8_t
    convert16to8(sizeLeft, tab);
    convert << (int) tab[0];
    convert << (int) tab[1];

    //Convert data
    for (int i = 0; i < getDataSize(); i++)
        convert << (int)data[i];

    //split crc into two uint8_t
    convert16to8(crc, tab);
    convert << (int) tab[0];
    convert << (int) tab[1];

    return convert.str();
}


/*!
 * \brief Prints a buffer for debug purposes
 *
 * Method to string
 *
 * \param indexInMess the buffer index in a message
 */        
std::string Buffer::toStringDebug(int indexInMess)
{
    std::ostringstream convert;
    uint8_t tab[2];
    convert << "Buffer ";
    if (indexInMess >= 0)
        convert << "n° " << indexInMess;
    convert << " : | ";
    convert << (int) header;
    convert << " | " ;
    convert << (int) idDevice;
    convert << " | " ;
    convert << (int) opCode;

    convert << " | " ;

    //split sizeLeft into two uint8_t
    convert16to8(sizeLeft, tab);
    convert << (int) tab[0];
    convert << (int) tab[1];

    convert << " | " ;

    if (getDataSize() != 0) {
        //Convert data
        for (int i = 0; i < getDataSize(); i++)
            convert << (int)data[i];
        convert << " | " ;
    }
    //split crc into two uint8_t
    convert16to8(crc, tab);
    convert << (int) tab[0];
    convert << (int) tab[1];
    convert << std::endl;

    return convert.str();
}


/*!
 * \brief Returns the size available for the data
 *
 *
 * \return the size a buffer can contain data
 */
int Buffer::getDataSize()
{
    return (sizeBuffer - DATA_INDEX - SIZE_CRC);
}


/*!
 * \brief Encodes the crc in the buffer
 */
void Buffer::crcEncoding()
{
    uint8_t* entireBuffer = new uint8_t[sizeBuffer- SIZE_CRC];
    memset(entireBuffer, 0, sizeBuffer-SIZE_CRC);

    entireBuffer[0] = getHeader();
    entireBuffer[1] = getID();
    entireBuffer[2] = getOpCode();

    uint8_t tab[2];
    convert16to8(this->getSizeLeft(), &tab[0]);
    memcpy(&entireBuffer[SIZE_INDEX], tab, 2);
    memcpy(&entireBuffer[DATA_INDEX], getData(),
           MIN(this->getSizeLeft(), this->getDataSize()));
    
    uint16_t crcComputed = computeCRC(entireBuffer,
                                      (sizeBuffer - SIZE_CRC));

    this->setCrc(crcComputed);
    delete [] entireBuffer;
}

/*!
 * \fn int crcIndex(int sizeBuffer)
 * \brief Returns the index of the crc in a buffer
 *
 * 
 * \param sizeBuffer entire size of a buffer
 * \return the index where the crc starts
 */
int crcIndex(int sizeBuffer)
{
    return (sizeBuffer - SIZE_CRC);
}
