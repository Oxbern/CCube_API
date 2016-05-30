#include "DataMessage.h"

/**
 * @brief Creates a message with list of buffers with opcode and sizeLeft
 * @param size of the message
 * @param code operation code
 */
DataMessage::DataMessage(uint8_t idDevice, uint16_t size, uint8_t code) : Message(idDevice, SIZE_BUFFER, size, code)
{
    LOG(1, "DataMessage(idDevice, sizeMessage, opCode)");
}


/**
 * @brief Destructor
 */
DataMessage::~DataMessage()
{
    LOG(1, "~DataMessage()");
}



