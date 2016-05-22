#include <stdlib.h>

#include "virtualCube.h"
#include "crc.h"

#define BUFFER_MAX_INDEX 64

int main() {

    uint8_t *buff_TX = calloc(BUFFER_MAX_INDEX, sizeof(uint8_t));

    buff_TX[0] = 0x00;
    buff_TX[1] = 0x01; 		/* Display Cube */
    buff_TX[2] = 0x00;
    buff_TX[3] = 0xFF;

    uint16_t crc = computeCRC(buff_TX+4, 58*sizeof(uint8_t));
    
    buff_TX[BUFFER_MAX_INDEX - 1] = crc & 0xFF;
    buff_TX[BUFFER_MAX_INDEX - 2] = crc >> 8;
    
    CDC_Receive_FS(buff_TX, NULL);

    
    
    return 0;
}
