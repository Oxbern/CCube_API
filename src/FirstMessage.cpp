#include "FirstMessage.h"

/**
 * @brief Creates a request
 * @param idDevice
 * @param opCode
 */
FirstMessage::FirstMessage(uint8_t id, uint8_t opCode) : Message(id, SIZE_FIRST, SIZE_FIRST - DATA_INDEX - SIZE_CRC, opCode)
{
    LOG(1, "FirstMessage(idDevice, opCode)");    
}

/**
 * @brief Destructor
 */
FirstMessage::~FirstMessage()
{
    LOG(1, "~FirstMessage()");
}
