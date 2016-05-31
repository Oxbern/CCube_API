#include "DeviceShape.h"
#include "Point.h"
#include "Device.h"

/**
 * \class ShapeToDisplay
 * \brief Parent class for all shapes which will be displayed on the device
 */
class ShapeToDisplay
{
 protected:
    int size; /**< Size of the shape (radius for a sphere, length for a cube) */
    Point origin; /**< Origin of the shape (center for a sphere, lower left back
                   *  corner for a cube) */
    bool full; /**< Indicate if the shape is full or empty */
    Device *device; /** device on which the shape will be displayed */

 public:
    /** 
     * \brief Constructor
     * Constructor of the class ShapeToDisplay
     * If there is no argument given, the device is a cube with a 9 side length
     */
    ShapeToDisplay(int i = 0, Device *d = new Device("usb", 1),
		   Point p = Point (0, 0, 0), bool b = true);

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
    
    Device * getDevice() const;
};

std::ostream& operator << (std::ostream &Out, ShapeToDisplay &std);
