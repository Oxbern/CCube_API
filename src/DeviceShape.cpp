#include <cmath>

#include "DeviceShape.h"

/**
 * @brief TODO
 */
void DeviceShape::clearLed()
{
    for (int x = 0; x < sizeX; ++x)
        for (int y = 0; y < sizeY; ++y)
            for (int z = 0; z < sizeZ; ++z)
                ledStatus[x][y][z] = false;
}

/**
 * @brief TODO
 */
DeviceShape::DeviceShape(int sizeX, int sizeY, int sizeZ) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ)
{
    LOG(1, "DeviceShape constructor called");
    //Allocation
    ledStatus = new bool**[sizeX];
    for (int x = 0; x < sizeX; ++x) {
        ledStatus[x] = new bool *[sizeY];
        for (int y = 0; y < sizeY; ++y)
            ledStatus[x][y] = new bool [sizeZ];
    }

    //Initialization
    clearLed();
}

/**
 * @brief TODO
 */
DeviceShape::~DeviceShape() {
    LOG(1, "DeviceShape destructor called");
    //Deallocation
    if (ledStatus != NULL) {
        for (int x = 0; x < sizeX; ++x) {
            for (int y = 0; y < sizeY; ++y) {
                delete[] ledStatus[x][y];
            }
            delete[] ledStatus[x];
        }
    delete[] ledStatus;
    }
    ledStatus = NULL;
}



/**
 * @brief Switchs on a led
 * @param x
 * @param y
 * @param z
 */
bool DeviceShape::on(int x, int y, int z)
{
    if (x > (sizeX - 1) || y > (sizeY-1) || z > (sizeZ-1)) {
        std::cerr << "Index of led out of bounds" << std::endl;
        return false;
    }
    return (ledStatus[x][y][z] = true);
}


/**
 * @brief Turns off the cube
 */
bool DeviceShape::off()
{
    clearLed();
    return true;
}


/**
 * @brief Turns off a led
 * @param x
 * @param y
 * @param z
 */
bool DeviceShape::off(int x, int y, int z)
{
    if (x > (sizeX - 1) || y > (sizeY-1) || z > (sizeZ-1)) {
        std::cerr << "Index of led out of bounds" << std::endl;
        return false;
    }
    return (ledStatus[x][y][z] = false);
}


/**
 * @brief Toggles a led
 * @param x
 * @param y
 * @param z
 */
bool DeviceShape::toggle(int x, int y, int z)
{
    if (x > (sizeX - 1) || y > (sizeY-1) || z > (sizeZ-1)) {
        std::cerr << "Index of led out of bounds" << std::endl;
        return false;
    }
    return (ledStatus[x][y][z] == true) ?
           (ledStatus[x][y][z] = false) : (ledStatus[x][y][z] = true);
}


/**
 * @brief Converts ledBuffer into an array
 * @param ledStatus : the filled array
 */
uint8_t * DeviceShape::toArray()
{
    uint8_t tmp = 0;
    uint8_t val;
    int i = 0;
    int j = 7;
    int iMax = ceil(double(sizeX * sizeY * sizeZ) / 8.0); //Nb of uint8_t in the array
    uint8_t *ledArray = new uint8_t[iMax];

    for (int x = 0; x < sizeX; ++x)
        for (int y = 0; y < sizeY; ++y)
            for (int z = 0; z < sizeZ; ++z) {
                val = ledStatus[x][y][z] ? 1 : 0;
                tmp |= (val << j);

                if (j == 0 || (x == 8 && y == 8 && z == 8)) {
                    ledArray[i] = tmp;
                    j = 7;
                    tmp = 0;
                    ++i;
                }else {
                    --j;
                }
            }

    return ledArray;
}

/**
 * @brief : TODO
 */
std::ostream& operator<<(std::ostream& os, const DeviceShape& d)
{
    d.print(os);
    return os;
}

void DeviceShape::print(std::ostream &str) const
{
    for (int z = 0; z < sizeZ; ++z) {
        str << "Z = " << z << std::endl;
        for (int y = 0; y < sizeY; ++y) {
            str << "Y = " << y << std::endl;
            for (int x = 0; x < sizeX; ++x) {
                if (ledStatus[x][y][z])
                    str << "1 ";
                else
                    str << "0 ";
            }
            str << std::endl;
        }
        str << std::endl;
    }
}
