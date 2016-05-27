#include <thread>
#include <cstring>

#include "VirtualCube.h"
#include "Utils.h"

#define APP_RX_DATA_SIZE  512
#define BEGINNING_DATA 0x01

uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
uint16_t UserRxBufferFS_Current_Index;
uint16_t UserRxBufferFS_Size_Left = 0;
uint8_t UserRxBufferFS_Current_CMD;
bool HANDLE_DATA_RECEIVED = false;

/* Received Buffer Index */
// see Utils.h

/* Size of ACK buffers */
uint8_t ACK[SIZE_ACK] = {0};

typedef struct _Control_Args {
	uint8_t cmd;
	uint8_t *Buf;
	uint16_t size;
} Control_Args;

static void *CDC_Control_FS(void *args) {

	Control_Args *control_args = (Control_Args*)args;

	switch (control_args->cmd) {
	case CDC_DISPLAY_CUBE:
		printf("Display the cube\n");
		break;
	}

	return NULL;
}


/* Helper */
static void Empty_UserRxBufferFS() {
	for (int i = 0; i < APP_RX_DATA_SIZE; ++i) {
		UserRxBufferFS[i] = 0;
	}
	UserRxBufferFS_Current_Index = 0;
}

static void printBuffer(uint8_t *buffer, uint16_t size) {
	printf("ACK : |");
	for (int i = 0; i < size; ++i) {
		printf(" %u |", buffer[i]);
	}
	printf("\n");
}

static bool Is_CMD_Known(uint8_t CMD) {
	if (CMD == CDC_DISPLAY_CUBE ||
	    CMD == CDC_SEND_ACK)
		return true;

	return false;
}

static uint8_t *ACKSend_OK(uint8_t CMD, uint16_t size_buff, uint16_t crc) {
	printf("ACK OK\n");

	ACK[0] = CDC_SEND_ACK_OK;
	ACK[1] = CMD;
	ACK[2] = size_buff >> 8;
	ACK[3] = size_buff & 0xFF;
	ACK[4] = crc >> 8;
	ACK[5] = crc & 0xFF;

	return ACK;
}

static uint8_t *ACKSend_ERR(uint8_t CMD, uint16_t size_buff, uint16_t crc) {
	printf("ACK ERR\n");

	ACK[0] = CDC_SEND_ACK_ERR;
	ACK[1] = CMD;
	ACK[2] = size_buff >> 8;
	ACK[3] = size_buff & 0xFF;
	ACK[4] = crc >> 8;
	ACK[5] = crc & 0xFF;

	return ACK;
}

static uint8_t *ACKSend_NOK(uint8_t CMD, uint16_t size_buff, uint16_t crc) {
	printf("ACK NOK\n");

	ACK[0] = CDC_SEND_ACK_NOK;
	ACK[1] = CMD;
	ACK[2] = size_buff >> 8;
	ACK[3] = size_buff & 0xFF;
	ACK[4] = crc >> 8;
	ACK[5] = crc & 0xFF;

	return ACK;
}

static uint16_t CRC_compute(uint8_t *buff_RX) {
	return computeCRC(buff_RX, 58*sizeof(uint8_t));
}

static uint8_t *CDC_Set_ACK(uint8_t *buff_RX) {

	uint16_t buff_RX_Index = DATA_INDEX;
	uint8_t Current_CMD = buff_RX[OPCODE_INDEX];
	uint16_t size_left_buff = (buff_RX[SIZE_INDEX + 1]
	                           + (buff_RX[SIZE_INDEX] << 8));

	/* Compute CRC for received buffer */
	uint16_t computed_CRC = CRC_compute(buff_RX + DATA_INDEX);
	uint16_t buff_CRC = (buff_RX[(SIZE_BUFFER - SIZE_CRC)] << 8) + buff_RX[(SIZE_BUFFER - SIZE_CRC) + 1];

	/* Checks if a buffer was lost */
	if (buff_RX[HEADER_INDEX] != BEGINNING_DATA) {
		if (size_left_buff != UserRxBufferFS_Size_Left) {
			return ACKSend_NOK(Current_CMD,
			                   UserRxBufferFS_Size_Left, CRC_compute(buff_RX));
		} else if (Current_CMD != UserRxBufferFS_Current_CMD) {
			return ACKSend_NOK(UserRxBufferFS_Current_CMD,
			                   UserRxBufferFS_Size_Left, CRC_compute(buff_RX));
		}
	}

	if (buff_CRC != computed_CRC) {
		printf("CRC don't match: %u != %u\n", buff_CRC, computed_CRC);
		return ACKSend_ERR(Current_CMD,
		                   size_left_buff, CRC_compute(buff_RX));
	}

	/* Empty local buffer for new message */
	if (buff_RX[HEADER_INDEX] == BEGINNING_DATA) {
		if (UserRxBufferFS_Size_Left > 0) {
			return ACKSend_NOK(Current_CMD,
			                   size_left_buff, CRC_compute(buff_RX));
		} else {
			Empty_UserRxBufferFS();
			UserRxBufferFS_Size_Left = size_left_buff;
			UserRxBufferFS_Current_CMD = Current_CMD;
		}
	}

	/* Fill local buffer until no there is no data left to read */
	while (UserRxBufferFS_Size_Left > 0 && buff_RX_Index < (SIZE_BUFFER - SIZE_CRC)) {
		--UserRxBufferFS_Size_Left;
		UserRxBufferFS[UserRxBufferFS_Current_Index] = buff_RX[buff_RX_Index];
		UserRxBufferFS_Current_Index++;
		buff_RX_Index++;
	}

	if (UserRxBufferFS_Size_Left <= 0) {
		HANDLE_DATA_RECEIVED = true;
	} else {
		printf("Size Left : %d\n", UserRxBufferFS_Size_Left);
	}

	/* Send ACK */
	return ACKSend_OK(Current_CMD,
	                  size_left_buff, CRC_compute(buff_RX));
}



uint8_t *CDC_Receive_FS (uint8_t *buff_RX) {
	uint8_t *buff_TX = (uint8_t *) calloc(512, sizeof(uint8_t));

	if (Is_CMD_Known(buff_RX[OPCODE_INDEX])) { /* Only handle buffer that can be understood */
		memcpy(buff_TX, CDC_Set_ACK(buff_RX), SIZE_ACK*sizeof(uint8_t));
	} else if (UserRxBufferFS_Size_Left > 0){
		/* A buffer was received but there is still data to be recovered from last message */
		memcpy(buff_TX, ACKSend_NOK(UserRxBufferFS_Current_CMD,
		                            UserRxBufferFS_Size_Left, CRC_compute(buff_RX)),
		       SIZE_ACK*sizeof(uint8_t));
	}

	/* If all data were received the call control function */
	if (HANDLE_DATA_RECEIVED) {

		HANDLE_DATA_RECEIVED = false;

		Control_Args args = {.cmd = UserRxBufferFS_Current_CMD,
		                     .Buf = UserRxBufferFS,
		                     .size = (uint16_t )(UserRxBufferFS_Current_Index*sizeof(uint8_t))};
		pthread_t Control_FS_thread;


		if(pthread_create(&Control_FS_thread, NULL, CDC_Control_FS, &args)) {
			/* Do something smart to handle error */
		}

		if(pthread_join(Control_FS_thread, NULL)) {
			/* ERROR HANDLING ? */
		}

	}

	return USBD_CDC_TransmitPacket(buff_TX);

}


uint8_t *USBD_CDC_TransmitPacket(uint8_t *buff_TX) {

	printBuffer(buff_TX, SIZE_ACK);

	return buff_TX;
}
