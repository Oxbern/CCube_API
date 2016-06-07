#ifndef INCOMINGMESSAGE_H
#define INCOMINGMESSAGE_H

/*!
 * \file IncomingMessage.h
 * \brief IncomingMessages of all types
 * \version 0.1
 */

#include <iostream>

#include "Buffer.h"

/*!
 * \class IncomingMessage 
 * \brief Parent class 
 */

class IncomingMessage
{
 protected :
    uint8_t idDevice; /*!< device's ID */
    int sizeBuffer;  /*!< the size of each buffer in listBuffer*/
    uint16_t sizeData; /*!< the size available for the data to encode */
    uint8_t opCode; /*!< the message's operation code */
    Buffer *listBuffer; /*!< the list of buffers representing the message */
    
 public :
    /*!
     * \brief Constructor
     *
     * Creates a message
     *
     * \param id device's ID
     * \param sizeBuff the buffers' size
     * \param size the size of the data to encode
     * \param code the message's operation code
     */    
    IncomingMessage(uint8_t id, int sizeBuff, uint16_t size, uint8_t code);

    /*!
     * \brief Constructor by copie
     *
     * Creates a message by copying another one
     *
     * \param M the other message which will be unchanged
     */        
    IncomingMessage(const IncomingMessage &M);

    /*!
     * \brief Destructor
     */
    ~IncomingMessage();

    /*!
     * \fn int NbBuffers() const
     * \brief Calculates the number of buffers necessary to encode a message
     * \return the number of buffers needed
     */
    int NbBuffers() const;

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

    /*!
     * \fn Buffer *getListBuffer() const
     * \brief Accessor to the list of buffers
     * \return list of buffers
     */
    Buffer *getListBuffer() const;

    /*!
     * \fn Buffer *getBuffer(uint8_t opCode, uint16_t sizeLeft) const
     * \brief Accessor to one specific buffer
     * \param opCode operation code
     * \param sizeLeft the size left of the buffer
     * \return a buffer
     */
    Buffer *getBuffer(uint8_t opCode, uint16_t sizeLeft) const;

    /*!
     * \fn int getSizeBuffer() const
     * \brief Gets the buffers' size
     * \return the size
     */
    int getSizeBuffer() const;

    /*!
     * \fn uint16_t getSizeData() const
     * \brief Gets the data's size
     * \return the size 
     */
    uint16_t getSizeData() const;

    /*!
     * \fn uint8_t getOpCode() const
     * \brief Gets the operation code
     * \return the opCode
     */
    uint8_t getOpCode() const;

    /*!
     * \fn uint8_t getID() const
     * \brief Gets the device's ID
     * \return ID
     */
    uint8_t getID() const;

    /*!
     * \fn std::string toStringDebug() const
     * \brief Prints for debug purposes
     * \return string
     */
    std::string toStringDebug() const;
};


#endif
