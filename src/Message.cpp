#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <iostream>
#include <string.h>

#include "Message.h"
#include "Ack.h"

extern "C" {
#include "crc.h"
#include "virtualCube.h"
}
/**
 * @brief Creates an empty message
 */
Message::Message() {
    size = 0;
    opCode = 0;
    listBuffer = new Buffer[0];
}

/**
 * @brief Creates a message without any data or crc
 * @param size of the message
 * @param code operation code
 */
Message::Message(uint16_t size, uint8_t code) {
    this->size = size;
    this->opCode = code;
    listBuffer = new Buffer[NbBuffers()];
    listBuffer[0].setHeader(1); // first one
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
 * @brief Calculates the number of buffers necessary to create Message
 * @return number of buffers
 */
int Message::NbBuffers() {
    if ((size % DATA_MAX_SIZE) == 0)
        return size/DATA_MAX_SIZE;
    else
        return size/DATA_MAX_SIZE + 1;
}

/**
 * @brief Fills the buffers with the data
 * @param data to encode
 * @param sizeData data's size
 */
void Message::encode(uint8_t *dataToEncode, uint16_t sizeData) {
    int j = 0; int k= 0;
    for (int i = 0; i < NbBuffers(); i ++) {
        while (j < DATA_MAX_SIZE) {
            if (k < sizeData)
                listBuffer[i].data[j] = dataToEncode[k];
            else
                listBuffer[i].data[j] = 0;
            j++; k++;
        }
	j = 0;


        uint16_t crcComputed = computeCRC(listBuffer[i].data, sizeof(uint8_t)*DATA_MAX_SIZE);
        listBuffer[i].setCrc(crcComputed);
    }
}

/**
 * @brief Finds a buffer based on its opCode and sizeLeft
 * @param opCode 
 * @param sizeLeft
 * @todo return for else
 * @return buffer
 */

Buffer Message::getBuffer(uint8_t opCode, uint16_t sizeLeft) {
    for (int i = 0; i < NbBuffers(); i++) {
	if (listBuffer[i].opCode == opCode && listBuffer[i].sizeLeft == sizeLeft)
	    return listBuffer[i];
    }
}

/**
 * @brief Sends a message
 * @param fd file descriptor
 */
void Message::send(int fd) {    
    std::cout << "Sending Ok :" << fd << "\n";

    for (int i = 0; i < NbBuffers(); i++) {
	uint8_t buf[6];
        
	if (fd) {
	    uint8_t pack[64];
	    memcpy(pack,(listBuffer[i]).toArray(),64);
	    for (int j = 0; j < 64; j++) 
                std::cout<< (int) pack[j] << " | ";
            std::cout<<"\n";
	    if (fd == 1)
		CDC_Receive_FS(pack, NULL);
	    else
		write(fd, pack, SIZE_BUFFER);
	    
	    //listBuffer[i].describe();
            //int index = 0, c = 0;
	
	    // while (read(fd, &c, 1) > 0) {
	    //     buf[index] = c;
	    //     index ++;
	    // }
	}
	// else
	//     CDC_Receive_FS(listBuffer+i, NULL);
	
    // 	Ack ack(buf[0], buf[1],
    // 		(buf[2] << 8) + buf[3], (buf[4] << 8) + buf[5]);
	
    // 	ack.checkAck(computeCRC(buf+1, 3*sizeof(uint8_t)));
    // 	ack.handleAck(fd, *this);
     }
}


