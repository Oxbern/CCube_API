#include <iostream>
#include <fstream>

#include "Device.h"


int main(int argc, char *argv[]) {

    Message m(1, SIZE_BUFFER, 20, 0x1);

    std::fstream file;
    file.open("/dev/ttyACM0", std::ios::in | std::ios::out);

    std::cout << m.getBuffer()[0].toString() << std::endl;
    file << m.getBuffer()[0].toString();

    file.close();



    return EXIT_SUCCESS;
}
