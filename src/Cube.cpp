#include <cstdint>
#include <stdio.h>
#include <cstdlib>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "Cube.h"
#include "Message.h"

#define BUFFER_MAX_SIZE 64

/**
 * @brief Creates a cube
 */
Cube::Cube() {
    ledBuffer = new uint16_t*[10];
    for (int k = 0; k < 10; k++)
        ledBuffer[k] = new uint16_t[10];
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            ledBuffer[i][j] = (uint16_t)0b0000000000;
        }
        ledBuffer[i][9] = (uint16_t)(1 << i);
    }
    this->ledBuffer[9][9] = (uint16_t)0b0000000000;

}


/**
 * @brief Destructor
 */
Cube::~Cube() {
    for (int i = 0; i < 10; i++)
        delete [] ledBuffer[i];
    delete [] ledBuffer;
}

/** 
 * @brief Switchs on a led
 * @param x
 * @param y
 * @param z
 */
void Cube::on(int x, int y, int z) {
    if (x > 8 || y > 8 || z > 8) {
        perror("Index of led out of bounds");
        exit(EXIT_FAILURE);
    } else {
        this->ledBuffer[z][(8-y)] |= (1 << x);
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
        perror("Index of led out of bounds");
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
        perror("Index of led out of bounds");
        exit(EXIT_FAILURE);
    } else {
        ledBuffer[z][(8-y)] ^= (1 << x);
    }
}

/**
 * @brief Converts ledBuffer into an array
 * @param ledStatus the filled array
 */
void Cube::toArray(uint8_t * ledStatus) {

    //uint8_t *ledStatus = new uint8_t[SIZE_DATA_LED];
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
    //return ledStatus;
}

/**
 * @brief Displays the entire cube
 * @param dev
 */
void Cube::display(const char *dev) {
    int fd = 0;
    if (strcmp(dev, "local")) 
	fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);

    // std::cout << "Connection Ok :" << fd << "\n";
    Message message(SIZE_DATA_LED,1);

    if (fd == -1) {
        perror("Unable to open connection\n");
        exit(EXIT_FAILURE);
    } else if (fd > 0) {
        uint8_t *data = new uint8_t[SIZE_DATA_LED];
        toArray(data); //converts ledBuffer to an array
        message.encode(data, SIZE_DATA_LED);
        message.send(fd);
        delete [] data;
        
    } else {
	perror("Error in open_connection function\n");
	exit(EXIT_FAILURE);
    }
    close(fd);
            
}

uint8_t Cube::getLedBuffer(int x, int y, int z) {
    uint8_t val = (uint8_t)((ledBuffer[z][y] >> x) & 0x1);
    return val;
}
