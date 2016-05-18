#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "cube.h"

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

void display(char * dev, cube *cube) {
    int fd /* = open_connection(dev) */;
    uint8_t *buffer = calloc(BUFFER_MAX_INDEX, sizeof(uint8_t));
    
    if (fd == -1)
	perror("Unable to open connection\n");
    else if (fd > 0) {
	int x = 0, y = 0;
	bool firstBuffer = true;

	while (x < 10 && y < 10) {

	    /* First octet set to know if this is the first buffer of package */
	    if (firstBuffer)
		buffer[0] = 0x01;
	    else
		buffer[0] = 0x00;
	    
	    /* Commande : Display cube */
	    buffer[1] = 0x01;
	    /* Size of data to send : 10x10x16bits = 200B = 0xC8B */
	    buffer[3] = 0xC8; buffer[2] = 0;

	    for (int k = 4; k < BUFFER_MAX_INDEX - 2; k += 2) {
		if (x > 9 || y > 9)
		    buffer[k] = 0;
		else {
		    buffer[k] = cube->led_buffer[x][y] >> 8;
		    buffer[k+1] = 0xFF & cube->led_buffer[x][y];

		    y = (y + 1) % 10;
		    if (y == 0) {
			x = (x + 1) % 10;
			if (x == 0) {
			    x = 10; y = 10;
			}
		    }
		}
	    }

	    buffer[BUFFER_MAX_INDEX - 2] = 0x04;
	    buffer[BUFFER_MAX_INDEX - 1] = 0x04;

	    /* Buffer is now full, ready to be sent */
	    /* write(fd, buffer, 64); */

#if DEBUG
	    printf("BUFFER : \n");
	    for (int l = 0; l < BUFFER_MAX_INDEX; ++l)
		printf("%x ", buffer[l]);
	    printf("\nEND OF BUFFER\n");
#endif
	}

    } else {
	perror("Error in open_connection function\n");
    }
    
}


