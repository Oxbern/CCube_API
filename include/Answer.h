#ifndef ANSWER_H
#define ANSWER_H

/*!
 * \file Answer.h
 * \brief Messages of type answer 
 * \version 0.5
 */
#include <cstdint>

#include "IncomingMessage.h"

/*! 
 * \class Answer
 * \brief Class representing a message of type Answer
 */
class Answer : public IncomingMessage
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates an answer
     *
     * \param id device's ID
     * \param opCode
     * \param size
     */   
    Answer(uint8_t id, int size, uint8_t code);
    
    /*!
     * \brief Destructor
     *
     */
    ~Answer();
};

#endif
