#include <iostream>
#include <fstream>

#include "Device.h"
#include "DeviceShape.h"


int main(int argc, char *argv[]) {
    Device dev("/dev/ttyACM0", 1);
    dev.connect();

/*
    int sizeAckData = SIZE_ACK - SIZE_OPCODE - SIZE_CRC - SIZE_SIZE - 1;
    uint8_t data[3] = {1,2,3};
    
    Message m (dev.getID(), SIZE_BUFFER, sizeAckData, ACK_OK);
    m.encode(data);
*/
    DeviceShape cubeLed(9,9,9);
    cubeLed.on(0,0,7);

    //std::cout << cubeLed;

    Message m (dev.getID(), SIZE_BUFFER, (9*9*9)/8, 1);

    uint8_t  * tabLed = cubeLed.toArray();
    /*for(int i =0; i < (9*9*9); i++) {
        //tabLed[364] = 1
        std::cout << (int) tabLed[i];
    }
    std::cout << std::endl;*/

    std::cout << static_cast<void*>(tabLed) << std::endl;
    m.encode(tabLed);
    std :: cout << m.toStringDebug();

    dev.send(&m);

    /*char *buffer = new char [7];
    buffer[6] = '\0';
    std::fstream &file = dev.getFile();

    if (file.is_open()) {
        std::cout << std::endl;
        file.read(buffer, 6);
        std::cout << buffer << std::endl;
    }

    delete []buffer;*/

    dev.disconnect();

    return EXIT_SUCCESS;
}