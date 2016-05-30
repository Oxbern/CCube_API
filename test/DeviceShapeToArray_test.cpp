#include <cstdlib>
#include <iostream>
#include <cmath>

#include "DeviceShape.h"
#include "Utils.h"

/**
 * Test file for the method toArray
 */
int main(int argc, char* argv[]) {
    int size = 9;
    DeviceShape d(size, size, size);
    int sizeArray = d.getSizeInBytes();
    std::cout << "Size of uint8_t array : " << sizeArray << " Bytes" << std::endl;
    std::cout << std::endl;

    d.on(0, 0, 0); //Switch on the first led
    d.on(4, 4, 4);
    d.on(8, 8, 8); //Switch on the last led

    std::cout << "=> on(0, 0, 0) and on(4, 4, 4) and on(8, 8, 8)" << std::endl;
    std::cout << std::endl;
    std::cout << "DeviceShape.toArray () : " << std::endl;
    uint8_t *ledArray = d.toArray();
    printArray(ledArray, sizeArray);

    delete [] ledArray;

    return EXIT_SUCCESS;
}
