#include "ShapeToDisplay.h"

ShapeToDisplay::ShapeToDisplay(int i, int x, int y, int z, Device *d, Point p, bool b)
: size(i), origin(p), full(b), device(d), sizeX(x), sizeY(y), sizeZ(z) {
    LOG(1,"Constructor ShapeToDisplay");
}

ShapeToDisplay::~ShapeToDisplay() {
    LOG(1,"Destructor ShapeToDisplay");
    delete device;
}

void ShapeToDisplay::print(std::ostream &str) {
    if (full)
        str << "This is a full shape :" << std::endl;
    else
        str << "This is an empty shape :" << std::endl;
    str << "Size : " << size << std::endl;
    str << "Origin : " << origin << std::endl;
    str << "Dimension : X = " << sizeX << ", Y = " << sizeY << ", Z = " << sizeZ << std::endl;
    
    device->getcurrentConfig()->print(str);
}

std::ostream& operator<<(std::ostream &out, ShapeToDisplay &std) {
    std.print(out);
    return out;
}

bool ShapeToDisplay::incrSize() {
    size++;
    if (size > sizeX || size > sizeY || size > sizeZ) {
        std::cout << "size bigger than device dimensions" << std::endl;
        std::cout << "size = " << size << std::endl;
        std::cout << "sizeX = " << sizeX << ", sizeY = " << sizeY
                << ", sizeZ = " << sizeZ << std::endl;
        return false;
    }
    return true;
}

bool ShapeToDisplay::decrSize() {
    size--;
    if (size < 0) {
        std::cout << "negative size" << std::endl;
        return false;
    }
    return true;
}
