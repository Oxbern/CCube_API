#include "ShapeToDisplay.h"

class Cube : public ShapeToDisplay
{
 public:
    Cube(int s = 0, int x = 9, int y = 9, int z = 9, Device *d = new Device("usb", 1),
	 Point p = Point (0,0,0), bool b =  true);
    Cube();
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