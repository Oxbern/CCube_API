#include "Buffer.h"

/**
 * @brief Creates a buffer
 */
Buffer::Buffer()
{

}

/**
 * @brief Creates a buffer
 * @param header : indicates if it is the first buffer of the message or not
 * @param opCode 
 * @param sizeLeft
 * @param crcCheck
 */
Buffer::Buffer(uint8_t head, uint8_t code, uint16_t size, uint16_t crcCheck)
{

}

/**
 * @brief Destructor
 */
Buffer::~Buffer()
{

}

/**
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
