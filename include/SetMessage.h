#ifndef SETMESSAGE_H
#define SETMESSAGE_H

/*!
 * \file SetMessage.h
 * \brief Messages of type setting : LIGHT_SENDING
 *
 * \version 0.1
 */

#include "Message.h"

/*!
 * \class SetMessage
 * \brief Class representing a message when wanting to set something
 */
class SetMessage : public Message
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates a setting request
     *
     * \param id device's ID
     * \param code LIGHT_SENDING
     */           
    SetMessage(uint8_t id, uint8_t code);

    /*!
     * \brief Destructor
     *
     */    
    ~SetMessage();
};

#endif
