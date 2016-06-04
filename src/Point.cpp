#include "Point.h"
#include <iostream>
#include <cmath>

    /*!
     * \brief Default constructor
     *
     * Creates a point of dimension 3 and coordinates x = 0, y = 0, z = 0 
     */       
Point::Point() : x(0), y(0), z(0)
{
}

    /*!
     * \brief Constructor
     *
     * Creates a point for a cube of 9 by 9 by 9 LEDs
     *
     * \param x first coordinate
     * \param y second coordinate
     * \param z third coordinate
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

    /*!
     * \fn bool isOutOfBounds(uint8_t x, uint8_t y, uint8_t z)
     * \brief Checks if the point is in the cube
     * \param x first coordinate
     * \param y second coordinate
     * \param z third coordinate
     * \return 
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

    /*!
     * \fn void setX(int x)
     * \brief Sets the first coordinate
     * \param x value
     */    
void Point::setX(int x)
{
    //if (x >= 0 && x < 9)
	this->x = x;
    //else{
//	perror("Index (x) of led out of bounds");
  //      std::cout << "x = " << (int) x << std::endl;
//	exit(EXIT_FAILURE);
    //}
}

    /*!
     * \fn void setY(int y)
     * \brief Sets the second coordinate
     * \param y value
     */
void Point::setY(int y)
{
  //  if (y >= 0 && y < 9)
	this->y = y;
    //else{
	//perror("Index (y) of led out of bounds");
       // std::cout << "y = " << (int) y << std::endl;
	//exit(EXIT_FAILURE);
    //}
}

    /*!
     * \fn void setZ(int z)
     * \brief Sets the third coordinate
     * \param z value
     */
void Point::setZ(int z)
{
//    if (z >= 0 && z < 9)
	this->z = z;
//    else{
//	perror("Index (z) of led out of bounds");
//        std::cout << "z = " << (int) z << std::endl;
//	exit(EXIT_FAILURE);
//    }
}

uint8_t Point::getX() const
{
    return this->x;
}

uint8_t Point::getY() const
{
    return this->y;
} 

uint8_t Point::getZ() const
{
    return this->z;
}

/*!
 * \fn void print(std::ostream &str) const
 * \brief Prints the attributes of the point
 * \param str  stream on which we write
 */
void Point::print(std::ostream &str) const
{
    str << "(" << (int) x << ", " << (int) y << ", " << (int) z << ")";
}

/*!
 * \fn Point& operator=(const Point &p)
 * \brief Overload of the operator =
 * \param p  Point 
 * \return Point
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

/*!
 * \fn bool operator==(Point p)
 * \brief Overload of the operator ==
 * \param p : Point to compare with 
 * \return boolean
 */
bool Point::operator== (Point p)
{
    return (this->x == p.getX() &&
     	    this->y == p.getY() &&
    	    this->z == p.getZ());
}

/*!
 * \fn std::ostream& operator << (std::ostream &out, const Point &p)
 * \brief Overload of the operator <<
 * \param str  stream on which we write
 * \param p  Point we want to display 
 * \return std::ostream out
 */
std::ostream& operator << (std::ostream &out, const Point &p)
{
    p.print(out);
    return out;
}

void Point::incrX() 
{
    x++;
}

void Point::decrX() 
{
    x--;
}

void Point::incrY() 
{
    y++;
}

void Point::decrY() 
{
    y--;
}

void Point::incrZ() 
{
    z++;
}

void Point::decrZ() 
{
    z--;
}

Point operator + (const Point &p1, const Point &p2)
{
    Point ret(p1.getX() + p2.getX(), p1.getY() + p2.getY(), p1.getZ() + p2.getZ());
    return ret;
} 
