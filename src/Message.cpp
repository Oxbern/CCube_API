#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <iostream>
using namespace std;

#include "Message.h"
#include "Ack.h"

extern "C" {
#include "crc.h"
#include "virtualCube.h"
}
/**
 * @brief Default Constructor
 */
Message::Message() {
    size = 0;
    opCode = 0;
    listBuffer = new Buffer[0];
}

/**
 * @brief Constructor
 * @param size of the message
 * @param code operation code
 */
Message::Message(uint16_t size, uint8_t code) {
    this->size = size;
    this->opCode = code;
    listBuffer = new Buffer[NbBuffers()];
    listBuffer[0].setHeader(0x1); // first one
    for (int i = 0; i< NbBuffers(); i++) {
        listBuffer[i].setOpCode(code);
        listBuffer[i].setSizeLeft(size - i*DATA_MAX_SIZE);
    }    
}

/**
 * @brief Destructor
 */
Message::~Message() {
    delete [] listBuffer;
}

/**
 * @brief 
 */
int Message::NbBuffers() {
    if ((size % DATA_MAX_SIZE) == 0)
        return size/DATA_MAX_SIZE;
    else
        return size/DATA_MAX_SIZE + 1;
}

/**
 * @brief encoding
 * @param data data to encode
 * @todo dataToEncode's size
 */
void Message::encode(uint8_t *dataToEncode, uint16_t sizeData) {
    int j;
    for (int i = 0; i < NbBuffers(); i ++) {
        j = 0;
        while (j < DATA_MAX_SIZE) {
            if (j < sizeData)
                listBuffer[i].data[j] = dataToEncode[j];
            else
                listBuffer[i].data[j] = 0;
            j++;
        }
        uint16_t crcComputed = computeCRC(listBuffer[i].data, 8*DATA_MAX_SIZE);
        listBuffer[i].setCrc(crcComputed);
    }
}

/**
 * @brief Find a buffer based on its opCode and sizeLeft
 * @todo return for else
 * @return The right buffer
 */

Buffer Message::getBuffer(uint8_t opCode, uint16_t sizeLeft) {
    for (int i = 0; i < NbBuffers(); i++) {
	if (listBuffer[i].opCode == opCode && listBuffer[i].sizeLeft == sizeLeft)
	    return listBuffer[i];
    }
}

/**
 * @brief Sends a message
 */
void Message::send(int fd) {
    for (int i = 0; i < NbBuffers(); i++) {
	uint8_t buf[6];
        
	if (fd) {
	    write(fd, listBuffer+i, SIZE_BUFFER);
	    for (uint8_t j = 0; j < NbBuffers(); j++)
		listBuffer[j].describe();
            int index = 0, c = 0;
	
	    while (read(fd, &c, 1) > 0) {
	        buf[index] = c;
	        index ++;
	    }
	}
	// else
	//     CDC_Receive_FS(listBuffer+i, NULL);
	
	Ack ack(buf[0], buf[1],
		(buf[2] << 8) + buf[3], (buf[4] << 8) + buf[5]);
	
	ack.checkAck(computeCRC(buf+1, 3*sizeof(uint8_t)));
	ack.handleAck(fd, *this);
    }
}


