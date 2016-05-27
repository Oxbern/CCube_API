#include "ShapeToDisplay.h"

ShapeToDisplay::ShapeToDisplay(int i, int x, int y, int z, Point p, bool b) 
  : DeviceShape::DeviceShape(x, y, z), size(i), origin(p), full(b)
{
    std::cout << "Constructor ShapeToDisplay" << std::endl;
}

ShapeToDisplay::~ShapeToDisplay() 
{
    std::cout << "Destructor ShapeToDisplay" << std::endl;
}

void ShapeToDisplay::print(std::ostream &str) 
{
    str << "Shape size : " << size << std::endl;
    this->DeviceShape::print(str);
}

std::ostream& operator <<(std::ostream &out, ShapeToDisplay &std)
{
    std.print(out);
    return out;
}

bool ShapeToDisplay::incrSize() 
{
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

bool ShapeToDisplay::decrSize() 
{
    size--;
    if (size < 0) {
	std::cout << "negative size" << std::endl;
	return false;
    }
    return true;
}
