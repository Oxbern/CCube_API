#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H

#include "Message.h"

/**
 * @class Message creation when sending data
 */

class DataMessage : public Message {
 public :
    DataMessage(uint8_t id, uint16_t size, uint8_t code);
    ~DataMessage();
};

#endif
