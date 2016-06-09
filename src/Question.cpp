#include "Question.h"
#include "Utils.h"
#include "Debug.h"
#include "ErrorException.h"
#include "Answer.h"

#include <string.h>

/*!
 * \brief Constructor
 *
 * Creates a question which is represented by one single SIZE_QUESTION sized buffer *
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

/*!
 * \brief Sends a message to a device
 * \param c controller
 * \return bool
 */
bool Question::send(Controller &c, uint8_t *result)
{
    if (c.getConnectedDevice() == NULL)
        return false;

    LOG(2, "[SEND] Send a message :\n" + this->toStringDebug());

    uint8_t *bufferArray = new uint8_t[sizeBuffer];

    listBuffer[0].toArray(bufferArray);

    int nbTry = 0;
    Answer ans(c.getConnectedDevice()->getID(), opCode);

    do {
        // Send the message to the device
        if (!(c.getConnectedDevice()->writeToFileDescriptor(bufferArray,
                                                            SIZE_QUESTION))) {
            c.disconnectDevice();
            throw ErrorException("Error while sending a message : "
                                 "Number of tries to send "
                                 "the message exceeded");
        } /* Buffer sent */

        read(c.getConnectedDevice()->getFile(), ans.received, SIZE_ANSWER);

        LOG(5, "Buffer sent");

        if (ans.verify()) {
            memcpy(&result[0], &ans.received[DATA_INDEX],
                   ans.received[SIZE_INDEX + 1]);
            break;
        } else {
            ++nbTry;
        }

    } while (nbTry < MAX_TRY);

    //If number of tries exceeded
    if (nbTry == MAX_TRY) {
        LOG(2, "[HANDLER] NB TRY EXCEDEED");

        c.disconnectDevice();
        throw ErrorException("Error while receiving the answer : "
                             "Number of tries to receive "
                             "the answer exceeded");
    }


    delete [] bufferArray;

    LOG(1, "[SEND] Message sent");

    return true;
}
