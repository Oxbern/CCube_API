#include <stdlib.h>
#include <stdio.h>

#include "virtualCube.h"
#include "crc.h"

#define BUFFER_MAX_INDEX 64

int main() {

    uint8_t *buff_TX = calloc(BUFFER_MAX_INDEX, sizeof(uint8_t));
    printf("Empty buffer sent!\n");
    CDC_Receive_FS(buff_TX, NULL);

    buff_TX[0] = 0x01;
    buff_TX[1] = 0x01; 		/* Display Cube */
    buff_TX[2] = 0x00;
    buff_TX[3] = 0xC8;		/* Size = 200 */

    buff_TX[4] = 0x12;
    buff_TX[5] = 0x34;
    buff_TX[6] = 0x56;
    buff_TX[7] = 0x78;
    buff_TX[8] = 0x90;
    
    printf("\nBuffer with wrong CRC sent!\n");

    CDC_Receive_FS(buff_TX, NULL);
    
    uint16_t crc = computeCRC(buff_TX+4, 58*sizeof(uint8_t));
    
    buff_TX[BUFFER_MAX_INDEX - 1] = crc & 0xFF;
    buff_TX[BUFFER_MAX_INDEX - 2] = crc >> 8;

    printf("\nPerfect buffer sent!\n");
    CDC_Receive_FS(buff_TX, NULL);
    buff_TX[0] = 0x00;

    printf("\nWrong size left...\n");
    CDC_Receive_FS(buff_TX, NULL);
    buff_TX[3] = 0x8E;
    
    buff_TX[1] = 0x10;
    printf("\nWrong CMD...\n");
    CDC_Receive_FS(buff_TX, NULL);
    buff_TX[1] = 0x01;
    
    printf("\nPerfect buffer sent!\n");
    CDC_Receive_FS(buff_TX, NULL);
    buff_TX[3] = 0x54;
    
    printf("\nPerfect buffer sent!\n");
    CDC_Receive_FS(buff_TX, NULL);
    buff_TX[3] = 0x1A;
    
    printf("\nPerfect buffer sent!\n");
    CDC_Receive_FS(buff_TX, NULL);


    free(buff_TX);
    return 0;
}
