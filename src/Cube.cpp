#include <cstdint>

#include "Cube.h"

#define BUFFER_MAX_SIZE 64

/**
 * @brief Creates a cube
 */
Cube::Cube()
{

}


/**
 * @brief Destructor
 */
Cube::~Cube()
{

}


/** 
 * @brief Switchs on a led
 * @param x
 * @param y
 * @param z
 */
bool Cube::on(int x, int y, int z)
{
    return false;
}


/** 
 * @brief Turns off the cube
 */
bool Cube::off()
{
    return false;
}


/** 
 * @brief Turns off a led
 * @param x
 * @param y
 * @param z
 */
bool Cube::off(int x, int y, int z)
{
    return false;
}


/** 
 * @brief Toggles a led
 * @param x
 * @param y
 * @param z
 */
bool Cube::toggle(int x, int y, int z)
{
    return false;
}


/**
 * @brief Converts ledBuffer into an array
 * @param ledStatus the filled array
 */
void Cube::toArray(uint8_t * ledStatus)
{

}