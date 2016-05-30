#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "DataMessage.h"
#include "AckMessage.h"
#include "RequestMessage.h"
#include "AnswerMessage.h"
#include "SetMessage.h"
#include "FirstMessage.h"

int main(int argc, char *argv[]) {
    Message message();

    Message mess(1, SIZE_BUFFER, 1, 0);

    Buffer b();
    DataMessage dataMess(2, 12, 0);
    uint8_t *data = new uint8_t[92];
    for (int i = 0 ; i < 92; i++)
        data[i] = i;
    dataMess.encode(data);

    delete [] data;

    AckMessage ack();
    AckMessage ack2(2, ACK_OK);

    Buffer buff;
    Buffer buff2(SIZE_BUFFER);
    if (buff2.getHeader() == 1)
        std::cout << "It is the first buffer \n";

    RequestMessage req();
    RequestMessage req2(3, BUFF_ASKING);

    AnswerMessage ans();
    AnswerMessage ans2(3, LIGHT_RECEPTION);

    SetMessage set();
    SetMessage set2(4, LIGHT_SENDING);

    FirstMessage one();
    FirstMessage one2(4, DEVICE_INFO);
    
    std::cout << "PASSED \n";
    return 0;
}


