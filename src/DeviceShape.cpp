#include <cmath>
#include <string.h>
#include <ErrorException.h>

#include "DeviceShape.h"
#include "Ack.h"
#include "Debug.h"

/*! 
 * \brief Constructor
 * Constructor of the class DeviceShape
 * 
 * \param sizeX  First dimension of the 3D array of booleans
 * \param sizeY  Second dimension of the 3D array of booleans
 * \param sizeZ  Third dimension of the 3D array of booleans
 */
DeviceShape::DeviceShape(int sizeX, int sizeY, int sizeZ) : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) 
{
    LOG(1, "DeviceShape(sizeX, sizeY, sizeZ)");
    //Allocation
    ledStatus = new bool**[sizeX];
    for (int x = 0; x < sizeX; ++x) {
        ledStatus[x] = new bool *[sizeY];
        for (int y = 0; y < sizeY; ++y)
            ledStatus[x][y] = new bool [sizeZ];
    }

    //Initialization
    this->off();
}

/*!
 * \brief Destructor
 * Destructor of the class DeviceShape
 */
DeviceShape::~DeviceShape() 
{
    LOG(1, "~DeviceShape()");
    //Deallocation
    if (ledStatus != NULL) {
        for (int x = 0; x < sizeX; ++x) {
            for (int y = 0; y < sizeY; ++y) {
                delete[] ledStatus[x][y];
            }
            delete[] ledStatus[x];
        }
        delete[] ledStatus;
    }
    ledStatus = NULL;
}

/*! 
 * \brief set the configuration of the LED of coordinates (x, y, z) to true
 *
 * \param x  first coordinate of the LED
 * \param y  second coordinate of the LED
 * \param z  third coordinate of the LED
 * 
 * \return true if the configuration of the LED is now true 
 * false otherwise
 */
bool DeviceShape::on(int x, int y, int z) 
{
    if (x > (this->sizeX - 1) || y > (this->sizeY - 1) || z > (this->sizeZ - 1))
        throw ErrorException("Index of led out of bounds");

    ledStatus[x][y][z] = true;
    
    return (ledStatus[x][y][z] == true);
}

/*! 
 * \brief Set the configuration of all LEDs to false
 * 
 * \return always return true
 */
bool DeviceShape::off() 
{
    for (int x = 0; x < sizeX; ++x)
        for (int y = 0; y < sizeY; ++y)
            for (int z = 0; z < sizeZ; ++z)
                ledStatus[x][y][z] = false;    
    return true;
}

/*! 
 * \brief set the configuration of the LED of coordinates (x, y, z) to false
 *
 * \param x  first coordinate of the LED
 * \param y  second coordinate of the LED
 * \param z  third coordinate of the LED
 *  
 * \return true if the configuration of the LED is now false 
 * false otherwise
 */
bool DeviceShape::off(int x, int y, int z) 
{
    if (x > (this->sizeX - 1) || y > (this->sizeY - 1) || z > (this->sizeZ - 1))
        throw ErrorException("Index of led out of bounds");

    ledStatus[x][y][z] = false;

    return (ledStatus[x][y][z] == false);
}

/*! 
 * \brief set the configuration of the LED of coordinates (x, y, z) to its 
 * opposite (true if it was false and false if it was true)
 * 
 * \param x  first coordinate of the LED
 * \param y  second coordinate of the LED
 * \param z  third coordinate of the LED
 * 
 * \return true if the whole shape stays in the 3D array
 * false otherwise
 */
bool DeviceShape::toggle(int x, int y, int z) 
{
    if (x > (sizeX - 1) || y > (sizeY - 1) || z > (sizeZ - 1))
        throw ErrorException("Index of led out of bounds");

    return (ledStatus[x][y][z] == true) ?
            (ledStatus[x][y][z] = false) : (ledStatus[x][y][z] = true);
}

/*! 
 * \brief Returns the nb of uint8_t in the array
 *
 * \return int : nb of uint8_t in the array
 */
int DeviceShape::getSizeInBytes() 
{
    return ceil(double(sizeX * sizeY * sizeZ) / 8.0); //Nb of uint8_t in the array
}

/*! 
 * \brief Write the 3D array in a 1D array
 * 
 * \param arrayToFill : array in which we write
 */
void DeviceShape::toArray(uint8_t *arrayToFill) 
{
    if (arrayToFill != NULL) {
        uint8_t tmp = 0;
        uint8_t val;
        int i = 0;
        int j = 7;

        for (int x = 0; x < sizeX; ++x)
            for (int y = 0; y < sizeY; ++y)
                for (int z = 0; z < sizeZ; ++z) {
                    //Make groups of 8 bits to fill the array
                    val = ledStatus[x][y][z] ? 1 : 0;
                    tmp |= (val << j);

                    if (j == 0 || (x == 8 && y == 8 && z == 8)) {
                        arrayToFill[i] = tmp;
                        j = 7;
                        tmp = 0;
                        ++i;
                    } else {
                        --j;
                    }
                }
    }
}

/*!
 * \brief Overload of the operator <<
 * 
 * \param os : stream on which we write
 * \param d : DeviceShape we display
 * 
 * @return std::ostream& : os (stream we wrote on) 
 */
std::ostream& operator<<(std::ostream& os, const DeviceShape& d) 
{
    d.print(os);
    return os;
}

/*! 
 * \brief Displays the 3D array
 */
void DeviceShape::print(std::ostream &str) const 
{
    for (int z = 0; z < sizeZ; ++z) {
        str << "Z = " << z << std::endl;
        for (int y = 0; y < sizeY; ++y) {
            str << "Y = " << y << std::endl;
            for (int x = 0; x < sizeX; ++x) {
                if (ledStatus[x][y][z])
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
 * \brief Overload of the operator =
 * 
 * \param ds  the DeviceShape we want to copy
 * 
 * \return the deviceShape equal to ds 
 */
DeviceShape& DeviceShape::operator=(const DeviceShape &ds) 
{
    LOG(1, "DeviceShape =");

    if (&ds != this) {
        this->sizeX = ds.getSizeX();
        this->sizeY = ds.getSizeY();
        this->sizeZ = ds.getSizeZ();

        memcpy(this->ledStatus, ds.ledStatus, sizeX * sizeY * sizeZ * sizeof (bool));
    }
    return *this;
}

/*! 
 * \brief Returns the first dimension of the 3D array
 *
 * \return int sizeX : first dimension of the 3D array
 */
int DeviceShape::getSizeX() const 
{
    return this->sizeX;
}

/*! 
 * \brief Returns the second dimension of the 3D array
 *
 * \return int sizeY : second dimension of the 3D array
 */
int DeviceShape::getSizeY() const 
{
    return this->sizeY;
}

/*! 
 * \brief Returns the third dimension of the 3D array
 *
 * \return int sizeZ : third dimension of the 3D array
 */
int DeviceShape::getSizeZ() const 
{
    return this->sizeZ;
}

/*! 
 * \brief Returns the 3D array
 *
 * \return bool ***ledStatus : the 3D array
 */
bool*** DeviceShape::getLedStatus() const 
{
    return this->ledStatus;
}

/*! 
 * \brief Sets the 3D array to the 3D array
 *  of the ShapeToDisplay
 * 
 * \return true if copy went well
 * false otherwise (for example dimensions did not match)
 */
bool DeviceShape::copyLedStatus(ShapeToDisplay &s) 
{
    if (sizeX != s.getSizeX() || sizeY != s.getSizeY() || sizeZ != s.getSizeZ()) {
        std::cout << "DeviceShape::copyLedStatus(ShapeToDisplay &s) : "
                "size does not match between the DeviceShape and the ShapeToDisplay" << std::endl;
        return false;
    } else {
        for (int x = 0; x < sizeX; x++)
            for (int y = 0; y < sizeY; y++)
                for (int z = 0; z < sizeZ; z++) {
                    ledStatus[x][y][z] = s.getStatus()[x][y][z];
                }         
    }
    return true;
}
