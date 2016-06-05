#include "Point.h"
#include <iostream>
#include <cmath>

using namespace std;

/*! 
 * \brief Default constructor
 * Creates a point with all coordinates initialised to 0
 */
Point::Point() : x(0), y(0), z(0) 
{
}

/*! 
 * \brief Constructor
 * Construtor of the class Point
 * 
 * \param int x : first coordinate of the Point
 * \param int y : second coordinate of the Point
 * \param int z : third coordinate of the Point
 */
Point::Point(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z) 
{
    if (x < 0 || x > 8) {
        perror("Index (x) of led out of bounds");
        exit(EXIT_FAILURE);
    }
    if (y < 0 || y > 8) {
        perror("Index (y) of led out of bounds");
        exit(EXIT_FAILURE);
    }
    if (z < 0 || z > 8) {
        perror("Index (z) of led out of bounds");
        exit(EXIT_FAILURE);
    }
}

/*! 
 * \fn bool isOutOfBounds(uint8_t x, uint8_t y, uint8_t z)
 * 
 * \brief Returns if the point is in the cube of size 9 LEDs
 * 
 * \param int x : first coordinate of the Point
 * \param int y : second coordinate of the Point
 * \param int z : third coordinate of the Point
 * 
 * \return true if the point is in the cube 
 * false otherwise
 */
bool Point::isOutOfBounds(uint8_t x, uint8_t y, uint8_t z) 
{
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
 * 
 * \brief Initialises the first coordinate of the Point
 * 
 * \param int x : int to set the coordinate to
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
 * 
 * \brief Initialises the second dimension of the Point
 * 
 * \param int y : int to set the coordinate to
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
 * 
 * \brief Initialises the third dimension of the Point
 * 
 * \param int z : int to set the coordinate to
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

/*! 
 * \fn int getX() const;
 * 
 * \brief Returns x
 * 
 * \return int x  
 */
uint8_t Point::getX() const 
{
    return this->x;
}

/*! 
 * \fn int getY() const;
 * 
 * \brief Returns y
 * 
 * \return int y
 */
uint8_t Point::getY() const 
{
    return this->y;
}

/*! 
 * \fn int getZ() const;
 * 
 * \brief Returns z
 * 
 * \return int z 
 */
uint8_t Point::getZ() const 
{
    return this->z;
}

/*!
 * \fn void print(std::ostream &str) const
 * 
 * \brief Displays the coordinates of the point
 * 
 * \param std::ostream &str : stream on which we write  
 */
void Point::print(std::ostream &str) const 
{
    str << "(" << (int) x << ", " << (int) y << ", " << (int) z << ")";
}

/*!
 * \fn Point& operator=(const Point &p)
 * 
 * \brief Overload of the operator =
 * 
 * \param const Point &p : Point  
 * 
 * \return Point& : Point with all attributes equal to the one of p 
 */
Point& Point::operator=(const Point &p) 
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
 * 
 * \brief Overload of the operator ==
 * 
 * \param Point p : Point we want to compare to 
 * 
 * \return true if the Points are equals
 * false otherwise 
 */
bool Point::operator==(Point p) 
{
    return (this->x == p.getX() &&
            this->y == p.getY() &&
            this->z == p.getZ());
}

/**
 * \fn std::ostream& operator << (std::ostream &out, const Point &p)
 * 
 * \brief Overload of the operator <<
 * 
 * \param std::ostream &out : stream on which we write
 * \param const Point &p : Point to display 
 * 
 * \return std::ostream out
 */
std::ostream& operator<<(std::ostream &out, const Point &p) 
{
    p.print(out);
    return out;
}

/*! 
 * \fn void incrX()
 * 
 * \brief Increments the first coordinate
 */
void Point::incrX() 
{
    x++;
}

/*! 
 * \fn void decrX()
 * 
 * \brief Decrements the first coordinate
 */
void Point::decrX() 
{
    x--;
}

/*! 
 * \fn void incrY()
 * 
 * \brief Increments the second coordinate
 */
void Point::incrY() 
{
    y++;
}

/*! 
 * \fn void decrY()
 * 
 * \brief Decrements the second coordinate
 */
void Point::decrY() 
{
    y--;
}

/*! 
 * \fn void incrZ()
 * 
 * \brief Increments the third coordinate
 */
void Point::incrZ() 
{
    z++;
}

/*! 
 * \fn void decrZ()
 * 
 * \brief Decrements the third coordinate
 */
void Point::decrZ() 
{
    z--;
}

/**
 * \fn Point operator + (const Point &p1, const Point &p2)
 * 
 * \brief Overload of the operator +
 * 
 * \param const Point &p1 : first Point
 * \param const Point &p2 : second Point
 * 
 * \return sum of the two Points
 */
Point operator+(const Point &p1, const Point &p2) 
{
    Point ret(p1.getX() + p2.getX(), p1.getY() + p2.getY(), p1.getZ() + p2.getZ());
    return ret;
} 