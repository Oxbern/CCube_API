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
     * \param dataToEncode 
     */
    void encode(uint8_t *dataToEncode);

    
};

#endif
