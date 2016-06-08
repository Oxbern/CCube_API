#include <sstream>

#include "IncomingMessage.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * Creates a message
 *
 * \param id device's ID
 * \param sizeBuff the buffers' size
 * \param size the size of the data to encode
 * \param code the message's operation code
 */    
IncomingMessage::IncomingMessage(uint8_t id, int size, uint8_t code) :
    idDevice(id), size(size), opCode(code)
{
    
    LOG(1, "IncomingMessage(id, sizeBuff, size, code)");
}

/*!
 * \brief Destructor
 */
IncomingMessage::~IncomingMessage()
{
    LOG(1, "~IncomingMessage()");
}

/*!
 * \brief Receives a message from a device
 * \param c controller
 * \return bool
 */
bool IncomingMessage::receive(Controller &c)
{
    read(c.getConnectedDevice()->getFile(), this, size);

    return true;
}

/*!
 * \brief Gets the device's ID
 * \return ID
 */
uint8_t IncomingMessage::getID() const
{
    return this->idDevice;
}


