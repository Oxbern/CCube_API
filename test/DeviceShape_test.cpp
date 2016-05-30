#include <cstdlib>
#include <iostream>

#include "DeviceShape.h"


int main(int argc, char* argv[]) {
    int size = 9;
    DeviceShape d (size, size, size);

    /*************************************
        TEST 1 : display all the leds
     *************************************/
    printf("******* Leds switched off *******\n");
    std::cout << d;


    /*************************************
        TEST 2 : switch on all the leds
     *************************************/
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y)
            for (int z = 0; z < size; ++z)
                d.on(x,y,z);
    printf("******* Leds switched on *******\n");
    std::cout << d;

    /*************************************
            TEST 3 : toArray() method
     *************************************/

    for (int z = 0; z < size; ++z) {
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x){
                if ((x % 2) == 0) {
                    d.off(x, y, z);
                }
            }
        }
    }

    uint8_t *leds = d.toArray();
    printf("******* toArray() method *******\n");
    for (int i = 0; i < d.getSizeInBytes(); i++)
        std::cout << (int)leds[i];
    std::cout << std::endl;
    delete [] leds;

    /*************************************
        TEST 4 : toggle(x,y,z) method
    *************************************/
    printf("******* Before toggle *******\n");
    std::cout << d;
    for (int z = 0; z < size; ++z) {
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x){
                d.toggle(x, y, z);
            }
        }
    }
    printf("******* After toggle *******\n");
    std::cout << d;


    /*************************************
        TEST 5 : off() method
    *************************************/
    printf("******* off() method *******\n");
    d.off();
    std::cout << d;

    return EXIT_SUCCESS;
}