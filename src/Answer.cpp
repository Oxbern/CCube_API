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
    received = new uint8_t[SIZE_ANSWER]();
    LOG(1, "Answer(id, opcode)");
}

/*!
 * \brief Destructor
 *
 */
Answer::~Answer()
{
    delete [] received;
    LOG(1, "~Answer()");
}


/*!
 * \todo check crc
 * \brief Verifies
 * \return bool
 */
bool Answer::verify()
{
    if (received[HEADER_INDEX] == 1 && received[ID_INDEX] == idDevice
        && received[OPCODE_INDEX] == opCode) {
        // TODO check crc
        return true;
    } else
        return false;        
}
