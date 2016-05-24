#include "Message.h"

/**
 * @brief Creates an empty message
 */
Message::Message() {

}

/**
 * @brief Creates a message without any data or crc
 * @param size of the message
 * @param code operation code
 */
Message::Message(uint16_t size, uint8_t code)
{

}


/**
 * @brief Destructor
 */
Message::~Message()
{

}

/**
 * @brief Calculates the number of buffers necessary to create Message
 * @return number of buffers
 */
int Message::NbBuffers()
{
    return 0;
}

/**
 * @brief Fills the buffers with the data
 * @param data to encode
 * @param sizeData data's size
 */
void Message::encode(uint8_t *dataToEncode, uint16_t sizeData)
{

}
