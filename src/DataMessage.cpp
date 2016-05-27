#include "Utils.h"
#include "DataMessage.h"

/**
 * @brief Creates an empty message
 */
DataMessage::DataMessage() : Message()
{
}

/**
 * @brief Creates a message with list of buffers with opcode and sizeLeft
 * @param size of the message
 * @param code operation code
 */
DataMessage::DataMessage(int idDevice, uint16_t size, uint8_t code) : Message(idDevice, SIZE_BUFFER, size, code)
{
}


/**
 * @brief Destructor
 */
DataMessage::~DataMessage()
{
}


/**
 * @brief Fills the buffers with the data
 * @param data to encode
 */
void DataMessage::encode(uint8_t *dataToEncode)
{}



