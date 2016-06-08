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

    Request dataMess(2, 92, SET_LEDSTATS);
    uint8_t *data = new uint8_t[92];
    for (int i = 0 ; i < 92; i++)
        data[i] = i;
    dataMess.encode(data);
    std::cout << "\n DataMess\n";
    std::cout << dataMess.toStringDebug();

    Buffer buff;
    Buffer buff2(SIZE_BUFFER);
    if (buff2.getHeader() == 1)
        std::cout << "It is the first buffer \n";
    
    Question req();
    Question req2(3, GET_LEDSTATS);
    std::cout << "\n Req2 \n";
    std::cout << req2.toStringDebug();    

    Request set();
    Request set2(4, 1, SET_LUMINOSITY);
    uint8_t *light = new uint8_t[1];
    light[0] = 1;
    set2.encode(light);
    std::cout << "\n Set2\n";
    std::cout << set2.toStringDebug();    

    delete [] light;
    delete [] data;
    
    std::cout << "PASSED \n";
    return 0;
}


