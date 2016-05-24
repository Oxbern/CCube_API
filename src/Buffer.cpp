#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <iostream>
#include <string.h>

#include "Buffer.h"
#include "Ack.h"

extern "C" {
#include "crc.h"
#include "virtualCube.h"
}


/**
 * @brief Creates a buffer
 */
Buffer::Buffer() {
    header = 0;
    opCode = 0;
    sizeLeft = 0;
    data = new uint8_t[DATA_MAX_SIZE];
    crc = 0;
}

/**
 * @brief Creates a buffer
 * @param header : indicates if it is the first buffer of the message or not
 * @param opCode 
 * @param sizeLeft
 * @param crcCheck
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
    // for (int i = 0; i < DATA_MAX_SIZE; i ++)
    //     delete (&data[i]);
    delete [] data;
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
 * @brief Sends one buffer
 * @param fd file descriptor
 */
void Buffer::send(int fd) {
    uint8_t pack[SIZE_BUFFER];
    memcpy(pack, this->toArray(), SIZE_BUFFER);
    for (int j = 0; j < SIZE_BUFFER; j++)
        std::cout << (int) pack[j] << " | ";
    std::cout << "\n";
    if (fd == 1)
        CDC_Receive_FS(pack, NULL);
    else 
        write(fd, pack, SIZE_BUFFER);
}

/**
 * @brief Prints a buffer
 */
void Buffer::describe(){
    std::cout <<"\n";
    std::cout << "header : "<< std::hex << (int) this->header << "\n"<<
	"opCode : " << (int) this->opCode <<"\n" <<
	"sizeLeft : " << (int) this->sizeLeft <<"\n"<<
	"Data : \n";
    for (int i = 0; i < DATA_MAX_SIZE; i ++){
        std::cout << (int) this->data[i] << " | ";
	
    }
    std::cout << "\nCRC : "<< (int) this->crc <<"\n";	
}

/**
 * @brief Converts a buffer into an array
 * @return array
 */
uint8_t * Buffer::toArray() {
    uint8_t *buffLinear = new uint8_t[SIZE_BUFFER];
    buffLinear[HEADER_INDEX] = header;
    buffLinear[OPCODE_INDEX] = opCode;
    buffLinear[SIZE_INDEX] = (uint8_t)(sizeLeft >> 8);
    buffLinear[SIZE_INDEX +1] = (uint8_t)(sizeLeft & 0xFF);

    for (int i = 0; i < DATA_MAX_SIZE; i++)
        buffLinear[DATA_INDEX+i] = data[i];

    buffLinear[CRC_INDEX] = (uint8_t)(crc >> 8);
    buffLinear[CRC_INDEX+1] = (uint8_t)(crc & 0xFF);

    std::cout << "CRC : " << (buffLinear[CRC_INDEX] << 8) +
	buffLinear[CRC_INDEX + 1] << "\n";
    
    return buffLinear;
}
