#include "Cube.h"
#include <sstream>

/*! 
 * \brief Constructor
 *
 * Constructor of the class Cube
 *
 * \param i
 * \param p 
 * \param b
 * \param x
 * \param y
 * \param z
 */
Cube::Cube(int i, Point p, bool b, int x, int y, int z) :
    ShapeToDisplay(i, p, b, x, y, z) 
{
    LOG(1, "Cube(int i, Point p, bool b, bool ***s, int x, int y, int z)");
    init();
}

/*!
 * \fn void init()
 * \brief Function that initialises the device depending 
 * on the parameters of the shape (the cube here)
 */
void Cube::init() 
{
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            for (int z = 0; z < sizeZ; z++) {
                if (full) {
                    if (x >= origin.getX() && x < origin.getX() + size
                            && y >= origin.getY() && y < origin.getY() + size
                            && z >= origin.getZ() && z < origin.getZ() + size)
                        on(x, y, z);
                } else
                    if (x == origin.getX() || x == origin.getX() + size - 1
                        || y == origin.getY() || y == origin.getY() + size - 1
                        || z == origin.getZ() || z == origin.getZ() + size - 1)
                    on(x, y, z);
            }
        }
    }
}

/*!
 * \brief Destructor
 * Destructor of the class ShapeToDisplay
 */
Cube::~Cube() 
{
    LOG(1, "~Cube()");
}

/*! 
 * \fn virtual bool incrSize()
 * \brief Increases the size of the shape 
 * \return true if the bigger cube stays in the 3D array 
 * false otherwise
 */
bool Cube::incrSize() 
{
    int X = origin.getX() + size;
    int Y = origin.getY() + size;
    int Z = origin.getZ() + size;

    std::stringstream s;

    s << "X = " << X << ", Y = " << Y << ", Z = " << Z;

    LOG(1, s.str());

    if (origin.getX() + size == 9
            || origin.getY() + size == 9
            || origin.getZ() + size == 9) {
        std::cout << "Cube size cannot increase more" << std::endl;
        return false;
    }
    size++;
    off();
    init();
    return true;
}

/*! 
 * \fn virtual bool decrSize()
 * \brief Decreases the size of the shape 
 * \return true if the size does not become negative
 * false otherwise
 */
bool Cube::decrSize() 
{
    if (size == 0) {
        std::cout << "Cube size cannot decrease more" << std::endl;
        return false;
    }
    size--;
    off();
    init();
    return true;
}

/*! 
 * \fn bool moveUp()
 * \brief Moves the cube up in the 3D array 
 * \return true if the whole cube stays in the 3D array
 * false otherwise
 */
bool Cube::moveUp() 
{
    if (origin.getZ() + size < 9) {
        off();
        origin.incrZ();
        init();
        return true;
    } else {
        std::cout << "Cannot go higher" << std::endl;
        return false;
    }
}

/*! 
 * \fn bool moveDown()
 * \brief Moves the cube down in the 3D array 
 * \return true if the whole cube stays in the 3D array
 * false otherwise
 */
bool Cube::moveDown() 
{
    if (origin.getZ() > 0) {
        off();
        origin.decrZ();
        init();
        return true;
    } else {
        std::cout << "Cannot go deeper" << std::endl;
        return false;
    }
}

/*! 
 * \fn bool moveLeft()
 * \brief Moves the cube on the left in the 3D array 
 * \return true if the whole cube stays in the 3D array
 * false otherwise
 */
bool Cube::moveLeft() 
{
    if (origin.getY() > 0) {
        off();
        origin.decrY();
        init();
        return true;
    } else {
        std::cout << "Cannot move more on the left" << std::endl;
        return false;
    }
}

/*! 
 * \fn bool moveRight()
 * \brief Moves the cube on the right in the 3D array 
 * \return true if the whole cube stays in the 3D array
 * false otherwise
 */
bool Cube::moveRight()
{
    if (origin.getY() + size < 9) {
        off();
        origin.incrY();
        init();
        return true;
    } else {
        std::cout << "Cannot move more on the right" << std::endl;
        return false;
    }
}

/*! 
 * \fn bool moveForward()
 * \brief Moves the cube forward in the 3D array 
 * \return true if the whole cube stays in the 3D array
 * false otherwise
 */
bool Cube::moveForward() 
{
    if (origin.getX() + size < 9) {
        off();
        origin.incrX();
        init();
        return true;
    } else {
        std::cout << "Cannot move more forward" << std::endl;
        return false;
    }
}

/*! 
 * \fn bool moveBackward()
 * \brief Moves the cube backward in the 3D array 
 * \return true if the whole cube all stays in the 3D array
 * false otherwise
 */
bool Cube::moveBackward() 
{
    if (origin.getX() > 0) {
        off();
        origin.decrX();
        init();
        return true;
    } else {
        std::cout << "Cannot move more backward" << std::endl;
        return false;
    }
}

/*! 
 * \fn void print(std::ostream &str)
 * \brief Calls the print function of the superclass (ShapeToDisplay)
 */
void Cube::print(std::ostream &str) 
{
    ShapeToDisplay::print(str);
}

/*!
 * \fn std::ostream& operator<<(std::ostream &out, Cube &c)
 * \brief Overloads of the operator <<
 * @param out : stream on which we write
 * @param c : Cube shape we want to display
 * \return std::ostream Out
 */
std::ostream& operator<<(std::ostream &out, Cube &c) 
{
    c.print(out);
    return out;
}
