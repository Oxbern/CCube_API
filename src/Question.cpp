#include "Question.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * TODO
 *
 * \param id device's ID
 * \param opCode
 */       
Question::Question(uint8_t id, uint8_t opCode) :
    OutgoingMessage(id, SIZE_QUESTION, SIZE_QUESTION - DATA_INDEX - SIZE_CRC, opCode)
{
    LOG(1, "Question(idDevice, opCode)");
    this->listBuffer[0].crcEncoding();    
}

/*!
 * \brief Destructor
 *
 */
Question::~Question()
{
    LOG(1, "~Question()");
}

