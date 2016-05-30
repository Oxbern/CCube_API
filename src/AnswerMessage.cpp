#include "AnswerMessage.h"

/**
 * @brief Creates a request
 * @param idDevice
 * @param opCode
 */
AnswerMessage::AnswerMessage(uint8_t id, uint8_t opCode) : Message(id, SIZE_ANSWER, SIZE_ANSWER - DATA_INDEX - SIZE_CRC, opCode)
{
    LOG(1, "AnswerMessage(idDevice, opCode)");    
}

/**
 * @brief Destructor
 */
AnswerMessage::~AnswerMessage()
{
    LOG(1, "~AnswerMessage()");
}
