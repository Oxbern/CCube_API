#include "ShapeToDisplay.h"


void ShapeToDisplay::initialisation() 
{
    for (int x = 0; x < sizeX; ++x)
        for (int y = 0; y < sizeY; ++y)
            for (int z = 0; z < sizeZ; ++z)
                status[x][y][z] = false;
}

/**
 * @brief TODO
 */
ShapeToDisplay::ShapeToDisplay(int i, Point p, bool b, int x, int y, int z) : 
size(i), origin(p), full(b), sizeX(x), sizeY(y), sizeZ(z) 
{
    LOG(1, "ShapeToDisplay(int i, Point p, bool b, int x, int y, int z)");

    //Allocation
    status = new bool**[sizeX];
    for (int X = 0; X < sizeX; ++X) {
        status[X] = new bool *[sizeY];
        for (int Y = 0; Y < sizeY; ++Y)
            status[X][Y] = new bool [sizeZ];
    }

    // initialisation
    initialisation();
}

/**
 * @brief TODO
 */
ShapeToDisplay::~ShapeToDisplay() {
    LOG(1, "~ShapeToDisplay()");

    //Deallocation
    if (status != NULL) {
        for (int x = 0; x < sizeX; ++x) {
            for (int y = 0; y < sizeY; ++y) {
                delete[] status[x][y];
            }
            delete[] status[x];
        }
        delete[] status;
        status = NULL;
    }
}

/**
 * @brief TODO
 */
void ShapeToDisplay::print(std::ostream &str) {
    if (full)
        str << "This is a full shape :" << std::endl;
    else
        str << "This is an empty shape :" << std::endl;
    str << "Size : " << size << std::endl;
    str << "Origin : " << origin << std::endl;
    str << "3D array of size " << sizeX << ", " << sizeY << ", " << sizeZ << std::endl;

    for (int z = 0; z < sizeZ; ++z) {
        str << "Z = " << z << std::endl;
        for (int y = 0; y < sizeY; ++y) {
            str << "Y = " << y << std::endl;
            for (int x = 0; x < sizeX; ++x) {
                if (status[x][y][z])
                    str << "1 ";
                else
                    str << "0 ";
            }
            str << std::endl;
        }
        str << std::endl;
    }
}

/**
 * @brief TODO
 */
std::ostream& operator<<(std::ostream &out, ShapeToDisplay &std) {
    std.print(out);
    return out;
}

/**
 * @brief TODO
 */
bool ShapeToDisplay::incrSize() {
    size++;
    if (size > sizeX || size > sizeY || size > sizeZ) {
        std::cout << "size bigger than device dimensions" << std::endl;
        std::cout << "size = " << size << std::endl;
        std::cout << "sizeX = " << sizeX
                << ", sizeY = " << sizeY
                << ", sizeZ = " << sizeZ << std::endl;
        size--;
        return false;
    }
    return true;
}

/**
 * @brief TODO
 */
bool ShapeToDisplay::decrSize() {
    size--;
    if (size < 0) {
        std::cout << "negative size" << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief TODO
 */
bool *** ShapeToDisplay::getStatus() {
    return this->status;
}

bool ShapeToDisplay::on(int x, int y, int z) {
    if (x > (sizeX - 1) || y > (sizeY - 1) || z > (sizeZ - 1)) {
        std::cerr << "Index of led out of bounds" << std::endl;
        return false;
    }
    return (status[x][y][z] = true);
}

/**
 * @brief Turns off the cube
 */
void ShapeToDisplay::off() {
    initialisation();
}

int ShapeToDisplay::getSizeX() const 
{
    return sizeX;
}

int ShapeToDisplay::getSizeY() const {
return sizeY;
}

int ShapeToDisplay::getSizeZ() const {
return sizeZ;
}