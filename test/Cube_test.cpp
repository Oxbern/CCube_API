#include "Cube.h"

int main(int argc, char* argv[]) 
{
    Point p(0,0,0);
    Cube c(5,9,9,9, p);
    
    std::cout << "Start" << std::endl;
    c.print(std::cout);

    if (c.moveDown())
	{
	    std::cout << "Down" << std::endl;
	    c.print(std::cout);
	}

    if (c.moveLeft())
	{
	    std::cout << "Down" << std::endl;
	    c.print(std::cout);
	}

    for (int i = 0; i < 10; i++)
        if (c.moveRight())
            {
                std::cout << "Down" << std::endl;
                c.print(std::cout);
            }
    
    return 0;
}
