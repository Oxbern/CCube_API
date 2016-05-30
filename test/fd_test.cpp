#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "DeviceShape.h"
#include "Utils.h"

/* User variable definition */
#define ACK_SIZE 10

pthread_t ack_thread;

/* User functions */
int getAck(int fd);
void *waitForACK(void *arg);

/**
 * @brief  Manually set a message and send it over USB
 *         Get the ACK sent back
 */

int main ()
{
	/* Open connection in non blocking mode */
	int fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY);
	fcntl(fd, F_SETFL, 0);

	/* Check for error */
	if (fd < 0) {
		fprintf(stderr, "Error opening file\n");
		close(fd);
		return EXIT_FAILURE;
	}
		
	/* Create a thread to listen to the response sent from the CUBE */
	if(pthread_create(&ack_thread, NULL, waitForACK, &fd)) {
		fprintf(stderr, "Error creating thread\n");
		return EXIT_FAILURE;	
	}

	/* Create a device shape */
	DeviceShape ds(9, 9, 9);

	/* Turn on one LED */
	ds.on(4, 4, 4);

	/* Create a data message */
	uint8_t *myDataMessage = (uint8_t *)calloc(92, sizeof(uint8_t));

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

	/* Get the ACK response */
	getAck(fd);

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

	/* Get the ACK response */
	getAck(fd);

	/* Close file descriptor */
	close(fd);

	/* Free allocated memory */
	free(myDataMessage);
	
	return 0;
}

/**
 * @brief Read a ACK message from USB
 */
void *waitForACK(void *arg)
{
	int *fd = (int *)arg;

	uint8_t ack[10] = {0};
	uint8_t emptyAck[10] = {0};
		
	// Get ack
	read(*fd, &ack[0], ACK_SIZE);

	if (memcmp(ack, emptyAck, 10)) {
		fprintf(stdout, "ACK: ");
		for (int i = 0; i < 10; ++i)
			fprintf(stdout, "%u |", ack[i]);
		fprintf(stdout, "\n");
	}

	return NULL;
}


/**
 * @brief Print the ACK message received 
 */
int getAck(int fd)
{
	if(pthread_join(ack_thread, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		return EXIT_FAILURE;
	}

	if(pthread_create(&ack_thread, NULL, waitForACK, &fd)) {
		fprintf(stderr, "Error creating thread\n");
		return EXIT_FAILURE;	
	}

	return 0;
}
