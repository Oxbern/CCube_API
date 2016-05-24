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
    uint16_t **ledBuffer;
    
 public :
    Cube();
    
    ~Cube();

    void on(int x, int y, int z);
    void off();
    void off(int x, int y, int z);
    void toggle(int x, int y, int z);
    void toArray(uint8_t * ledStatus);
    void display(const char *dev);
    uint8_t getLedBuffer(int x, int y, int z);
};

#endif
