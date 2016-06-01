#include "DataMessage.h"

/*!
 * \brief Constructor
 *
 * Creates a message with a list of buffers
 *
 * \param idDevice device's ID
 * \param size message's size
 * \param code operation code : BUFF_SENDING, FIRMWARE_UPDATE_SENDING
 */
DataMessage::DataMessage(uint8_t idDevice, uint16_t size, uint8_t code) :
    Message(idDevice, SIZE_BUFFER, size, code)
{
    LOG(1, "DataMessage(idDevice, sizeMessage, opCode)");
}

/*!
 * \brief Destructor
 *
 */
DataMessage::~DataMessage()
{
    LOG(1, "~DataMessage()");
}



