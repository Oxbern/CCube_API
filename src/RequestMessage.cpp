#include "RequestMessage.h"

/*!
 * \brief Constructor
 *
 * Creates a request
 *
 * \param id device's ID
 * \param opCode BUFF_ASKING, LIGHT_ASKING, SCREEN_SIZE_ASKING, 
 * FIRMWARE_VERSION_ASKING, ID_ASKING, AVAILABLE, WHO_ARE_YOU
 */       
RequestMessage::RequestMessage(uint8_t id, uint8_t opCode) :
    Message(id, SIZE_REQUEST, SIZE_REQUEST - DATA_INDEX - SIZE_CRC, opCode)
{
    LOG(1, "RequestMessage(idDevice, opCode)");
    this->listBuffer[0].crcEncoding();    
}

/*!
 * \brief Destructor
 *
 */
RequestMessage::~RequestMessage()
{
    LOG(1, "~RequestMessage()");
}

