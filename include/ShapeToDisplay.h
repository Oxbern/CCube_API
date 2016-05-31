#include "DeviceShape.h"
#include "Point.h"
#include "Device.h"

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
     * \brief Debug function. Print the matrix of ds
     */
    void print(std::ostream &str);

    virtual bool incrSize();
    virtual bool decrSize();

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();
    bool moveForward();
    bool moveBackward();

    bool ***getStatus();

    void initialisation();

    bool on(int x, int y, int z);
    bool off();
    
    int getSizeX() const;
    int getSizeY() const;
    int getSizeZ() const;
};

std::ostream& operator<<(std::ostream &Out, ShapeToDisplay &std);
