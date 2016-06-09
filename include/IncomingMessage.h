#ifndef INCOMINGMESSAGE_H
#define INCOMINGMESSAGE_H

/*!
 * \file IncomingMessage.h
 * \brief IncomingMessages of all types
 * \version 0.1
 */

#include <iostream>

#include "Buffer.h"
#include "Controller.h"

using namespace apicube;
/*!
 * \class IncomingMessage 
 * \brief Parent class 
 */

class IncomingMessage
{
 protected :
    uint8_t idDevice; /*!< device's ID */
    int size;  /*!< the size of the incoming buffer */
    uint8_t opCode; /*!< the message's operation code */
    
 public :
    /*!
     * \brief Constructor
     *
     * Creates a message
     *
     * \param id device's ID
     * \param size the size of the data to encode
     * \param code the message's operation code
     */    
    IncomingMessage(uint8_t id, int size, uint8_t code);

    /*!
     * \brief Destructor
     */
    ~IncomingMessage();

};


#endif
