#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "DataMessage.h"
#include "AckMessage.h"

int main(int argc, char *argv[]) {
    Message message;

    Message mess(1, SIZE_BUFFER, 1, 0);

    Buffer b();
    DataMessage dataMess(2, 12, 0);
     uint8_t *data = new uint8_t[92];
     for (int i = 0 ; i < 92; i++)
         data[i] = i;
     dataMess.encode(data);

     delete [] data;

     AckMessage ack;
     AckMessage ack2(2, ACK_OK);

     Buffer buff;
       Buffer buff2(SIZE_BUFFER);
    if (buff2.getHeader() == 1)
        std::cout << "It is the first buffer \n";
    
    std::cout << "PASSED \n";
    return 0;
}


