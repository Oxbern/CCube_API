#ifndef CUBE_H
#define CUBE_H

#include <cstdint>

#define SIZE_DATA_LED 200

/**
 * @class Cube
 * @brief TODO
 */

class Cube {
 private :
    uint16_t ledBuffer[10][10];
    
 public :
    Cube();
    
    ~Cube();

    void on(int x, int y, int z);
    void off();
    void off(int x, int y, int z);
    void toggle(int x, int y, int z);
    uint8_t *toArray();
    void display(const char *dev);
};

#endif
