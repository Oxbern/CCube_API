#ifndef ACK_H
#define ACK_H

/*!
 * \file AckMessage.h
 * \brief Messages of type ACK : ACK_ERR, ACK_OK, ACK_NOK 
 * \version 0.1
 */
#include "Message.h"

/*! 
 * \class ACK
 * \brief Class representing a message of type ACK
 */

class AckMessage : public Message
{
 public :
    /*!
     * \brief Constructor
     *
     * Constructor of AckMessage class
     *
     * \param id : device's ID
     * \param ackType : ack's operation code
     */
    AckMessage(uint8_t id, uint8_t ackType);

    /*!
     * \brief Destructor
     *
     * Destructor of AckMessage class
     */
    ~AckMessage();
    
    void encodeAck(uint16_t sizeLeftPack, uint8_t opCodePack);

    void handleAck(int fd, Message &msg);
    bool checkAck(uint16_t crc);
    void setAck(int fd);

    uint8_t getAckType() const;
};

#endif
