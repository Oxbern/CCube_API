#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>

#include "Message.h"


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
    size = size;
    opCode = code;
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
 */
void Message::encode(uint8_t *dataToEncode) {
    int j;    
    for (int i = 0; i < NbBuffers(); i ++) {
        j = 0;
        while (j < DATA_MAX_SIZE)
            listBuffer[i].data[j] = dataToEncode[j];
    }
}

/**
 * @brief Sends a message
 */
void Message::send(int fd) {
    for (int i = 0; i < NbBuffers(); i++)
        write(fd, listBuffer+i, SIZE_BUFFER);
}
