#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H

#include "Message.h"
#include "Utils.h"

/**
 * @class Message creation when sending data
 */

class DataMessage : public Message {
 public :
    DataMessage();
    DataMessage(int id, uint16_t size, uint8_t code);
    ~DataMessage();
};

#endif
