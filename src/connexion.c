#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

#include "connexion.h"
#include "crc.h"

int fd = -1;

/**
 * @brief Opens a connection with the device
 * @param dev : path of the device
 * @return file descriptor for communicate with the device
 */
int open_connection(char* dev) {
    if (fd == -1)  {
        fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
    }
    return fd;
}

int getNumberOfBuffer(uint16_t size) {
	int nb_buffer = 0;
	if ((size % DATA_MAX_SIZE) == 0) {
		nb_buffer = size / DATA_MAX_SIZE;
	} else
		nb_buffer = (size / DATA_MAX_SIZE) + 1;
	return nb_buffer; 
}

buffer* data_encoding(uint8_t codop, uint16_t size, uint8_t *data){
	buffer* l_buffer;
	bool firstBuffer = true;
	int size_remaining = size;
	int ind_buff = 0;

	//Number of buffer for all the data
	int nb_buffer = getNumberOfBuffer(size);	
	
	l_buffer = calloc(nb_buffer, sizeof(buffer));


	while (ind_buff < nb_buffer) {
		//First bit : 1 Byte
		if (firstBuffer) {
			l_buffer[ind_buff][0] = 0x1;
			firstBuffer = false;
		} else
			l_buffer[ind_buff][0] = 0x0;

		//Operation Code : 1 Byte
		l_buffer[ind_buff][1] = codop;

		// Size of data remaining to send
		l_buffer[ind_buff][2] = size_remaining >> 8;
		l_buffer[ind_buff][3] = size_remaining & 0xff; 

	    //Data
	    for (int k = 4; (size_remaining > 0) && (k < BUFFER_MAX_INDEX - 2); k++) {
	    	l_buffer[ind_buff][k] = data[size-size_remaining];
	    	size_remaining--;
	    }
		
	    //CRC
		uint16_t crc = computeCRC(l_buffer[ind_buff]+4, 8*58);
	    l_buffer[ind_buff][BUFFER_MAX_INDEX-2] = crc >> 8;
	    l_buffer[ind_buff][BUFFER_MAX_INDEX-1] = crc & 0xFF;

	    ind_buff++;
	}

	return l_buffer;
}
