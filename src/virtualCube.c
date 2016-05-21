#include <stdlib.h>
#include <stdbool.h>

#include "virtualCube.h"

#define APP_RX_DATA_SIZE  512
#define BEGINNING_DATA 0x01 

uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
uint16_t UserRxBufferFS_Current_Index;
uint16_t UserRxBufferFS_Size_Left;

/* Received Buffer Index */
#define BEGINNING_INDEX 0 
#define CMD_INDEX 1
#define SIZE_INDEX 2
#define DATA_INDEX 4
#define CRC_INDEX 62


static void CDC_Control_FS(uint8_t cmd, uint8_t *Buf, uint16_t size) {

    return;
}


/* Helper */
static void Empty_UserRxBufferFS() {
    for (int i = 0; i < APP_RX_DATA_SIZE; ++i) {
	UserRxBufferFS[i] = 0;
    }
    UserRxBufferFS_Current_Index = 0;
 }

static bool Is_CMD_Known(uint8_t CMD) {
    if (CMD == CDC_DISPLAY_CUBE ||
	CMD == CDC_SEND_ACK)
	return true;
    return false;
}

void ACKSend_OK(uint8_t *buff_TX, uint8_t CMD, uint16_t size_buff, uint16_t crc) {

}

uint16_t CRC_compute() {
    /* TODO */
    return 0x0001;
}

void CDC_Receive_FS (uint8_t *buff_RX, uint32_t *Len) {
    uint8_t Current_CMD = 0;
    static uint8_t buff_TX[512];
    static uint16_t buff_RX_Index = DATA_INDEX;
    
    if (Is_CMD_Known(buff_RX[1])) { /* Only handle buffer that can be understood */
    
	if (buff_RX[BEGINNING_INDEX] == BEGINNING_DATA) {  /* Empty local buffer for new message */
	    Empty_UserRxBufferFS();
	}
	
	Current_CMD = buff_RX[CMD_INDEX];
	/* TODO: Test whether size_left == size left written in message
	 If not send ACK_NOK */
	uint16_t size_buff = buff_RX[SIZE_INDEX + 1]
	    + (buff_RX[SIZE_INDEX] << 8);

	while (UserRxBufferFS_Size_Left-- > 0 || buff_RX_Index < CRC_INDEX) {
	    UserRxBufferFS[UserRxBufferFS_Current_Index++] = buff_RX[buff_RX_Index];
	}

	ACKSend_OK(buff_TX, Current_CMD, size_buff, CRC_compute()); 

	if (UserRxBufferFS_Size_Left == 0) {
	    CDC_Control_FS(Current_CMD, UserRxBufferFS,
			   UserRxBufferFS_Current_Index*sizeof(uint8_t));
	}
    } else { }			/* Nothing to do here */

    USBD_CDC_TransmitPacket(buff_TX);
}


uint8_t *USBD_CDC_TransmitPacket(uint8_t *buff_TX) {

    return 0;
}
