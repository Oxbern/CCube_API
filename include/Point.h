#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#include <iostream>

/*!
 * \class Point
 * \brief Defines a 3D point
 */
class Point
{
 private: 
    uint8_t x; /*!< First coordinate of the point */
    uint8_t y; /*!< Second coordinate of the point */
    uint8_t z; /*!< Third coordinate of the point */

 public:
     /*! 
     * \brief Default constructor
     * Creates a point with all coordinates initialised to 0
     */
    Point();

    /*! 
     * \brief Constructor
     * Construtor of the class Point
     * 
     * \param int x : first coordinate of the Point
     * \param int y : second coordinate of the Point
     * \param int z : third coordinate of the Point
     */
    Point(uint8_t x, uint8_t y, uint8_t z);

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
    bool isOutOfBounds(uint8_t x, uint8_t y, uint8_t z);
  
    /*! 
     * \fn void setX(int x)
     * 
     * \brief Initialises the first coordinate of the Point
     * 
     * \param int x : int to set the coordinate to
     */
    void setX(int x);

    /*! 
     * \fn void setY(int y)
     * 
     * \brief Initialises the second dimension of the Point
     * 
     * \param int y : int to set the coordinate to
     */
    void setY(int y);

    /*! 
     * \fn void setZ(int z)
     * 
     * \brief Initialises the third dimension of the Point
     * 
     * \param int z : int to set the coordinate to
     */
    void setZ(int z);

    /*! 
     * \fn void incrX()
     * 
     * \brief Increments the first coordinate
     */
    void incrX();

    /*! 
     * \fn void incrY()
     * 
     * \brief Increments the second coordinate
     */
    void incrY();

    /*! 
     * \fn void incrZ()
     * 
     * \brief Increments the third coordinate
     */
    void incrZ();
    
    /*! 
     * \fn void decrX()
     * 
     * \brief Decrements the first coordinate
     */
    void decrX();

    /*! 
     * \fn void decrY()
     * 
     * \brief Decrements the second coordinate
     */
    void decrY();

    /*! 
     * \fn void decrZ()
     * 
     * \brief Decrements the third coordinate
     */    
    void decrZ();

    /*! 
     * \fn int getX() const;
     * 
     * \brief Returns x
     * 
     * \return int x  
     */
    uint8_t getX() const;
    
    /*! 
     * \fn int getY() const;
     * 
     * \brief Returns y
     * 
     * \return int y
     */
    uint8_t getY() const;
    
    /*! 
     * \fn int getZ() const;
     * 
     * \brief Returns z
     * 
     * \return int z 
     */
    uint8_t getZ() const;
    
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
    bool operator==(Point p);

    /*!
     * \fn Point& operator=(const Point &p)
     * 
     * \brief Overload of the operator =
     * 
     * \param const Point &p : Point  
     * 
     * \return Point& : Point with all attributes equal to the one of p 
     */
    Point& operator=(const Point &p);
  
    /*!
     * \fn void print(std::ostream &str) const
     * 
     * \brief Displays the coordinates of the point
     * 
     * \param std::ostream &str : stream on which we write  
     */    
    void print(std::ostream &str) const;
};

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
std::ostream& operator << (std::ostream &out, const Point &p);

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
Point operator + (const Point &p1, const Point &p2);
    
#endif
