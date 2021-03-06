#ifndef CUBE_H
#define CUBE_H
/*!
 * \file Cube.h
 * \brief Class for demo
 * \version 0.1
 */
#include "ShapeToDisplay.h"

/*!
 * \class Cube
 * \brief Class describing a cube (a shape which can be displayed on the device)
 */
class Cube : public ShapeToDisplay
{
public:
    /*! 
     * \brief Constructor
     *
     * Constructor of the class Cube
     *
     * \param i size of the Cube
     * \param p origin (back lower left corner)
     * \param b if the cube is full or not
     * \param x first size of the device we displayed it on
     * \param y second size of the device we displayed it on
     * \param z third size of the device we displayed it on
     */
    Cube(int i = 0, Point p = Point(0, 0, 0), bool b = true,
            int x = 9, int y = 9, int z = 9);

    /*!
     * \brief Destructor
     * Destructor of the class ShapeToDisplay
     */
    virtual ~Cube();

    /*!
     * \fn void init()
     * \brief Initialises the device depending 
     * on the parameters of the shape (the cube here)
     */
    void init();

    /*! 
     * \fn virtual bool incrSize()
     * \brief Increases the size of the shape 
     * \return true if the bigger cube stays in the 3D array 
     * false otherwise
     */
    bool incrSize();

    /*! 
     * \fn virtual bool decrSize()
     * \brief Decreases the size of the shape 
     * \return true if the size does not become negative
     * false otherwise
     */
    bool decrSize();

    /*! 
     * \fn bool moveUp()
     * \brief Moves the cube up in the 3D array 
     * \return true if the whole cube stays in the 3D array
     * false otherwise
     */
    bool moveUp();

    /*! 
     * \fn bool moveDown()
     * \brief Moves the cube down in the 3D array 
     * \return true if the whole cube stays in the 3D array
     * false otherwise
     */
    bool moveDown();

    /*! 
     * \fn bool moveLeft()
     * \brief Moves the cube on the left in the 3D array 
     * \return true if the whole cube stays in the 3D array
     * false otherwise
     */
    bool moveLeft();

    /*! 
     * \fn bool moveRight()
     * \brief Moves the cube on the right in the 3D array 
     * \return true if the whole cube stays in the 3D array
     * false otherwise
     */
    bool moveRight();

    /*! 
     * \fn bool moveForward()
     * \brief Moves the cube forward in the 3D array 
     * \return true if the whole cube stays in the 3D array
     * false otherwise
     */
    bool moveForward();

    /*! 
     * \fn bool moveBackward()
     * \brief Moves the cube backward in the 3D array 
     * \return true if the whole cube all stays in the 3D array
     * false otherwise
     */
    bool moveBackward();

    /*! 
     * \fn void print(std::ostream &str)
     * \brief Calls the print function of the superclass (ShapeToDisplay)
     */
    void print(std::ostream &str);
};

/*!
 * \fn std::ostream& operator<<(std::ostream &out, Cube &c)
 * \brief Overloads of the operator <<
 * \param out stream on which we write
 * \param c Cube shape we want to display
 * \return out (stream on which we wrote)
 */
std::ostream& operator<<(std::ostream &out, Cube &c);

#endif
