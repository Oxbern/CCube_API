#ifndef ANSWERMESSAGE_H
#define ANSWERMESSAGE_H

#include "Message.h"
/**
 * @class Message creation when answering to a question
 */

class AnswerMessage : public Message
{
 public :
    AnswerMessage(uint8_t id, uint8_t code);
    ~AnswerMessage();
};

#endif
