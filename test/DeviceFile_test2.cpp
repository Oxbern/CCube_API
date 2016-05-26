#include <iostream>
#include <fstream>
#include <cstdint>

#include "Device.h"


int main(int argc, char *argv[]) {
    Device dev("/dev/stdin", 1);


    int sizeAckData = SIZE_ACK - SIZE_OPCODE - SIZE_CRC - SIZE_SIZE - 1;
    uint8_t data[3] = {1,2,3};

    Message m (SIZE_BUFFER, sizeAckData, ACK_OK);
    m.encode(data);

    dev.send(m);

    char *buffer = new char [7];
    buffer[6] = '\0';
    std::fstream &file = dev.getFile();

    if (file.is_open()) {
        std::cout << std::endl;
        file.read(buffer, 6);
        std::cout << buffer << std::endl;
    }

    delete []buffer;

    dev.disconnect();

    return EXIT_SUCCESS;
}
