#include "Utils.h"
#include "Buffer.h"
#include <sstream>

/**
 * @brief Creates a buffer with no data place
 */
Buffer::Buffer() :
    header(0), sizeBuffer(0), opCode(0), sizeLeft(0), crc(0)
{
    std::cout << "Buffer()1\n";
    data = new uint8_t[0];
    std::cout << "Buffer()2\n";    
}

/**
 * @brief Creates a right sized buffer
 */
Buffer::Buffer(int sizeBuff) :
    sizeBuffer(sizeBuff), opCode(0), sizeLeft(0), crc(0)
{
    header = 0;
    std::cout << "Buffer(sizebuff)1\n";    
    data = new uint8_t[sizeBuff-DATA_INDEX - SIZE_CRC];
    std::cout << "Buffer(sizeBuff)2\n";    
}


/**
 * @brief Destructor
 */
Buffer::~Buffer()
{
    std::cout << "~Buffer()1\n";        
    // if (data != NULL) {
    //     LOG(1, "Destructor for Buffer called");
    //     delete[] data;
    // }
    // data = NULL;
    std::cout << "~Buffer()2\n";            
}

int dataSize(int sizeBuffer) {
    return (sizeBuffer - DATA_INDEX - SIZE_CRC);
}

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

int Buffer::getSizeBuffer() const
{
    return this->sizeBuffer;
}

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
 * @todo choose between Buffer.toArray, Message.toArray, both or neither
 * @brief Converts a buffer into an array
 * @param buffLinear the filled array
 */
void Buffer::toArray(uint8_t* buffLinear)
{
    if (buffLinear != NULL) {
        buffLinear[HEADER_INDEX] = header;
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
 * @brief todo
 */
std::string Buffer::toString()
{
    std::ostringstream convert;
    uint8_t tab[2];
    convert << (int) header;
    convert << (int) opCode;

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
