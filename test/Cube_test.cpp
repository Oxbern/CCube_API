#include "Cube.h"

int main(int argc, char* argv[]) {
    Point p(0, 0, 0);
    Cube c(5, 9, 9, 9, p);

    std::cout << "Start" << std::endl;
    c.print(std::cout);

    if (c.moveDown()) {
        std::cout << "Down" << std::endl;
        c.print(std::cout);
    }

    if (c.moveLeft()) {
        std::cout << "Left" << std::endl;
        c.print(std::cout);
    }

    /* for (int i = 0; i < 10; i++)
        if (c.moveRight())
            {
                std::cout << "Right number " << (int) (i + 1) << std::endl;
                c.print(std::cout);
            }

    for (int i = 0; i < 5; i++) {
        std::cout << "Up number " << (int) (i + 1) << std::endl;
        if (c.moveUp()) {
            c.print(std::cout);
        }
    }
     */

    std::cout << "INCREASE" << std::endl;
    c.decrSize();
    c.print(std::cout);

    std::cout << "***********************************************" << std::endl;
    c.decrSize();
    c.print(std::cout);
    std::cout << "***********************************************" << std::endl;
    c.decrSize();
    c.print(std::cout);
    std::cout << "***********************************************" << std::endl;
    c.decrSize();
    c.print(std::cout);
    
    std::cout << "***********************************************" << std::endl;
    c.decrSize();
    c.print(std::cout);
    
    c.decrSize();

    return 0;
}
