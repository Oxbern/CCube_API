#include "Question.h"
#include "Utils.h"
#include "Debug.h"
#include "ErrorException.h"
#include "Answer.h"

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
bool Question::send(Controller &c)
{
    if (c.getConnectedDevice() == NULL)
        return false;

    LOG(2, "[SEND] Send a message :\n" + this->toStringDebug());

    int n = this->NbBuffers();

    for (int i = 0; i < n; i++) {
        LOG(5, "[SEND] Buffer N° " + std::to_string(i));

        // Convert the buffer i into an array
        uint8_t *bufferArray = new uint8_t[sizeBuffer];
        listBuffer[i].toArray(bufferArray);

        int nbTry = 0;

        do {
            // Send the message to the device
            if (!(c.getConnectedDevice()->writeToFileDescriptor(bufferArray,
                                                                sizeBuffer))) {
                throw ErrorException("Error while sending a message : "
                                     "Number of tries to send "
                                     "the message exceeded");
                c.disconnectDevice();
            } /* Buffer sent */
            LOG(5, "Buffer sent");
            
            Answer ans(c.getConnectedDevice()->getID(), opCode); 
            
        } while (++nbTry < MAX_TRY);

        //If number of tries exceeded
        if (nbTry == MAX_TRY) {
            LOG(2, "[HANDLER] NB TRY EXCEDEED");

            throw ErrorException("Error while receiving a ack: "
                                 "Number of tries to receive "
                                 "the ack exceeded");
        }

        delete [] bufferArray;
    }
    LOG(1, "[SEND] Message sent");
    return true;
}
