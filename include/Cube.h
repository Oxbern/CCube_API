#include "ShapeToDisplay.h"

class Cube : public ShapeToDisplay
{
 public:
    Cube(int s = 0, int x = 9, int y = 9, int z = 9, 
	 Point p = Point (0,0,0), bool b =  true);
    Cube();
    ~Cube();

    void print(std::ostream &str) const;

    void init();

    bool incrSize();
    bool decrSize();

    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();
    bool moveForward();
    bool moveBackward();


};

