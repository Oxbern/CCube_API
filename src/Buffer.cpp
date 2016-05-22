#include "Buffer.h"

/**
 * @brief Default Constructor
 */
Buffer::Buffer() {
    std::perror("Not yet implemented");
    exit(EXIT_FAILURE);
}

/**
 * @brief Constructor 
 * @param header
 * @param codeOp
 * @param sizeLeft
 * @param crc
 */
Buffer::Buffer(uint8_t head, uint8_t code, uint16_t size, uint16_t crcCheck) {
    header = head;
    codeOp = code;
    sizeLeft = size;
    data = new uint8_t[DATA_MAX_SIZE];
    crc = crcCheck;
}

/**
 * @brief Destructor
 */
Buffer::~Buffer() {
    delete [] data;
}


