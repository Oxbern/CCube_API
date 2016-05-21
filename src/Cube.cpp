#include "Cube.h"
// #include <iostream>

/**
 * @brief Default Constructor
 */
Cube::Cube() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            ledBuffer[i][j] = (uint16_t)0b0000000000;
        }
        ledBuffer[i][9] = (uint16_t)(1 << i);
    }
}

/**
 * @brief Destructor
 */
Cube::~Cube() {
}

/** 
 * @brief Switchs on a led
 * @param x
 * @param y
 * @param z
 */
void Cube::on(int x, int y, int z) {
    if (x > 8 || y > 8 || z > 8) {
        std::perror("Index of led out of bounds");
        exit(EXIT_FAILURE);
    } else {
        ledBuffer[z][(8-y)] |= (1 << x);
    }
}

/** 
 * @brief Turns off the cube
 */
void Cube::off() {
    for (int i = 0; i < 9 ; i++) {
        for (int j = 0; j < 9; j++) {
            ledBuffer[i][j] = 0b0000000000;
        }
    }    
}


/** 
 * @brief Turns off a led
 * @param x
 * @param y
 * @param z
 */
void Cube::off(int x, int y, int z) {
    if (x > 8 || y > 8 || z > 8) {
        std::perror("Index of led out of bounds");
        exit(EXIT_FAILURE);
    } else {
        ledBuffer[z][(8-y)] &= ~(1 << x);
    }
}

/** 
 * @brief Toggles a led
 * @param x
 * @param y
 * @param z
 */
void Cube::toggle(int x, int y, int z) {
    if (x > 8 || y > 8 || z > 8) {
        std::perror("Index of led out of bounds");
        exit(EXIT_FAILURE);
    } else {
        ledBuffer[z][(8-y)] ^= (1 << x);
    }
}

/**
 * @brief Converts into an array
 * @param ledStatus 
 */
void Cube::toArray(uint8_t *ledStatus) {
    int i = 0, x = 0, y = 0;

    while (x < 10 && y < 10) {
        if (x > 9 || y > 9) {
            ledStatus[i] = 0;
            ledStatus[i+1] = 0;
        } else {
            ledStatus[i] = (uint8_t)(ledBuffer[x][y] >> 8);
            ledStatus[i+1] = (uint8_t)(0xFF & ledBuffer[x][y]);

            y = (y + 1) % 10;
            if (y == 0) {
            x = (x + 1) % 10;
            if (x == 0) {
                x = 10; y = 10;
            }
            }
        }
        i += 2;
    }
}