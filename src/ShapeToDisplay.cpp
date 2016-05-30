#include "ShapeToDisplay.h"

ShapeToDisplay::ShapeToDisplay(int i, Device *d, Point p, bool b)
: size(i), origin(p), full(b), device(d)
{
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
    
    device->getcurrentConfig()->print(str);
}

std::ostream& operator<<(std::ostream &out, ShapeToDisplay &std) {
    std.print(out);
    return out;
}

bool ShapeToDisplay::incrSize() {
    size++;
    if (size > device->getcurrentConfig()->getSizeX() 
            || size > device->getcurrentConfig()->getSizeY() 
            || size > device->getcurrentConfig()->getSizeZ()) {
        std::cout << "size bigger than device dimensions" << std::endl;
        std::cout << "size = " << size << std::endl;
        std::cout << "sizeX = " << device->getcurrentConfig()->getSizeX() 
                << ", sizeY = " << device->getcurrentConfig()->getSizeY()
                << ", sizeZ = " << device->getcurrentConfig()->getSizeZ() << std::endl;
        size--;
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

Device * ShapeToDisplay::getDevice() const 
{
    return this->device;
}