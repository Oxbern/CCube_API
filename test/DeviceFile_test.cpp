#include <iostream>

#include "Device.h"


int main(int argc, char *argv[]) {
    int size = 9;
    Device dev("/dev/stdout", "NoId", size, size, size);

    if (dev.connect())
        dev.write("Write in a file in C++");
    else
        std:: cerr << "Wrong file" << std::endl;

    dev.disconnect();

    return EXIT_SUCCESS;
}