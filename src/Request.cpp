#include "Request.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * TODO
 *
 * \param idDevice device's ID
 * \param size message's size
 * \param code operation code
 */
Request::Request(uint8_t idDevice, uint16_t size, uint8_t code) :
    OutgoingMessage(idDevice, SIZE_BUFFER, size, code)
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



