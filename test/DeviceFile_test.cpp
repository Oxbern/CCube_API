#include <iostream>

#include "Device.h"


int main(int argc, char *argv[]) {
    int size = 9;
    Device dev("/dev/stdin", "NoId", size, size, size);
    dev.connect();

    dev.write("Write in a file in C++");

    dev.disconnect();

    return EXIT_SUCCESS;
}