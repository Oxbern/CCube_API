#include "AnswerMessage.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * Creates an answer
 *
 * \param id device's ID
 * \param opCode LIGHT_RECEPTION, SCREEN_SIZE_RECEPTION, 
 * FIRMWARE_VERSION_RECEPTION, ID_RECEPTION
 */
AnswerMessage::AnswerMessage(uint8_t id, uint8_t opCode) : Message(id, SIZE_ANSWER, SIZE_ANSWER - DATA_INDEX - SIZE_CRC, opCode)
{
    LOG(1, "AnswerMessage(idDevice, opCode)");    
}

/*!
 * \brief Destructor
 *
 */
AnswerMessage::~AnswerMessage()
{
    LOG(1, "~AnswerMessage()");
}
