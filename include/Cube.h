#ifndef CUBE_H
#define CUBE_H

#include <cstdint>
#include <cstdbool>

#include "DeviceShape.h"

/**
* @class Cube
* @brief TODO
*/

class Cube : public DeviceShape {
public :
    Cube();
    ~Cube();

    bool on(int x, int y, int z);
    bool off();
    bool off(int x, int y, int z);
    bool toggle(int x, int y, int z);
    void toArray(uint8_t * ledStatus);
};
#endif
