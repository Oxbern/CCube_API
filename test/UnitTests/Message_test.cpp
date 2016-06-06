#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "DataMessage.h"
#include "AckMessage.h"
#include "RequestMessage.h"
#include "AnswerMessage.h"
#include "SetMessage.h"
#include "FirstMessage.h"
#include "Utils.h"

int main(int argc, char *argv[])
{
    Message message();

    Message mess(1, SIZE_BUFFER, 1, 0);

    DataMessage dataMess(2, 92, 0);
    uint8_t *data = new uint8_t[92];
    for (int i = 0 ; i < 92; i++)
        data[i] = i;
    dataMess.encode(data);
    std::cout << "\n DataMess\n";
    std::cout << dataMess.toStringDebug();

    AckMessage ack();
    AckMessage ack2(2, ACK_OK);
    std::cout << "\n Ack2\n";
    std::cout << ack2.toStringDebug();

    ack2.encode(data);
    std::cout << "\n Ack2 encoded : \n";
    std::cout << ack2.toStringDebug();    
    
    Buffer buff;
    Buffer buff2(SIZE_BUFFER);
    if (buff2.getHeader() == 1)
        std::cout << "It is the first buffer \n";
    
    RequestMessage req();
    RequestMessage req2(3, BUFF_ASKING);
    std::cout << "\n Req2 \n";
    std::cout << req2.toStringDebug();    
    
    AnswerMessage ans();
    AnswerMessage ans2(3, LIGHT_RECEPTION);
    std::cout << "\n Ans2\n";
    std::cout << dataMess.toStringDebug();    

    SetMessage set();
    SetMessage set2(4, LIGHT_SENDING);
    std::cout << "\n Set2\n";
    std::cout << set2.toStringDebug();    

    FirstMessage one();
    FirstMessage one2(4, DEVICE_INFO);
    std::cout << " \n One2\n";
    std::cout << one2.toStringDebug();    
    one2.encode(data);
    std::cout << " \n One2 encoded :\n";
    std::cout << one2.toStringDebug();    

    delete [] data;
    
    std::cout << "PASSED \n";
    return 0;
}


