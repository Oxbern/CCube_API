
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <mutex>

#include "DeviceShape.h"
#include "Utils.h"

/* User variable definition */
#define ACK_SIZE 10

/* File descriptor used  */
int fd = 0;

/* Up to 10 ACKs can be stored */
uint8_t ack[10][10];   
uint8_t ack_index = 0;

std::mutex lock_ack;

/* User functions */
void *waitForACK();

/**
 * @brief  Manually set a message and send it over USB
 *         Get the ACK sent back
 */
int main ()
{
	/* Open connection in non blocking mode */
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

	/* Check for error */
	if (fd < 0) {
		fd = open("/dev/stdout", O_RDWR | O_NOCTTY);
	}

	/* Set blocking mode */
	fcntl(fd, F_SETFL, 0);

	/* Define ACK thread */
	std::thread ack_thread(waitForACK);
	
	/* Create a device shape */
	DeviceShape ds(9, 9, 9);

	/* Turn on one LED */
	ds.on(4, 4, 4);

	/* Create a data message */
	uint8_t *myDataMessage = (uint8_t *)calloc(92, sizeof(uint8_t));
	uint8_t *localAck = (uint8_t *)calloc(10, sizeof(uint8_t));
	
	/* Manually set header */
	myDataMessage[0] = 1;
	myDataMessage[1] = 1;
	myDataMessage[2] = 0x42;
	myDataMessage[3] = 0;
	myDataMessage[4] = 92;

	/* Copy data into the buffer */
	memcpy(&myDataMessage[5], ds.toArray(), 57);

	/* Set CRC */
	uint16_t crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t));
	
	myDataMessage[62] = crc >> 8;
	myDataMessage[63] = crc & 0xFF;

	/* Print the message */
	printf("My Data Message:");
	for (int i = 0; i < 64; ++i)
		printf("%u |", myDataMessage[i]);
	printf("\n");

	/* Send it over USB */
	write(fd, &myDataMessage[0], 64);

	while (!lock_ack.try_lock());
	memcpy(&localAck[0], ack[ack_index--], 10);
	lock_ack.unlock();

	fprintf(stdout, "ACK: ");
	for (int i = 0; i < 10; ++i)
		fprintf(stdout, "%u |", localAck[i]);
	fprintf(stdout, "\n");

	/* Prepare next buffer to send */
	myDataMessage[0] = 0;
	myDataMessage[4] = 35;

	/* Copy the rest of the data in the buffer */
	memcpy(&myDataMessage[5], ds.toArray() + 57, 35);

	/* Set the CRC */
	crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t));

	myDataMessage[62] = crc >> 8;
	myDataMessage[63] = crc & 0xFF;

	/* Print the buffer sent */
	printf("My Data Message:");
	for (int i = 0; i < 64; ++i)
		printf("%u |", myDataMessage[i]);
	printf("\n");

	/* Send the buffer */
	write(fd, &myDataMessage[0], 64);

	while (!lock_ack.try_lock());
	memcpy(&localAck[0], ack[ack_index--], 10);
	lock_ack.unlock();

	fprintf(stdout, "ACK: ");
	for (int i = 0; i < 10; ++i)
		fprintf(stdout, "%u |", localAck[i]);
	fprintf(stdout, "\n");

	/* Let the thread go */
	ack_thread.detach();

    /* Close file descriptor */
	close(fd);

	/* Free allocated memory */
	free(myDataMessage);
	free(localAck);
	
	return 0;
}

/**
 * @brief Read a ACK message from USB
 */
void *waitForACK()
{
	/* uint8_t emptyAck[10] = {0}; */

	while (1) {
		
		while (!lock_ack.try_lock());
		read(fd, &ack[++ack_index], ACK_SIZE);
		lock_ack.unlock();
	}

	return NULL;
}
