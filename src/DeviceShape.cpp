#include "DeviceShape.h"

void DeviceShape::clearLed()
{
    for (int x = 0; x < sizeX; ++x)
        for (int y = 0; y < sizeY; ++y)
            for (int z = 0; z < sizeZ; ++z)
                ledStatus[x][y][z] = false;
}

DeviceShape::DeviceShape(int sizeX, int sizeY, int sizeZ) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ)
{
    log(1, "DeviceShape constructor called");
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

DeviceShape::~DeviceShape() {
    log(1, "DeviceShape destructor called");
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
 * @param ledStatus the filled array
 */
uint8_t * DeviceShape::toArray()
{
    uint8_t *ledArray = new uint8_t[sizeX*sizeY*sizeZ];
    int i = 0;
    for (int x = 0; x < sizeX; ++x)
        for (int y = 0; y < sizeY; ++y)
            for (int z = 0; z < sizeZ; ++z) {
                ledStatus[x][y][z] ? ledArray[i] = 1 : ledArray[i] = 0;
                ++i;
            }
    return ledArray;
}

/**
 * @brief : TODO
 */
std::ostream& operator<<(std::ostream& os, const DeviceShape& d)
{
    for (int z = 0; z < d.sizeZ; ++z) {
        os << "Z = " << z << "\n";
        for (int y = 0; y < d.sizeY; ++y) {
            os << "Y = " << y << "\n";
            for (int x = 0; x < d.sizeX; ++x) {
                if (d.ledStatus[x][y][z])
                    os << "1 ";
                else
                    os << "0 ";
            }
            os << "\n";
        }
        os << "\n";
    }
    return os;
}