#include "Utils.h"
#include "Buffer.h"
#include <sstream>

/**
 * @brief Creates a buffer with no data place
 */
Buffer::Buffer() : sizeBuffer(0), opCode(0), sizeLeft(0), crc(0), header(0)
{
    data = new uint8_t[0];
}

/**
 * @brief Creates a right sized buffer
 */
Buffer::Buffer(int sizeBuff) : sizeBuffer(sizeBuff), opCode(0), sizeLeft(0), crc(0), header(0)
{
    data = new uint8_t[sizeBuff-DATA_INDEX - SIZE_CRC];
}

/**
 * @brief Creates a buffer
 * @param header : indicates if it is the first buffer of the message or not
 * @param opCode 
 * @param sizeLeft
 * @param crcCheck
 */
Buffer::Buffer(int sizeBuff, uint8_t head, uint8_t code, uint16_t size, uint16_t crcCheck) :
    sizeBuffer(sizeBuff), opCode(code), sizeLeft(size), crc(crcCheck), header(head)
{
    data = new uint8_t[sizeBuff - DATA_INDEX - SIZE_CRC];
}

/**
 * @brief Destructor
 */
Buffer::~Buffer()
{
    if (data != NULL)
        delete [] data;
    data = NULL;
}

int sizeData(int sizeBuffer) {
    return (sizeBuffer - DATA_INDEX - SIZE_CRC);
}

/**
 * @todo choose between Buffer.toArray, Message.toArray, both or neither
 * @brief Converts a buffer into an array
 * @param buffLinear the filled array
 */
void Buffer::toArray(uint8_t* buffLinear)
{
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
uint8_t Buffer::getHeader() {
    return this->header;
}

/**
 * @brief Gets the operation code
 */
uint8_t Buffer::getOpCode() {
    return this->opCode;
}

/**
 * @brief Gets the sizeLeft
 */
uint16_t Buffer::getSizeLeft() {
    return this->sizeLeft;
}

/**
 * @brief Gets the data
 */
uint8_t * Buffer::getData() {
    return this->data;
}

/**
 * @brief Gets the crc
 */
uint16_t Buffer::getCrc() {
    return this->crc;
}

int Buffer::getSizeBuffer()
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
    for (int i = 0; i < sizeData(sizeBuffer); i++)
        convert << (int)data[i];

    //split crc into two uint8_t
    convert16to8(crc, tab);
    convert << (int) tab[0];
    convert << (int) tab[1];

    return convert.str();
}