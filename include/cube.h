#ifndef CUBE_H
#define CUBE_H

#include <stdint.h>

#define BUFFER_MAX_INDEX 64
#define DATA_MAX_SIZE 58

/**
 * @struct cube
 */
typedef struct _cube {
    uint16_t led_buffer[10][10];
} cube;

typedef uint8_t buffer[BUFFER_MAX_INDEX]; 

/**
 * @struct buffer
 */
 /*
typedef struct _buffer {
	uint16_t header_bit;
	uint8_t codop;
	uint16_t size;
	uint8_t data[DATA_MAX_SIZE];
	uint16_t crc;
} buffer; 
*/

/**
 * @brief 
 * @return new cube 
 */
cube *new_cube();

/**
 * @brief Converts cube's structure to an array 
 * @param c : a cube 
 * @param led_status : array to fill
 */
void cubeToArray(cube c, uint8_t *led_status);

/**
 * @brief
 * @return get ACK (over USB connection) as uint8_t table 
 */
uint8_t *getACK(int fd);


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
