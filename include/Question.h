#ifndef QUESTION_H
#define QUESTION_H

/*!
 * \file Question.h
 * \brief TODO
 *
 * \version 0.1
 */

#include "OutgoingMessage.h"

/*!
 * \class Question 
 * \brief Class representing a message of type request
 */
class Question : public OutgoingMessage
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates TODO
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
