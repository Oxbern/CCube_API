#ifndef ANSWER_H
#define ANSWER_H

/*!
 * \file Answer.h
 * \brief Messages of type answer 
 * \version 1.0
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
    uint8_t *received; /*!< the buffer received raw */
    
    /*!
     * \brief Constructor
     *
     * Creates an answer
     *
     * \param id device's ID
     * \param opCode
     */   
    Answer(uint8_t id, uint8_t opCode);
    
    /*!
     * \brief Destructor
     *
     */
    ~Answer();

    /*!
     * \brief Verifies if it is a correct answer
     * \return bool
     */
    bool verify();
};

#endif
