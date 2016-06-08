#ifndef REQUEST_H
#define REQUEST_H

/*!
 * \file Request.h
 * \brief Creates a request
 * \version 1.0
 */
#include "OutgoingMessage.h"

/*! 
 * \class Request
 * \brief Class representing the creation of a request
 * which is an outgoing message which does not need an answer from the device
 */
class Request : public OutgoingMessage
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates a request which can be represented by one single buffer
     * or by a list of SIZE_BUFFER sized buffers
     *
     * \param idDevice device's ID
     * \param sizeData message's size
     * \param code operation code
     */
    Request(uint8_t idDevice, uint8_t sizeData, uint8_t code);
    
    /*!
     * \brief Destructor
     *
     */
    ~Request();

    /*!
     * \fn void encode(uint8_t *dataToEncode)
     * \brief Fills the buffers with the data and calculates and sets the crc
     * 
     *  Fills the buffers with the data
     * if size(dataToEncode) > sizeData,
     * only the first sizeData values of dataToEncode will be encoded
     *
     * \param dataToEncode the data which fills a message
     */
    void encode(uint8_t *dataToEncode);

    
};

#endif
