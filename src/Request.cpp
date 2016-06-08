#include "Request.h"
#include "OutgoingMessage.h"
#include "Utils.h"
#include "Debug.h"
#include "ErrorException.h"
#include "Ack.h"

#include <string.h>

#define MAX_TRY 10

/*!
 * \brief Constructor
 *
 * Creates a request which can be represented by one single buffer
 * or by a list of SIZE_BUFFER sized buffers
 *
 * \param idDevice device's ID
 * \param sizeData message's size
 * \param code operation code
 */
Request::Request(uint8_t idDevice, uint8_t sizeData, uint8_t code) :
    OutgoingMessage(idDevice, MIN(sizeData + DATA_INDEX + SIZE_CRC, SIZE_BUFFER),
                    sizeData, code)
{
    LOG(1, "Request(idDevice, sizeMessage, opCode)");
}

/*!
 * \brief Destructor
 *
 */
Request::~Request()
{
    LOG(1, "~Request()");
}

/*!
 * \brief Fills the buffers with the data and calculates and sets the crc
 * \see crcEncoding()
 *
 *  Fills the buffers with the data
 * if size(dataToEncode) > sizeData,
 * only the first sizeData values of dataToEncode will be encoded
 *
 * \param dataToEncode the data which fills a message
 */
void Request::encode(uint8_t *dataToEncode)
{
    LOG(2, "OutgoingMessage encoding :");

    //Header, DeviceID, Opcode already set in the constructor
    int j = 0; int k= 0; int n = NbBuffers();

    //Fills the buffers with the data
    for (int i = 0; i < n; i ++) {
        while (j < (listBuffer[i].getDataSize())) {
            if (k < sizeData) {
                listBuffer[i].setData(j, dataToEncode[k]);
            }
            else {
                listBuffer[i].setData(j,0);
            }
            j++; k++;
        }
        j = 0;

        //Sets CRC computed on the entire buffer
        listBuffer[i].crcEncoding();

        LOG(2, "[ENCODING] Buffer N° " + std::to_string(i)
            + ": DATA = "
            + uint8ArrayToString(listBuffer[i].getData(), listBuffer[i].getDataSize())
            + " | CRC = " + std::to_string(listBuffer[i].getCrc()));
    }
}



/*!
 * \brief Sends a message to a device
 * \param c controller
 * \return bool
 */
bool Request::send(Controller &c)
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

        uint8_t *ackBuffer = new uint8_t[SIZE_ACK];
        memset(&ackBuffer[0], 0, SIZE_ACK);
        uint8_t ackRef[SIZE_ACK] = {1, 1, 1, 0, 3, bufferArray[2],
                                    bufferArray[3], bufferArray[4], 0, 0};
        printBuffer("Ref ACK", ackRef, SIZE_ACK);
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

            if (!c.secure)
                break;

            read(c.getConnectedDevice()->getFile(), &ackBuffer[0], SIZE_ACK);
            fsync(c.getConnectedDevice()->getFile());

            if (memcmp(ackBuffer, ackRef, SIZE_ACK - 2))
                ++nbTry;
            else
                break;

            printBuffer("ACK ACK ACK", ackBuffer, SIZE_ACK);

        } while (nbTry < MAX_TRY);

        //If number of tries exceeded
        if (nbTry == MAX_TRY) {
            LOG(2, "[HANDLER] NB TRY EXCEDEED");

            throw ErrorException("Error while receiving a ack: "
                                 "Number of tries to receive "
                                 "the ack exceeded");
            c.disconnectDevice();
        }

        delete [] bufferArray;
    }
    LOG(1, "[SEND] Message sent");
    return true;
}
