#include "Cube.h"

/**
 * @brief TODO
 */
Cube::Cube(int s, Device *d, Point p, bool b) : 
    ShapeToDisplay(s, d, p, b)
{
    LOG(1,"Constructor cube");
    init();
}

/**
 * @brief TODO
 */
void Cube::init()
{
    for (int x = 0; x < device->getcurrentConfig()->getSizeX(); x++) {
	for (int y = 0; y < device->getcurrentConfig()->getSizeY(); y++) {	    
	    for (int z = 0; z < device->getcurrentConfig()->getSizeZ(); z++) {
		if (full) 
		    {
			if (x >= origin.getX() && x < origin.getX() + size
			    && y >= origin.getY() && y < origin.getY() + size
			    && z >= origin.getZ() && z < origin.getZ() + size) 
			    device->getcurrentConfig()->on(x, y, z);
		    }
		else		    
		    if (x == origin.getX() || x == origin.getX() + size - 1
			|| y == origin.getY() || y == origin.getY() + size - 1
			|| z == origin.getZ() || z == origin.getZ() + size - 1) 
			device->getcurrentConfig()->on(x, y, z);	
	    }
	}
    }
}

/**
 * @brief TODO
 */
Cube::~Cube()
{
    LOG(1,"Destructor cube");
}

/**
 * @brief TODO
 */
bool Cube::incrSize() 
{
    std::cout << "X = " << origin.getX() + size 
              << ", Y = " << origin.getY() + size 
              <<", Z = " << origin.getZ() + size << std::endl;
    if (origin.getX() + size == 9 
	|| origin.getY() + size == 9 
	|| origin.getZ() + size == 9) 
	{
	    std::cout << "Cube size cannot increase more" << std::endl;
	    return false;
	}
    size++;
    device->getcurrentConfig()->off();
    init();
    return true;
}

/**
 * @brief TODO
 */
bool Cube::decrSize() 
{
    if (size == 0) {
	std::cout << "Cube size cannot decrease more" << std::endl;
	return false;
    }
    size--;
    device->getcurrentConfig()->off();
    init();
    return true;
}

/**
 * @brief TODO
 */
bool Cube::moveUp() 
{
    if (origin.getZ() + size < 9)
	{
	    device->getcurrentConfig()->off();
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

/**
 * @brief TODO
 */
bool Cube::moveDown() 
{
    if (origin.getZ() > 0)
	{
	    device->getcurrentConfig()->off();
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

/**
 * @brief TODO
 */
bool Cube::moveLeft() 
{
    if (origin.getY()  > 0)
	{
	    device->getcurrentConfig()->off();
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

/**
 * @brief TODO
 */
bool Cube::moveRight() 
{
    if (origin.getY() + size < 9)
	{
	    device->getcurrentConfig()->off();
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

/**
 * @brief TODO
 */
bool Cube::moveForward() 
{
    if (origin.getX() + size < 9)
	{
	    device->getcurrentConfig()->off();
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

/**
 * @brief TODO
 */
bool Cube::moveBackward() 
{
    if (origin.getX() > 0)
	{
	    device->getcurrentConfig()->off();
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


/**
 * @brief TODO
 */
void Cube::print(std::ostream &str)
{
    ShapeToDisplay::print(str);
}

/**
 * @brief TODO
 */
std::ostream& operator<<(std::ostream &out, Cube &c)
{
    c.print(out);
    return out;
}
