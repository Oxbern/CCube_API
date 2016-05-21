#include <stdlib.h>
#include <stdbool.h>

#include "virtualCube.h"

#define APP_RX_DATA_SIZE  512
#define BEGINNING_DATA 0x01 

uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
uint16_t UserRxBufferFS_Current_Index;
uint16_t UserRxBufferFS_Size_Left;
uint8_t UserRxBufferFS_Current_CMD;

/* Received Buffer Index */
#define BEGINNING_INDEX 0 
#define CMD_INDEX 1
#define SIZE_INDEX 2
#define DATA_INDEX 4
#define CRC_INDEX 62

/* Size of ACK buffers */
#define ACK_OK_SIZE 8
#define ACK_ERR_SIZE 8
#define ACK_NOK_SIZE 8

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

void ACKSend_OK(uint8_t *buff_TX, uint16_t size, uint8_t CMD, uint16_t size_buff, uint16_t crc) {

}

void ACKSend_NOK(uint8_t *buff_TX, uint16_t size, uint8_t CMD, uint16_t size_buff, uint16_t crc) {

}

void ACKSend_ERR(uint8_t *buff_TX, uint16_t size, uint8_t CMD, uint16_t size_buff, uint16_t crc) {

}

uint16_t CRC_compute(uint8_t *buff_RX) {
    /* TODO */
    return 0x0001;
}

void CDC_Receive_FS (uint8_t *buff_RX, uint32_t *Len) {
    static uint8_t buff_TX[512];
    static uint16_t buff_RX_Index = DATA_INDEX;
    
    if (Is_CMD_Known(buff_RX[CMD_INDEX])) { /* Only handle buffer that can be understood */

	/* Get the info about the buffer */
	uint8_t Current_CMD = buff_RX[CMD_INDEX];
	uint16_t size_left_buff = buff_RX[SIZE_INDEX + 1]
	    + (buff_RX[SIZE_INDEX] << 8);
	
	/* Compute CRC for received buffer */
	uint16_t computed_CRC = CRC_compute(buff_RX);
	uint16_t buff_CRC = (buff_RX[CRC_INDEX] >> 8) + buff_RX[CRC_INDEX + 1];

	/* If CRC don't match then send ACK_ERR message */
	if (buff_CRC != computed_CRC) {
	    ACKSend_ERR(buff_TX, ACK_ERR_SIZE, Current_CMD,
			size_left_buff, CRC_compute(buff_RX));
	} else {

	    /* Checks if a buffer was lost */
	    if (size_left_buff != UserRxBufferFS_Size_Left) { 
		ACKSend_NOK(buff_TX, ACK_NOK_SIZE, Current_CMD,
			    size_left_buff, CRC_compute(buff_RX));  
	    } else { 		/* Buffer should be OK now */

		/* Empty local buffer for new message */
		if (buff_RX[BEGINNING_INDEX] == BEGINNING_DATA) {  
		    if (UserRxBufferFS_Size_Left > 0) {
			ACKSend_NOK(buff_TX, ACK_NOK_SIZE, Current_CMD,
				    size_left_buff, CRC_compute(buff_RX));
		    } else {
			Empty_UserRxBufferFS();
			UserRxBufferFS_Size_Left = size_left_buff;
			UserRxBufferFS_Current_CMD = Current_CMD;
		    }
		}

		/* Fill local buffer until no there is no data left to read */
		while (UserRxBufferFS_Size_Left-- > 0 || buff_RX_Index < CRC_INDEX) {
		    UserRxBufferFS[UserRxBufferFS_Current_Index++] = buff_RX[buff_RX_Index];
		}

		/* Send ACK */
		ACKSend_OK(buff_TX, ACK_OK_SIZE, Current_CMD,
			   size_left_buff, CRC_compute(buff_RX)); 

		/* If all data were received the call control function */
		if (UserRxBufferFS_Size_Left == 0) {
		    CDC_Control_FS(Current_CMD, UserRxBufferFS,
				   UserRxBufferFS_Current_Index*sizeof(uint8_t));
		}
	    }
	}
    } else if (UserRxBufferFS_Size_Left > 0){
	/* A buffer was received but there is still data to be recovered from last message */
	ACKSend_NOK(buff_TX, ACK_NOK_SIZE, UserRxBufferFS_Current_CMD,
		    UserRxBufferFS_Size_Left, CRC_compute(buff_RX));  
    }

    USBD_CDC_TransmitPacket(buff_TX);
}


uint8_t *USBD_CDC_TransmitPacket(uint8_t *buff_TX) {

    return buff_TX;
}
