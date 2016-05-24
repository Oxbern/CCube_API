#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "Utils.h"
#include "Buffer.h"
#include "Message.h"
#include "Ack.h"

int main(int argc, char *argv[]) {
    Message message;

    Message mess(132, 2);
    uint8_t *data = new uint8_t[92];
    for (int i = 0 ; i < 92; i++)
        data[i] = i;
    mess.encode(data, 92);

    delete [] data;

    Ack ack;
    Ack ack2(ACK_OK, BUFF_SENDING, 32, 12);
    if (ack2.checkAck(12))
        std::cout << "The crc matches : " << ack2.getCrc() << "\n";

    Buffer buff;
    Buffer buff2(1, LIGHT_SENDING, 13, 22);
    if (buff2.getHeader() == 1)
        std::cout << "It is the first buffer \n";
    
    std::cout << "PASSED";
    return 0;
}


