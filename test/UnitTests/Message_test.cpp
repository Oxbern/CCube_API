#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Request.h"
#include "Ack.h"
#include "Question.h"

#include "Answer.h"

#include "Utils.h"

int main(int argc, char *argv[])
{
    OutgoingMessage message();

    OutgoingMessage mess(1, SIZE_BUFFER, 1, 0);

    Request dataMess(2, 92, 0);
    uint8_t *data = new uint8_t[92];
    for (int i = 0 ; i < 92; i++)
        data[i] = i;
    dataMess.encode(data);
    std::cout << "\n DataMess\n";
    std::cout << dataMess.toStringDebug();

    Ack ack();
    Ack ack2(2, ACK_OK);
    std::cout << "\n Ack2\n";
    std::cout << ack2.toStringDebug();

    ack2.encode(data);
    std::cout << "\n Ack2 encoded : \n";
    std::cout << ack2.toStringDebug();    
    
    Buffer buff;
    Buffer buff2(SIZE_BUFFER);
    if (buff2.getHeader() == 1)
        std::cout << "It is the first buffer \n";
    
    Question req();
    Question req2(3, GET_LEDSTATS);
    std::cout << "\n Req2 \n";
    std::cout << req2.toStringDebug();    
    
    Answer ans();
    Answer ans2(3, SIZE_QUESTION+1, GET_LUMINOSITY);
    std::cout << "\n Ans2\n";
    std::cout << dataMess.toStringDebug();    

    Request set();
    Request set2(4, 1, SET_LUMINOSITY);
    std::cout << "\n Set2\n";
    std::cout << set2.toStringDebug();    

    Answer one();
    Answer one2(4, SIZE_QUESTION+3, DEVICE_INFO);
    std::cout << " \n One2\n";
    std::cout << one2.toStringDebug();    
    one2.encode(data);
    std::cout << " \n One2 encoded :\n";
    std::cout << one2.toStringDebug();    

    delete [] data;
    
    std::cout << "PASSED \n";
    return 0;
}


