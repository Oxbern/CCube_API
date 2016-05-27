#include "Cube.h"


Cube::Cube(int s, int x, int y, int z, Point p, bool b) : ShapeToDisplay(s, x, y, z, p, b)
{
    init();
    std::cout << "Constructor Cube" << std::endl;
}

void Cube::init()
{
    for (int x = 0; x < 9; x++) {
	for (int y = 0; y < 9; y++) {	    
	    for (int z = 0; z < 9; z++) {
		if (full) 
		    {
			if (x >= origin.getX() && x < origin.getX() + size
			    && y >= origin.getY() && y < origin.getY() + size
			    && z >= origin.getZ() && z < origin.getZ() + size) 
			    on(x, y, z);
		    }
		else		    
		    if (x == origin.getX() || x == origin.getX() + size - 1
			|| y == origin.getY() || y == origin.getY() + size - 1
			|| z == origin.getZ() || z == origin.getZ() + size - 1) 
			on(x, y, z);	
	    }
	}
    }
}

Cube::Cube() : ShapeToDisplay()
{
    on(origin.getX(), origin.getY(), origin.getZ());
}

void Cube::print(std::ostream &str) const 
{
    if (full)
	str << "Full Shape";
    else
	str << "Empty Shape";
    str << " of size " << size;
    str << " where origin is " << origin << std::endl;

    this->DeviceShape::print(str);
}

Cube::~Cube() 
{
    std::cout << "Destructor of Cube" << std::endl;
}

bool Cube::incrSize() 
{
    if (origin.getX() + size == 8 
	|| origin.getY() + size == 8 
	|| origin.getZ() + size == 8) 
	{
	    std::cout << "Cube size cannot increase more" << std::endl;
	    return false;
	}
    size++;
    DeviceShape::off();
    init();
    return true;
}

bool Cube::decrSize() 
{
    if (size == 0) {
	std::cout << "Cube size cannot decrease more" << std::endl;
	return false;
    }
    size--;
    DeviceShape::off();
    init();
    return true;
}

bool Cube::moveUp() 
{
    if (origin.getZ() + size < 10)
	{
	    DeviceShape::off();
	    origin.incrZ();
	    init();
	    return true;
	}
    else
	{
	std::cout << "Cannot go higher" << std::endl; 
	return false;
	}
}

bool Cube::moveDown() 
{
    if (origin.getZ() > 0)
	{
	    DeviceShape::off();
	    origin.decrZ();
	    init();
	    return true;
	}
    else 
	{
	    std::cout << "Cannot go deeper" << std::endl; 
	    return false;
	}
}

bool Cube::moveLeft() 
{
    if (origin.getY()  > 0)
	{
	    DeviceShape::off();
	    origin.decrY();
	    init();
	    return true;
	}
    else
	{
	    std::cout << "Cannot move more on the left" << std::endl; 
	    return false;
	}
}

bool Cube::moveRight() 
{
    if (origin.getY() + size < 10)
	{
	    DeviceShape::off();
	    origin.incrY();
	    init();
	    return true;
	}
    else 
	{
	    std::cout << "Cannot move more on the right" << std::endl; 
	    return false;
	}
}

bool Cube::moveForward() 
{
    if (origin.getX() + size < 10)
	{
	    DeviceShape::off();
	    origin.incrX();
	    init();
	    return true;
	}
    else
	{
	    std::cout << "Cannot move more forward" << std::endl; 
	    return false;
	}
}

bool Cube::moveBackward() 
{
    if (origin.getX() > 0)
	{
	    DeviceShape::off();
	    origin.decrX();
	    init();
	    return true;
	}
    else 
	{
	    std::cout << "Cannot move more backward" << std::endl; 
	    return false;
	}
}
