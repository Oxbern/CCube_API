#include "Point.h"
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief Creates a point of dimension 3 and coordinates x = 0, y = 0, z = 0 
 */
Point::Point() : x(0), y(0), z(0)
{
}

/**
 * @brief Creates a point for a cube of length 9 LEDs
 * @param x : first coordinate
 * @param y : seconde coordinate
 * @param z : third coordinate
 */
Point::Point(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z)
{
    if (x < 0 || x > 8){
	perror("Index (x) of led out of bounds");
	exit(EXIT_FAILURE);
    }
    if (y < 0 || y > 8){
	perror("Index (y) of led out of bounds");
	exit(EXIT_FAILURE);
    }
    if (z < 0 || z > 8){
	perror("Index (z) of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

/**
 * @brief Checks if the point is in the cube of length 9 LEDs
 * @param x : first coordinate
 * @param y : seconde coordinate
 * @param z : third coordinate
 * @return boolean
 */
bool Point::isOutOfBounds(uint8_t x,uint8_t y, uint8_t z){
    if (x < 0 || x > 8)
	return true;
    if (y < 0 || y > 8)
	return true;
    if (z < 0 || z > 8)
	return true;
    return false;
}

/**
 * @brief Set the first coordinate
 * @param x : value setted
 */
void Point::setX(uint8_t x)
{
    if (x >= 0 && x < 9)
	this->x = x;
    else{
	perror("Index (x) of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

/**
 * @brief Set the second coordinate
 * @param y : value setted
 */
void Point::setY(uint8_t y)
{
    if (y >= 0 && y < 9)
	this->y = y;
    else{
	perror("Index (y) of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

/**
 * @brief Set the third coordinate
 * @param z : value setted
 */
void Point::setZ(uint8_t z)
{
    if (z >= 0 && z < 9)
	this->z = z;
    else{
	perror("Index (z) of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

/**
 * @brief return the first coordinate
 * @return uint8_t
 */
uint8_t Point::getX() const
{
    return this->x;
}

/**
 * @brief return the second coordinate
 * @return uint8_t
 */
uint8_t Point::getY() const
{
    return this->y;
} 

/**
 * @brief return the third coordinate
 * @return uint8_t
 */
uint8_t Point::getZ() const
{
    return this->z;
}

/**
 * @brief Print the attributes of the point
 * @param str : stream on which we write
 */
void Point::print(std::ostream &str) const
{
    str << "(" << (int) x << ", " << (int) y << ", " << (int) z << ")";
}

/**
 * @brief Overload of the operator =
 * @param p : Point 
 * @return Point
 */
Point& Point::operator = (const Point &p) 
{
    if (&p != this) {
	x = p.getX();
	y = p.getY();
	z = p.getZ();
    }
    return *this;
}

/**
 * @brief Overload of the operator ==
 * @param p : Point to compare with 
 * @return boolean
 */
bool Point::operator== (Point p)
{
    return (this->x == p.getX() &&
     	    this->y == p.getY() &&
    	    this->z == p.getZ());
}

/**
 * @brief Overload of the operator <<
 * @param str : stream on which we write
 * @param p : Point to compare with 
 * @return boolean
 */
std::ostream& operator << (std::ostream &out, const Point &p)
{
    p.print(out);
    return out;
}

/**
 * @brief Increment the first coordinate
 */
void Point::incrX() 
{
    x++;
}

/**
 * @brief Decrement the first coordinate
 */
void Point::decrX() 
{
    x--;
}

/**
 * @brief Increment the second coordinate
 */
void Point::incrY() 
{
    y++;
}

/**
 * @brief Decrement the seconde coordinate
 */
void Point::decrY() 
{
    y--;
}

/**
 * @brief Increment the third coordinate
 */
void Point::incrZ() 
{
    z++;
}

/**
 * @brief Decrement the third coordinate
 */
void Point::decrZ() 
{
    z--;
}
