#include "Answer.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * Creates an answer, which can only be one buffer
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

        // Check sizeLeft
        uint16_t size = convertTwo8to16(received[SIZE_INDEX], received[SIZE_INDEX + 1]);
        if (size > SIZE_ANSWER - DATA_INDEX - SIZE_CRC)
            return false;

        else {        

            // Check crc
            uint16_t expectedCRC = computeCRC(received, SIZE_ANSWER);
            uint16_t actualCRC = convertTwo8to16(received[SIZE_ANSWER - SIZE_CRC],
                                                 received[SIZE_ANSWER - SIZE_CRC +1]);

            return (expectedCRC == actualCRC); 
                }
        
    } else
        return false;        
}
