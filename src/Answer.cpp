#include "Answer.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * Creates an answer
 *
 * \param id device's ID
 * \param opCode 
 * \param size
 */
Answer::Answer(uint8_t id, uint8_t opCode) :
    IncomingMessage(id, SIZE_ANSWER, opCode)
{
    LOG(1, "Answer(id, opcode)");
}

/*!
 * \brief Destructor
 *
 */
Answer::~Answer()
{
    LOG(1, "~Answer()");
}

