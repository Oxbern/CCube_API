#ifndef CUBE_H
#define CUBE_H

#include <stdint.h>

#define BUFFER_MAX_INDEX 64

/**
 * @struct cube
 */
typedef struct _cube {
    uint16_t led_buffer[10][10];
} cube;

/**
 * @brief 
 * @return new cube 
 */
cube *new_cube();


/**
 * @brief Turns on a led
 * @param x
 * @param y 
 * @param z
 * @param cube
 */
void on(int x, int y, int z, cube *cube);

/**
 * @brief Turns off a led
 * @param x
 * @param y 
 * @param z
 * @param cube
 */
void off(int x, int y, int z, cube *cube);

/**
 * @brief Toggles a led status
 * @param x
 * @param y 
 * @param z
 * @param cube
 */
void toggle(int x, int y, int z, cube *cube);

/**
 * @brief 
 * @param dev 
 * @param cube
 */
void display(char * dev, cube *cube);

#endif 
