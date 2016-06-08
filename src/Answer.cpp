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
Answer::Answer(uint8_t id, uint8_t sizeData, uint8_t opCode) :
    IncomingMessage(id, sizeData + DATA_INDEX + SIZE_CRC, sizeData, opCode)
{
    LOG(1, "Answer(idDevice, opCode)");    
}

/*!
 * \brief Destructor
 *
 */
Answer::~Answer()
{
    LOG(1, "~Answer()");
}

