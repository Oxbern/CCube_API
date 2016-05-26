#include <iostream>

#include "Device.h"


int main(int argc, char *argv[]) {
    Device dev("/dev/stdout", 1);

    if (dev.connect())
        dev.write("Write in a file in C++");
    else
        std:: cerr << "Wrong file" << std::endl;

    dev.disconnect();

    return EXIT_SUCCESS;
}
