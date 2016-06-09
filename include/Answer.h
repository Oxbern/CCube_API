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
    uint8_t *received;
    
    /*!
     * \brief Constructor
     *
     * Creates an answer
     *
     * \param id device's ID
     * \param sizeData
     * \param opCode
     */   
    Answer(uint8_t id, uint8_t opCode);
    
    /*!
     * \brief Destructor
     *
     */
    ~Answer();

    /*!
     * \brief Verifies
     * \return bool
     */
    bool verify();
};

#endif
