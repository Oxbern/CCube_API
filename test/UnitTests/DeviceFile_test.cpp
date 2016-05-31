#include <iostream>

#include "Device.h"

int main(int argc, char *argv[])
{
    Device dev("/dev/stdout", 1);
    uint8_t buff[24] = "Write in a file in C++\n";

    if (dev.connect())
        dev.writeToFileDescriptor(buff, 24);
    else
        std:: cerr << "Wrong file" << std::endl;

    dev.disconnect();

    return EXIT_SUCCESS;
}
