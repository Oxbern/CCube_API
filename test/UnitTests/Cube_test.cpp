#include "Cube.h"

bool arrayCompare(bool ***first, bool ***second, int sizeX, int sizeY, int sizeZ)
{
    for (int x = 0; x < sizeX; x++)
        for (int y = 0; y < sizeY; y++)
            for (int z = 0; z < sizeZ; z++)
                if (first[x][y][z] != second[x][y][z])
                    return false;
    return true;
}

int main(int argc, char* argv[])
{
    int size = 5;
    Point p(0, 0, 0);
    bool full = true;
    int sizeX = 9;
    int sizeY = 9;
    int sizeZ = 9;
    
    Cube c(size, p, full, sizeX, sizeY, sizeZ);

    int X = sizeX;
    int Y = sizeY;
    int Z = sizeZ;
    
    bool ***cmp = new bool**[c.getSizeX()];
    for (int x = 0; x < X; ++x) {
        cmp[x] = new bool *[c.getSizeY()];
        for (int y = 0; y < Y; ++y)
            cmp[x][y] = new bool [c.getSizeZ()];
    }

    /* TEST 1 : Full c ube of size 5 and from the origin (0, 0, 0) */

    for (int x = 0; x < X; x++)
        for (int y = 0; y < Y; y++)
            for (int z = 0; z < Z; z++)
                if (x < 5 && y < 5 && z < 5)
                    cmp[x][y][z] = true;
                else
                    cmp[x][y][z] = false;


    if (arrayCompare(c.getStatus(), cmp, X, Y, Z))
        std::cout << "Test 1 : PASSED" << std::endl;

    else
        perror("Test 1 : FAILED");

    /* TEST 2 : Try to go down */

    if (!c.moveDown())
        std::cout << "Test 2 : PASSED" << std::endl;
    else
        perror("Test 2 : FAILED");

    /* TEST 3 : Try to go left */

    if (!c.moveLeft())
        std::cout << "Test 3 : PASSED" << std::endl;
    else
        perror("Test 3 : FAILED");

    /* TEST 4 : Increase size */
    if (!c.incrSize())
        perror("Test 3 : FAILED");

            
            
    std::cout << "Test 3 : PASSED" << std::endl;

    /*
      for (int i = 0; i < 10; i++)
      if (c.moveRight()) {
      std::cout << "Right number " << (int) (i + 1) << std::endl;
      c.print(std::cout);
      }

      for (int i = 0; i < 5; i++) {
      std::cout << "Up number " << (int) (i + 1) << std::endl;
      if (c.moveUp()) {
      c.print(std::cout);
      }
      }


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
    */

    for (int x = 0; x < c.getSizeX(); ++x) {
        for (int y = 0; y < c.getSizeY(); ++y) {
            delete[] cmp[x][y];
        }
        delete[] cmp[x];
    }
    delete[] cmp;

    return 0;
}
