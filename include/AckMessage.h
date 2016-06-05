#ifndef ACK_H
#define ACK_H

/*!
 * \file AckMessage.h
 * \brief Messages of type ACK : ACK_ERR, ACK_OK, ACK_NOK 
 * \version 0.1
 */
#include "Message.h"

/*! 
 * \class AckMessage
 * \brief Class representing a message of type ACK
 */
class AckMessage : public Message
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates an ack
     *
     * \param id device's ID
     * \param ackType ACK_OK, ACK_ERR, ACK_NOK
     */
    AckMessage(uint8_t id, uint8_t ackType);

    /*!
     * \brief Destructor
     *
     */
    ~AckMessage();

    /*!
     * \todo is this methode usefull ?
     * \fn void encodeAck(uint16_t sizeLeftPack, uint8_t opCodePack)
     * \brief Fills the buffers with the data
     *
     * Method which encodes an ack
     *
     * \param sizeLeftPack 
     * \param opCodePack
     */
    void encodeAck(uint16_t sizeLeftPack, uint8_t opCodePack);

    /*!
     * \todo is this method usefull ? 
     * \fn void handleAck(int fd, Message &msg)
     * \brief TODO
     * \param fd
     * \param msg
     */
    void handleAck(int fd, Message &msg);

    /*!
     * \todo is this method usefull ?
     * \fn void setAck(int fd)
     * \brief TODO
     * \param fd
     */
    void setAck(int fd);

    /*!
     * \fn uint8_t getAckType() const
     * \brief Getter
     *
     * Method which returns the type of ack
     *
     * \return the ack's operation code
     */
    uint8_t getAckType() const;
};

#endif
