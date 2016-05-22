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
    listBuffer = new Buffer[getNumberOfBuffer()];
}

/**
 * @brief 
 */
int Message::getNumberOfBuffer() {
    if ((size % DATA_MAX_SIZE) == 0)
        return size/DATA_MAX_SIZE;
    else
        return size/DATA_MAX_SIZE + 1;
}
