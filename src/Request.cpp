#include "Request.h"
#include "OutgoingMessage.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * TODO
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
 * \param dataToEncode 
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


