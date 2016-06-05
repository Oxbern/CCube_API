#ifndef POINT_H
#define POINT_H

/*!
 * \file Point.h
 * \brief TODO
 * \version 0.1
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#include <iostream>

/*!
 * \class Point
 * \brief TODO
 */
class Point
{
 private: 
    uint8_t x; /*!< TODO */
    uint8_t y; /*!< TODO */
    uint8_t z; /*!< TODO */

 public:
    /*!
     * \brief Default constructor
     *
     * Creates a point of dimension 3 and coordinates x = 0, y = 0, z = 0 
     */       
    Point();
    
    /*!
     * \brief Constructor
     *
     * Creates a point for a cube of 9 by 9 by 9 LEDs
     *
     * \param x first coordinate
     * \param y second coordinate
     * \param z third coordinate
     */           
    Point(uint8_t x, uint8_t y, uint8_t z);


    /*!
     * \brief Destructor
     */
    //    ~Point();

    /*!
     * \fn bool isOutOfBounds(uint8_t x, uint8_t y, uint8_t z)
     * \brief Checks if the point is in the cube
     * \param x first coordinate
     * \param y second coordinate
     * \param z third coordinate
     * \return 
     */
    bool isOutOfBounds(uint8_t x, uint8_t y, uint8_t z);

    /*!
     * \fn void setX(int x)
     * \brief Sets the first coordinate
     * \param x value
     */    
    void setX(int x);

    /*!
     * \fn void setY(int y)
     * \brief Sets the second coordinate
     * \param y value
     */
    void setY(int y);

    /*!
     * \fn void setZ(int z)
     * \brief Sets the third coordinate
     * \param z value
     */
    void setZ(int z);
  
    void incrX();
    void incrY();
    void incrZ();
    void decrX();
    void decrY();
    void decrZ();

    uint8_t getX() const;
    uint8_t getY() const;
    uint8_t getZ() const;

    /*!
     * \fn bool operator==(Point p)
     * \brief Overload of the operator ==
     * \param p : Point to compare with 
     * \return boolean
     */    
    bool operator==(Point p);

    /*!
     * \fn Point& operator=(const Point &p)
     * \brief Overload of the operator =
     * \param p  Point 
     * \return Point
     */    
    Point& operator=(const Point &p);

    /*!
     * \fn void print(std::ostream &str) const
     * \brief Prints the attributes of the point
     * \param str  stream on which we write
     */  
    void print(std::ostream &str) const;
};

/*!
 * \fn std::ostream& operator << (std::ostream &out, const Point &p)
 * \brief Overload of the operator <<
 * \param str  stream on which we write
 * \param p  Point we want to display 
 * \return std::ostream out
 */
std::ostream& operator << (std::ostream &out, const Point &p);

Point operator + (const Point &p1, const Point &p2);
    
#endif
