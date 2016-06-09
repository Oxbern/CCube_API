#ifndef SHAPETODISPLAY_H
#define SHAPETODISPLAY_H

/*!
 * \file ShapeToDisplay.h
 * \brief Creates a shape which can be displayed on a device
 * \version 0.1
 */
#include "Point.h"

/*!
 * \class ShapeToDisplay
 * \brief Parent class for all shapes which will be displayed on the device
 */
class ShapeToDisplay {
protected:
    int size; /*!< Size of the shape (radius for a sphere, length for a cube) */
    Point origin; /*!< Origin of the shape (center for a sphere, lower left back
                   *  corner for a cube) */
    bool full; /*!< Indicates if the shape is full or empty */
    bool ***status; /*!< 3D array on which the shape is drawn */
    int sizeX; /*!< First dimension of the array */
    int sizeY; /*!< Second dimension of the array */
    int sizeZ; /*!< Third dimension of the array */

public:
    /*! 
     * \brief Constructor
     * Constructor of the class ShapeToDisplay
     */
    ShapeToDisplay(int i = 0, Point p = Point(0, 0, 0), bool b = true, int x = 9,
            int y = 9, int z = 9);

    /*!
     * \brief Destructor
     * Destructor of the class ShapeToDisplay
     */
    virtual ~ShapeToDisplay();


    void print(std::ostream &str);

    /*! 
     * \fn virtual bool incrSize()
     * \brief Increases the size of the shape 
     * \return true if the size is not bigger than the 3D array dimensions 
     * false otherwise
     */
    virtual bool incrSize();

    /*! 
     * \fn virtual bool decrSize()
     * \brief Decreases the size of the shape 
     * \return true if the size does not become negative
     * false otherwise
     */
    virtual bool decrSize();

    /*! 
     * \fn bool moveUp()
     * \brief Moves the shape up in the 3D array 
     * function only described in the inherited classes
     * \return true if the whole shape stays in the 3D array
     * false otherwise
     */
    bool moveUp();

    /*! 
     * \fn bool moveDown()
     * \brief Moves the shape down in the 3D array
     * function only described in the inherited classes
     * \return true if the whole shape stays in the 3D array
     * false otherwise
     */
    bool moveDown();

    /*! 
     * \fn bool moveLeft()
     * \brief Moves the shape on the left in the 3D array 
     * function only described in the inherited classes
     * \return true if the whole shape stays in the 3D array
     * false otherwise
     */
    bool moveLeft();

    /*! 
     * \fn bool moveRight()
     * \brief Moves the shape on the right in the 3D array 
     * function only described in the inherited classes
     * \return true if the whole shape stays in the 3D array
     * false otherwise
     */
    bool moveRight();

    /*! 
     * \fn bool moveForward()
     * \brief Moves the shape forward in the 3D array 
     * function only described in the inherited classes
     * \return true if the whole shape stays in the 3D array
     * false otherwise
     */
    bool moveForward();

    /*! 
     * \fn bool moveBackward()
     * \brief Moves the shape backward in the 3D array
     * function only described in the inherited classes
     * \return true if the whole shape stays in the 3D array
     * false otherwise
     */
    bool moveBackward();

    /*! 
     * \fn bool ***getStatus()
     * \brief Returns the 3D array
     * \return bool ***status
     */
    bool ***getStatus();

    /*! 
     * \fn void initialisation()
     * \brief Initializes the 3D array at false 
     */
    void initialisation();

    /*! 
     * \fn bool on(int x, int y, int z)
     * \brief Changes the status of the cell of the array at true
     * \param x first coordinate of the cell
     * \param y second coordinate of the cell
     * \param z third coordinate of the cell
     * \return true if the parameters are in the 3D array
     * false otherwise
     */
    bool on(int x, int y, int z);
    
    /*! 
     * \fn void off();
     * \brief Sets all the cell to false
     */
    void off();
    
    /*! 
     * \fn int getSizeX() const;
     * \brief Returns sizeX
     * \return int sizeX  
     */
    int getSizeX() const;

    /*! 
     * \fn int getSizeY() const;
     * \brief Returns sizeY
     * \return int sizeY
     */
    int getSizeY() const;

    /*! 
     * \fn int getSizeZ() const;
     * \brief Returns sizeZ
     * \return int sizeZ
     */
    int getSizeZ() const;
};

/*!
 * \fn std::ostream& operator<<(std::ostream &Out, ShapeToDisplay &std);
 * \brief Overloads of the operator <<
 * @param out  stream on which we write
 * @param std  ShapeToDisplay we want to display
 * \return std::ostream Out stream we wrote on
 */
std::ostream& operator<<(std::ostream &Out, ShapeToDisplay &std);

#endif
