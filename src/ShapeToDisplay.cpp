#include "ShapeToDisplay.h"
#include "ErrorException.h"
#include "Debug.h"

/*! 
 * \brief Initializes the 3D array at false 
 */
void ShapeToDisplay::initialisation() 
{
    for (int x = 0; x < sizeX; ++x)
        for (int y = 0; y < sizeY; ++y)
            for (int z = 0; z < sizeZ; ++z){
                status[x][y][z] = false;
            }
}

/*! 
 * \brief Constructor
 * Constructor of the class ShapeToDisplay
 */
ShapeToDisplay::ShapeToDisplay(int i, Point p, bool b, int x, int y, int z) :
size(i), origin(p), full(b), sizeX(x), sizeY(y), sizeZ(z) 
{
    LOG(1, "ShapeToDisplay(int i, Point p, bool b, int x, int y, int z)");

    //Allocation
    status = new bool**[sizeX];
    for (int X = 0; X < sizeX; ++X) {
        status[X] = new bool *[sizeY];
        for (int Y = 0; Y < sizeY; ++Y)
            status[X][Y] = new bool [sizeZ];
    }

    // initialisation
    initialisation();
}

/*!
 * \brief Destructor
 * Destructor of the class ShapeToDisplay
 */
ShapeToDisplay::~ShapeToDisplay() 
{
    LOG(1, "~ShapeToDisplay()");

    //Deallocation
    if (status != NULL) {
        for (int x = 0; x < sizeX; ++x) {
            for (int y = 0; y < sizeY; ++y) {
                delete[] status[x][y];
            }
            delete[] status[x];
        }
        delete[] status;
        status = NULL;
    }
}

/*! 
 * \brief Prints the array
 */
void ShapeToDisplay::print(std::ostream &str) 
{
    if (full)
        str << "This is a full shape :" << std::endl;
    else
        str << "This is an empty shape :" << std::endl;
    str << "Size : " << size << std::endl;
    str << "Origin : " << origin << std::endl;
    str << "3D array of size " << sizeX << ", " << sizeY << ", " << sizeZ << std::endl;

    for (int z = 0; z < sizeZ; ++z) {
        str << "Z = " << z << std::endl;
        for (int y = 0; y < sizeY; ++y) {
            str << "Y = " << y << std::endl;
            for (int x = 0; x < sizeX; ++x) {
                if (status[x][y][z])
                    str << "1 ";
                else
                    str << "0 ";
            }
            str << std::endl;
        }
        str << std::endl;
    }
}

/*!
 * \brief Overloads of the operator <<
 * @param Out  stream on which we write
 * @param std  ShapeToDisplay we want to display
 * \return std::ostream Out stream we wrote on
 */
std::ostream& operator<<(std::ostream &out, ShapeToDisplay &std) 
{
    std.print(out);
    return out;
}

/*! 
 * \brief Increases the size of the shape 
 * \return true if the size is not bigger than the 3D array dimensions 
 * false otherwise
 */
bool ShapeToDisplay::incrSize() 
{
    size++;
    if (size > sizeX || size > sizeY || size > sizeZ) {
        std::cout << "size bigger than device dimensions" << std::endl;
        std::cout << "size = " << size << std::endl;
        std::cout << "sizeX = " << sizeX
                << ", sizeY = " << sizeY
                << ", sizeZ = " << sizeZ << std::endl;
        size--;
        return false;
    }
    return true;
}

/*! 
 * \brief Decreases the size of the shape 
 * \return true if the size does not become negative
 * false otherwise
 */
bool ShapeToDisplay::decrSize()
{
    size--;
    if (size < 0) {
        std::cout << "negative size" << std::endl;
        return false;
    }
    return true;
}

/*! 
 * \brief Returns the 3D array
 * \return bool ***status
 */
bool *** ShapeToDisplay::getStatus() 
{
    return this->status;
}

/*! 
 * \brief Changes the status of the cell of the array at true
 * \param x first coordinate of the cell
 * \param y second coordinate of the cell
 * \param z third coordinate of the cell
 * \return true if the parameters are in the 3D array
 * false otherwise
 */
bool ShapeToDisplay::on(int x, int y, int z) 
{
    if (x > (sizeX - 1) || y > (sizeY - 1) || z > (sizeZ - 1))
        throw ErrorException("Index of led out of bounds");

    return (status[x][y][z] = true);
}

/*! 
 * \brief Sets all the cell to false
 */
void ShapeToDisplay::off() 
{
    initialisation();
}

/*! 
 * \brief Returns sizeX
 * \return int sizeX  
 */
int ShapeToDisplay::getSizeX() const 
{
    return sizeX;
}

/*! 
 * \brief Returns sizeY
 * \return int sizeY
 */
int ShapeToDisplay::getSizeY() const 
{
    return sizeY;
}

/*! 
 * \brief Returns sizeZ
 * \return int sizeZ
 */
int ShapeToDisplay::getSizeZ() const 
{
    return sizeZ;
}
