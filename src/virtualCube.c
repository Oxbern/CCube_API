#include <stdlib.h>

#include "virtualCube.h"

#define APP_RX_DATA_SIZE  512
#define BEGINNING_DATA 0x01 

uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
uint16_t UserRxBufferFS_Current_Index;
uint16_t UserRxBufferFS_Expected_Size;

static void CDC_Control_FS(uint8_t cmd, uint8_t *Buf, uint16_t size) {

    return;
}


/* Helper */
static void Empty_UserRxBufferFS() {
    for (int i = 0; i < APP_RX_DATA_SIZE; ++i) {
	UserRxBufferFS[i] = 0;
    }
 }


void CDC_Receive_FS (uint8_t *buff_RX, uint32_t *Len) {
    uint8_t Current_CMD = 0;
    static uint8_t buff_TX[512];
        
    if (buff_RX[0] == BEGINNING_DATA) {
	Current_CMD = buff_RX[1];
	Empty_UserRxBufferFS();
    	UserRxBufferFS_Current_Index = 0;
    	UserRxBufferFS_Expected_Size = buff_RX[3] + (buff_RX[2] << 8);
    } else {
	Current_CMD = buff_RX[1];
    }
    
    if (Current_CMD == CDC_DISPLAY_CUBE) {
	for (int i = 4; i < 62; ++i) {
	    UserRxBufferFS[UserRxBufferFS_Current_Index] = buff_RX[i];
	    UserRxBufferFS_Current_Index++;
	}
	buff_TX[0] = CDC_SEND_ACK;
	buff_TX[1] = Current_CMD;
	buff_TX[2] = buff_RX[2];
	buff_TX[3] = buff_RX[3];
	buff_TX[4] = 0;
	buff_TX[5] = 0x01;
	*Len = 6;
    }

    if (Current_CMD == 0x01 && UserRxBufferFS_Current_Index >= UserRxBufferFS_Expected_Size) {
    	CDC_Control_FS(Current_CMD, UserRxBufferFS, UserRxBufferFS_Current_Index*sizeof(uint8_t));
    }

    USBD_CDC_TransmitPacket(buff_TX);
}


uint8_t *USBD_CDC_TransmitPacket(uint8_t *buff_TX) {

    return 0;
}
