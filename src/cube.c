#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include "cube.h"
#include "crc.h"

#define DEBUG 0

cube *new_cube() {
    cube *newCube = malloc(sizeof(cube));

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 9; ++j)
	    	newCube->led_buffer[i][j] = (uint16_t)0b0000000000;
			newCube->led_buffer[i][9] = (uint16_t)(1 << i);
    }
    newCube->led_buffer[9][9] = (uint16_t)0b0000000000;
    return newCube;
}

/**
 * Fill an array with the status of each led 
 */
void cubeToArray(cube c, uint8_t *led_status) {
	int i = 0, x = 0, y = 0;

	while (x < 10 && y < 10) {
		if (x > 9 || y > 9) {
		    led_status[i] = 0;
			led_status[i+1] = 0;
		} else {
		    led_status[i] = c.led_buffer[x][y] >> 8;
		    led_status[i+1] = 0xFF & c.led_buffer[x][y];

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

/**
* Switch on a led
* x, y, z should be > 0 and <= 8
*/
void on(int x, int y, int z, cube *cube) {
	if (x > 8 || y > 8 || z > 8) {
		perror("Index of led out of bounds");
		exit(EXIT_FAILURE);
	} else {
		cube->led_buffer[z][(8-y)] |= (1 << x);
	}
}

/**
* Switch off a led
* 	x, y, z should be > 0 and <= 8
*/
void off(int x, int y, int z, cube *cube) {
	if (x > 8 || y > 8 || z > 8) {
		perror("Index of led out of bounds");
		exit(EXIT_FAILURE);
	} else {
		cube->led_buffer[z][(8-y)] &= (0 << x);
	}
}

/**
* Toggle a led status
* 	x, y, z should be > 0 and <= 8
*/
void toggle(int x, int y, int z, cube *cube) {
	if (x > 8 || y > 8 || z > 8) {
		perror("Index of led out of bounds");
		exit(EXIT_FAILURE);
	} else {
		cube->led_buffer[z][(8-y)] ^= (1 << x);
	}
}


void display(char * dev, cube *cube) {
    int fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
    uint8_t *buf = calloc(BUFFER_MAX_INDEX, sizeof(uint8_t));
    
    if (fd == -1) {
		perror("Unable to open connection\n");
		exit(EXIT_FAILURE);
    } else if (fd > 0) {
	int x = 0, y = 0;
	bool firstBuffer = true;

	while (x < 10 && y < 10) {

	    /* First octet set to know if this is the first buffer of package */
	    if (firstBuffer) {
		buf[0] = 0x01;
		firstBuffer = false;
	    }
	    else
		buf[0] = 0x00;
	    
	    /* Commande : Display cube */
	    buf[1] = 0x01;
	    /* Size of data to send : 10x10x16bits = 200B = 0xC8B */
	    buf[3] = 0xC8; buf[2] = 0;

	    for (int k = 4; k < BUFFER_MAX_INDEX - 2; k += 2) {
		if (x > 9 || y > 9)
		    buf[k] = 0;
		else {
		    buf[k] = cube->led_buffer[x][y] >> 8;
		    buf[k+1] = 0xFF & cube->led_buffer[x][y];

		    y = (y + 1) % 10;
		    if (y == 0) {
			x = (x + 1) % 10;
			if (x == 0) {
			    x = 10; y = 10;
			}
		    }
		}
	    }
	    uint16_t crc = computeCRC(buf+4, 8*58);
	    
	    buf[BUFFER_MAX_INDEX - 2] = crc >> 8;
	    buf[BUFFER_MAX_INDEX - 1] = crc & 0xFF;

	    printf("One buffer sent! \n");
	    for (int k = 0; k < 64; ++k)
		printf("%u | ", buf[k]);
	    printf("\n");
	    
	    /* Buffer is now full, ready to be sent */
	    write(fd, buf, 64);
	    sleep(1);
	  
	    /* uint8_t *ACK = getACK(fd); */
#if DEBUG
	    printf("BUFFER : \n");
	    for (int l = 0; l < BUFFER_MAX_INDEX; ++l)
		printf("%x ", buf[l]);
	    printf("\nEND OF BUFFER\n");
#endif
	}

    } else {
	perror("Error in open_connection function\n");
	exit(EXIT_FAILURE);
    }
    close(fd);
}

uint8_t *getACK(int fd) {
    
    int index = 0,
	c = 0;
    
    uint8_t *buf = malloc(6*sizeof(uint8_t));
        
    while (read(fd, &c, 1) > 0) {
	buf[index] = c;
	index ++;
    }
        
    return buf;
}
