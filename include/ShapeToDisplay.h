#ifndef SHAPETODISPLAY_H
#define SHAPETODISPLAY_H

#include "Point.h"
#include "Debug.h"


/**
 * \class ShapeToDisplay
 * \brief Parent class for all shapes which will be displayed on the device
 */
class ShapeToDisplay {
protected:
    int size; /**< Size of the shape (radius for a sphere, length for a cube) */
    Point origin; /**< Origin of the shape (center for a sphere, lower left back
                   *  corner for a cube) */
    bool full; /**< Indicate if the shape is full or empty */
    bool ***status; /**< 3D array on which the shape is drawn */
    int sizeX; /**< First dimension of the array */
    int sizeY; /**< Second dimension of the array */
    int sizeZ; /**< Third dimension of the array */

public:
    /** 
     * \brief Constructor
     * Constructor of the class ShapeToDisplay
     */
    ShapeToDisplay(int i = 0, Point p = Point(0, 0, 0), bool b = true, int x = 9,
            int y = 9, int z = 9);

    /**
     * \brief Destructor
     * Destructor of the class ShapeToDisplay
     */
    virtual ~ShapeToDisplay();

    /** 
     * \fn void ShapeToDisplay::print(std::ostream &str)
     * \brief Prints the array
     */
    void print(std::ostream &str);

    /** 
     * \fn virtual bool incrSize()
     * \brief Increases the size of the shape 
     */
    virtual bool incrSize();
    
    /** 
     * \fn virtual bool decrSize()
     * \brief Decreases the size of the shape 
     */
    virtual bool decrSize();

    /** 
     * \fn bool moveUp()
     * \brief Move the shape up in the 3D array 
     */
    bool moveUp();

    /** 
     * \fn bool moveDown()
     * \brief Move the shape down in the 3D array 
     */
    bool moveDown();

    /** 
     * \fn bool moveLeft()
     * \brief Move the shape on the left in the 3D array 
     */
    bool moveLeft();

    /** 
     * \fn bool moveRight()
     * \brief Move the shape on the right in the 3D array 
     */
    bool moveRight();

    /** 
     * \fn bool moveForward()
     * \brief Move the shape forward in the 3D array 
     */
    bool moveForward();

    /** 
     * \fn bool moveBackward()
     * \brief Move the shape backward in the 3D array 
     */
    bool moveBackward();

    /** 
     * \fn bool ***getStatus()
     * \brief Returns the 3D array
     * \return bool ***status
     */
    bool ***getStatus();

    /** 
     * \fn void initialisation()
     * \brief Initializes the 3D array at false 
     */
    void initialisation();

    /** 
     * \fn bool on(int x, int y, int z)
     * \brief Changes the status of the cell of the array at true
     * \param int x, int y, int z : coordinates in the 3D array   
     * \return true if the parameters are in the 3D array
     * false otherwise
     */
    bool on(int x, int y, int z);
    
    /** 
     * \fn void off();
     * \brief Sets all the cell to false
     */
    void off();
    
    /** 
     * \fn int getSizeX() const;
     * \brief Returns sizeX
     * \return int sizeX  
     */
    int getSizeX() const;

    /** 
     * \fn int getSizeY() const;
     * \brief Returns sizeY
     * \return int sizeY
     */
    int getSizeY() const;

    /** 
     * \fn int getSizeZ() const;
     * \brief Returns sizeZ
     * \return int sizeZ
     */
    int getSizeZ() const;
};

/** 
 * \fn std::ostream& operator<<(std::ostream &Out, ShapeToDisplay &std);
 * \brief Overloads of the operator <<
 * @param Out : stream on which we write
 * @param std : ShapeToDisplay we want to display
 * \return std::ostream Out
 */
std::ostream& operator<<(std::ostream &Out, ShapeToDisplay &std);

#endif