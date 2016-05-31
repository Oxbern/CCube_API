#include "ShapeToDisplay.h"

/**
 * \class Cube
 * \brief Class describing a cube (a shape which can be displayed on the device)
 */
class Cube : public ShapeToDisplay
{
 public:
    Cube(int i = 0, Point p = Point (0, 0, 0), bool b = true, 
            int x = 9, int y = 9, int z = 9);
    
    virtual ~Cube();

    void init();

    bool incrSize();
    bool decrSize();

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();
    bool moveForward();
    bool moveBackward();

    void print(std::ostream &str);
};

// std::ostream& operator<<(std::ostream &out, Cube &c);
