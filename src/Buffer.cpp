#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <iostream>


#include "Buffer.h"

using namespace std;
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

void Buffer::describe(){
    cout <<"\n";
    cout << "header : "<< std::hex << (int) this->header << "\n"<<
	"opCode : " << (int) this->opCode <<"\n" <<
	"sizeLeft : " << (int) this->sizeLeft <<"\n"<<
	"Data : \n";
    for (int i = 0; i < DATA_MAX_SIZE; i ++){
	cout << (int) this->data[i] << " | ";
	
    }
    cout << "\nCRC : "<< (int) this->crc <<"\n";
	
}

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
    
    return buffLinear;
}
