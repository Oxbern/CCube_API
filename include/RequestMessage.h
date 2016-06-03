#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H

#include "Message.h"

/**
 * @class Message creation when asking for something
 */
class RequestMessage : public Message
{
 public :
    RequestMessage(uint8_t id, uint8_t code);
    ~RequestMessage();
    void encodeCrc();
};

#endif
