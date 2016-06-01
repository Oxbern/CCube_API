#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H

/*!
 * \file DataMessage.h
 * \brief Messages of type Data : BUFF_SENDING, FIRMWARE_UPDATE_SENDING
 * \version 0.1
 */
#include "Message.h"

/*! 
 * \class DataMessage
 * \brief Class representing a message of type Data
 */
class DataMessage : public Message
{
 public :
    /*!
     * \brief Constructor
     *
     * Creates a message with a list of buffers
     *
     * \param idDevice device's ID
     * \param size message's size
     * \param code operation code : BUFF_SENDING, FIRMWARE_UPDATE_SENDING
     */
    DataMessage(uint8_t id, uint16_t size, uint8_t code);
    /*!
     * \brief Destructor
     *
     */
    ~DataMessage();
};

#endif
