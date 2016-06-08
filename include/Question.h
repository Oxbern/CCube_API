#ifndef QUESTION_H
#define QUESTION_H

/*!
 * \file Question.h
 * \brief Creates a question
 *
 * \version 1.0
 */

#include "OutgoingMessage.h"

/*!
 * \class Question 
 * \brief Class representing the creation of a question asked to the device
 * which is an outgoing message which does need an answer from the device
 */
class Question : public OutgoingMessage
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates a question which is represented by one single SIZE_QUESTION sized buffer
     *
     * \param id device's ID
     * \param opCode
     */       
    Question(uint8_t id, uint8_t code);

    /*!
     * \brief Destructor
     *
     */    
    ~Question();
};

#endif
