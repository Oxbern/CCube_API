#ifndef FIRSTMESSAGE_H
#define FIRSTMESSAGE_H

/*!
 * \file FirstMessage.h
 * \brief First Message sent by the cube to give its personnal info, DEVICE_INFO
 * \version 0.1
 */

#include "Message.h"

/*!
 * \class FirstMessage 
 * \brief Class representing a message with the cube's personnal info
 */
class FirstMessage : public Message
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates an answer
     *
     * \param id device's ID
     * \param opCode DEVICE_INFO
     */       
    FirstMessage(uint8_t id, uint8_t code);

    /*!
     * \brief Destructor
     *
     */    
    ~FirstMessage();
};

#endif
