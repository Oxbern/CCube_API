#include "RequestMessage.h"

/**
 * @brief Creates a request
 * @param idDevice
 * @param opCode
 */
RequestMessage::RequestMessage(uint8_t id, uint8_t opCode) : Message(id, SIZE_REQUEST, SIZE_REQUEST - DATA_INDEX - SIZE_CRC, opCode)
{
    LOG(1, "RequestMessage(idDevice, opCode)");    
}

/**
 * @brief Destructor
 */
RequestMessage::~RequestMessage()
{
    LOG(1, "~RequestMessage()");
}
