#include "SetMessage.h"

/*!
 * \brief Constructor
 *
 * Creates a setting request
 *
 * \param id device's ID
 * \param code LIGHT_SENDING
 */           
SetMessage::SetMessage(uint8_t id, uint8_t opCode) :
    Message(id, SIZE_SET, SIZE_SET - DATA_INDEX - SIZE_CRC, opCode)
{
    LOG(1, "SetMessage(idDevice, opCode)");    
}

/*!
 * \brief Destructor
 *
 */
SetMessage::~SetMessage()
{
    LOG(1, "~SetMessage()");
}
