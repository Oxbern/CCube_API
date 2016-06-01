#include "Cube.h"
#include <sstream>

/**
 * @brief TODO
 */
Cube::Cube(int i, Point p, bool b, int x, int y, int z) : ShapeToDisplay(i, p, b, x, y, z)
{
    LOG(1,"Cube(int i, Point p, bool b, bool ***s, int x, int y, int z)");
    init();
}

/**
 * \fn void Cube::init()
 * \brief Function thaht initialise the device in terms 
 * of the parameters of the shape (the cube here)
 */
void Cube::init()
{
    for (int x = 0; x < sizeX; x++) {
	for (int y = 0; y < sizeY; y++) {	    
	    for (int z = 0; z < sizeZ; z++) {
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


Cube::~Cube()
{
    LOG(1,"~Cube()");
}

/**
 * \fn bool Cube::incrSize()
 * \brief Function that increases the size of the cube  
 * of the parameters of the shape (the cube here)
 */
bool Cube::incrSize() 
{
    int X = origin.getX() + size;
    int Y = origin.getY() + size;
    int Z = origin.getZ() + size;
    
    std::stringstream s;
    
    s << "X = " << X << ", Y = " << Y << ", Z = " << Z;

    LOG(1, s.str());
    
    if (origin.getX() + size == 9 
	|| origin.getY() + size == 9 
	|| origin.getZ() + size == 9) 
	{
	    std::cout << "Cube size cannot increase more" << std::endl;
	    return false;
	}
    size++;
    off();
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
    off();
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
	    off();
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
	    off();
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
	    off();
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
	    off();
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
	    off();
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
	    off();
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
