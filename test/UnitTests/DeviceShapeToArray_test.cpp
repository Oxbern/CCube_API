#include <cstdlib>
#include <iostream>
#include <cmath>

#include "DeviceShape.h"
#include "Utils.h"
#include "string.h"
#include "assert.h"

#define DEBUG 0


/**
 * Test file for the method toArray
 */
int main(int argc, char* argv[])
{
    int size = 9;
    DeviceShape d(size, size, size);


    int sizeArray = d.getSizeInBytes();

#if DEBUG
    std::cout << "Size of uint8_t array : " << sizeArray << " Bytes" << std::endl;
#endif
    int sizeArrayExpected = 92;
    assert(sizeArray == sizeArrayExpected);


    /**
     * Test the toArray() method after having switched on some leds
     */

    d.on(0, 0, 0); //Switch on the first led
    d.on(4, 4, 4); //Swith on the led in the middle
    d.on(8, 8, 8); //Switch on the last led

    uint8_t *ledArray = new uint8_t[d.getSizeInBytes()];
    d.toArray(ledArray);


    uint8_t resExpected[sizeArrayExpected];
    memset(resExpected, 0, sizeArrayExpected);
    resExpected[0] = 128;
    resExpected[45] = 8;
    resExpected[91] = 128;

#if DEBUG
    std::cout << "DeviceShape.toArray () : " << std::endl;
    printArray(ledArray, sizeArray);
    std::cout << "Res expected : " << std::endl;
    printArray(resExpected, sizeArrayExpected);
#endif

    assert(memcmp(ledArray, resExpected, sizeArrayExpected) == 0);

    delete [] ledArray;

    std::cout << "Test : PASSED" << std::endl;

    return EXIT_SUCCESS;
}
