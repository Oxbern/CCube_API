#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H

/*!
 * \file RequestMessage.h
 * \brief Messages of type request : BUFF_ASKING, LIGHT_ASKING, SCREEN_SIZE_ASKING, 
 * FIRMWARE_VERSION_ASKING, ID_ASKING, AVAILABLE, WHO_ARE_YOU
 *
 * \version 0.1
 */

#include "Message.h"

/*!
 * \class RequestMessage 
 * \brief Class representing a message of type request
 */
class RequestMessage : public Message
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates a request
     *
     * \param id device's ID
     * \param opCode BUFF_ASKING, LIGHT_ASKING, SCREEN_SIZE_ASKING, 
     * FIRMWARE_VERSION_ASKING, ID_ASKING, AVAILABLE, WHO_ARE_YOU
     */       
    RequestMessage(uint8_t id, uint8_t code);

    /*!
     * \brief Destructor
     *
     */    
    ~RequestMessage();

    /*!
     * \fn void encodeCrc()
     * \brief Calculates and sets the crc
     */
    void encodeCrc();
};

#endif
