#include "Cube.h"
#include <assert.h> 
#include "DeviceShape.h"

bool arrayEqual(bool ***first, bool ***second, int sizeX, int sizeY, int sizeZ)
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



    assert(arrayEqual(c.getStatus(), cmp, X, Y, Z));

    /* TEST 2 : Try to go down */

    assert(!c.moveDown());

    /* TEST 3 : Try to go left */

    assert(!c.moveLeft());

    /* TEST 4 : Increase size */
    assert(c.incrSize());          
            
    for (int x = 0; x < c.getSizeX(); ++x) {
        for (int y = 0; y < c.getSizeY(); ++y) {
            delete[] cmp[x][y];
        }
        delete[] cmp[x];
    }
    delete[] cmp;
    
    DeviceShape ds;
    ds.copyLedStatus(c);
    
    assert(arrayEqual(c.getStatus(), ds.getLedStatus(), X, Y, Z));
    
    std::cout << "Test : PASSED" << std::endl;
    
    return EXIT_SUCCESS;
}
