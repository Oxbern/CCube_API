#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>

#include "Buffer.h"

/**
 * @brief Default Constructor
 */
Buffer::Buffer() {
    header = 0;
    opCode = 0;
    sizeLeft = 0;
    data = new uint8_t[DATA_MAX_SIZE];
    crc = 0;
}

/**
 * @brief Constructor 
 * @param header
 * @param opCode
 * @param sizeLeft
 * @param crc
 */
Buffer::Buffer(uint8_t head, uint8_t code, uint16_t size, uint16_t crcCheck) {
    header = head;
    opCode = code;
    sizeLeft = size;
    data = new uint8_t[DATA_MAX_SIZE];
    for (int i = 0; i < DATA_MAX_SIZE; i ++)
        data[i] = 0;
    crc = crcCheck;
}

/**
 * @brief Destructor
 */
Buffer::~Buffer() {
    delete [] data;
}

/**
 * @brief Sets the header
 */
void Buffer::setHeader(uint8_t head) {
    header = head;
}
/** 
 * @brief Sets the opCode
 */
void Buffer::setOpCode(uint8_t code) {
    opCode = code;
}

/**
 * @brief Sets the sizeLeft
 */
void Buffer::setSizeLeft(uint16_t size) {
    sizeLeft = size;
}

/** 
 * @brief Sets the crc
 */
void Buffer::setCrc(uint16_t crcCheck) {
    crc = crcCheck;
}

/**
 * @brief Sends one buffer
 */
void Buffer::send(int fd) {
    write(fd, this, SIZE_BUFFER);
}
