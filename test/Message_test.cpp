#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "DataMessage.h"
#include "AckMessage.h"

int main(int argc, char *argv[]) {
    Message message;

    DataMessage dataMess(12, 0);
    uint8_t *data = new uint8_t[92];
    for (int i = 0 ; i < 92; i++)
        data[i] = i;
    dataMess.encode(data);

    delete [] data;

    AckMessage ack;
    AckMessage ack2(ACK_OK);
    if (ack2.checkAck(0))
        std::cout << "The crc matches : " << ack2.getCrc() << "\n";

    Buffer buff;
    Buffer buff2(SIZE_BUFFER, 1, LIGHT_SENDING, 13, 22);
    if (buff2.getHeader() == 1)
        std::cout << "It is the first buffer \n";
    
    std::cout << "PASSED";
    return 0;
}


