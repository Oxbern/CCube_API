#include "DeviceShape.h"
#include "Point.h"

class ShapeToDisplay : public DeviceShape
{
 protected:
    int size;
    Point origin;
    bool full;

 public:
    /**
     * \brief Constructor
     * Constructor of the class ShapeToDisplay
     * If there is no argument given, the device is a cube with a 9 side length
     */
    ShapeToDisplay(int i = 0, int x = 9, int y = 9, int z = 9, 
		   Point p = Point (0, 0, 0), bool b = true);

    /**
     * \brief Destructor
     * Destructor of the class ShapeToDisplay
     */
    ~ShapeToDisplay();

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
};

std::ostream& operator << (std::ostream &Out, ShapeToDisplay &std);
