#include "Utils.h"
#include "Buffer.h"
#include <sstream>

/**
 * @brief Creates a buffer with no data place
 */
Buffer::Buffer() :
    header(0), idDevice(0), sizeBuffer(0), opCode(0), sizeLeft(0), crc(0)
{
    data = new uint8_t[0];
    LOG(1, "Buffer()");
}

/**
 * @brief Creates a right sized buffer
 */
Buffer::Buffer(int sizeBuff) :
    header(0), idDevice(0), sizeBuffer(sizeBuff), opCode(0), sizeLeft(0), crc(0)
{
    data = new uint8_t[sizeBuff-DATA_INDEX - SIZE_CRC]();
    LOG(1, "Buffer(sizeBuffer)");
}


/**
 * @brief Destructor
 */
Buffer::~Buffer()
{
    LOG(1, "~Buffer()");
    if (data != NULL) {
        LOG(1, "Destructor for Buffer called");
        delete[] data;
    }
    data = NULL;
}
/**
 * @brief Returns the size available for the data
 * @param entire size of the buffer
 */
int dataSize(int sizeBuffer) {
    return (sizeBuffer - DATA_INDEX - SIZE_CRC);
}

/**
 * @brief Returns the index of the crc
 * @param entire size of the buffer
 */
int crcIndex(int sizeBuffer) {
    return (sizeBuffer - SIZE_CRC);
}

/**
 * @brief Sets the header
 * @param head
 */
void Buffer::setHeader(uint8_t head) {
    this->header = head;
}

/**
 * @brief Sets the id of the Device 
 * @param idDevice
 */
void Buffer::setID(uint8_t id) {
    this->idDevice = id;
}

/**
 * @brief Sets the opCode
 * @param code
 */
void Buffer::setOpCode(uint8_t code) {
    this->opCode = code;
}

/**
 * @brief Sets the sizeLeft
 * @param size
 */
void Buffer::setSizeLeft(uint16_t size) {
    this->sizeLeft = size;
}

/**
 * @brief Sets the crc
 * @param crcCheck
 */
void Buffer::setCrc(uint16_t crcCheck) {
    this->crc = crcCheck;
}

/**
 * @brief Sets the data
 * @param index
 * @param dataIndex
 */
void Buffer::setData(int index, uint8_t dataIndex) {
    this->data[index] = dataIndex;
}

/**
 * @brief Gets the header
 */
uint8_t Buffer::getHeader() const
{
    return this->header;
}

/**
 * @brief Gets the operation code
 */
uint8_t Buffer::getOpCode() const {
    return this->opCode;
}

/**
 * @brief Gets the sizeLeft
 */
uint16_t Buffer::getSizeLeft() const
{
    return this->sizeLeft;
}

/**
 * @brief Gets the data
 */
uint8_t * Buffer::getData() const
{
    return this->data;
}

/**
 * @brief Gets the crc
 */
uint16_t Buffer::getCrc() const
{
    return this->crc;
}

/**
 * @brief Gets the size of the buffer
 */
int Buffer::getSizeBuffer() const
{
    return this->sizeBuffer;
}

uint8_t Buffer::getID() const
{
    return this->idDevice;
}

/**
 * @brief Operator == 
 * @param buffer
 */
bool Buffer::operator==(Buffer b){
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

/**
 * @brief Converts a buffer into an array
 * @param buffLinear the filled array
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
        for (int i = 0; i < dataSize(sizeBuffer); i++)
            buffLinear[DATA_INDEX + i] = data[i];

        //split crc into two uint8_t
        int indexCrc = crcIndex(sizeBuffer);
        convert16to8(crc, tab);
        buffLinear[indexCrc] = tab[0];
        buffLinear[indexCrc + 1] = tab[1];
    }
}

/**
 * @brief Prints a buffer
 * @return string
 */
std::string Buffer::toString()
{
    std::ostringstream convert;
    uint8_t tab[2];
    convert << (int) header;
    convert << (int) opCode;
    convert << (int) idDevice;

    //split sizeLeft into two uint8_t
    convert16to8(sizeLeft, tab);
    convert << (int) tab[0];
    convert << (int) tab[1];

    //Convert data
    for (int i = 0; i < dataSize(sizeBuffer); i++)
        convert << (int)data[i];

    //split crc into two uint8_t
    convert16to8(crc, tab);
    convert << (int) tab[0];
    convert << (int) tab[1];

    return convert.str();
}


/**
 * @brief Prints a buffer for debugging
 * @return string
 */
std::string Buffer::toStringDebug(int indexInMess)
{
    std::ostringstream convert;
    uint8_t tab[2];
    convert << "Buffer n°" << indexInMess << " : | ";
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

    //Convert data
    for (int i = 0; i < dataSize(sizeBuffer); i++)
        convert << (int)data[i];
    convert << " | " ;

    //split crc into two uint8_t
    convert16to8(crc, tab);
    convert << (int) tab[0];
    convert << (int) tab[1];
    convert << std::endl;

    return convert.str();
}
