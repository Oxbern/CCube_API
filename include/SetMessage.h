#ifndef SETMESSAGE_H
#define SETMESSAGE_H

#include "Message.h"

/**
 * @class Message creation when wanting to set something
 */
class SetMessage : public Message
{
 public :
    SetMessage(uint8_t id, uint8_t code);
    ~SetMessage();
};

#endif
