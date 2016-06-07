#ifndef REQUEST_H
#define REQUEST_H

/*!
 * \file Request.h
 * \brief TODO
 * \version 0.1
 */
#include "OutgoingMessage.h"

/*! 
 * \class Request
 * \brief TODO
 */
class Request : public OutgoingMessage
{
 public :
    /*!
     * \brief Constructor
     *
     * TODO
     *
     * \param idDevice device's ID
     * \param size message's size
     * \param code operation code
     */
    Request(uint8_t id, uint16_t size, uint8_t code);
    /*!
     * \brief Destructor
     *
     */
    ~Request();
};

#endif
