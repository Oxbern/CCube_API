#ifndef FIRSTMESSAGE_H
#define FIRSTMESSAGE_H

#include "Message.h"
/**
 * @class Message creation when wanting to set something
 */
class FirstMessage : public Message {
 public :
    FirstMessage(uint8_t id, uint8_t code);
    ~FirstMessage();
};

#endif
