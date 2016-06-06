#ifndef ANSWERMESSAGE_H
#define ANSWERMESSAGE_H

/*!
 * \file AnswerMessage.h
 * \brief Messages of type answer : LIGHT_RECEPTION, SCREEN_SIZE_RECEPTION, 
 * FIRMWARE_VERSION_RECEPTION, ID_RECEPTION
 * \version 0.1
 */
#include <cstdint>

#include "Message.h"

/*! 
 * \class AnswerMessage
 * \brief Class representing a message of type Answer
 */
class AnswerMessage : public Message
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates an answer
     *
     * \param id device's ID
     * \param opCode LIGHT_RECEPTION, SCREEN_SIZE_RECEPTION, 
     * FIRMWARE_VERSION_RECEPTION, ID_RECEPTION
     */   
    AnswerMessage(uint8_t id, uint8_t code);
    
    /*!
     * \brief Destructor
     *
     */
    ~AnswerMessage();
};

#endif
