#include "Utils.h"
#include "Buffer.h"

/**
 * @brief Creates a buffer
 */
Buffer::Buffer() : header(0), opCode(0), sizeLeft(0), crc(0)
{
    data = new uint8_t[DATA_MAX_SIZE];
}

/**
 * @todo is this buffer useful ?
 * @brief Creates a buffer
 * @param header : indicates if it is the first buffer of the message or not
 * @param opCode 
 * @param sizeLeft
 * @param crcCheck
 */
Buffer::Buffer(uint8_t head, uint8_t code, uint16_t size, uint16_t crcCheck) :
    header(head), opCode(code), sizeLeft(size), crc(crcCheck)
{
    data = new uint8_t[DATA_MAX_SIZE];
}

/**
 * @brief Destructor
 */
Buffer::~Buffer()
{
    delete [] data;
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
