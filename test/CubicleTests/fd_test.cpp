#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <thread>
#include <mutex>

#include "DeviceShape.h"
#include "Utils.h"

/* User variable definition */
#define ACK_SIZE 10

#define DEBUG 0


/* File descriptor used  */
int fd = 0;
fd_set set;

/* Up to 10 ACKs can be stored */
uint8_t ack[100][10];   
uint8_t ack_index = 0;
struct timeval timeout = {0, 1000000L};

uint8_t ACK_OK_HEADER[5] = {1, 1, 1, 0, 3};

std::recursive_mutex lock_ack;

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

	/* clear the set */
	FD_ZERO(&set); 
    /* add our file descriptor to the set */
	FD_SET(fd, &set); 
	
	
	/* Define ACK thread */
	std::thread ack_thread(waitForACK);
	
	/* Create a device shape */
	DeviceShape ds(9, 9, 9);

	/* Turn on one LED */
	ds.on(4, 4, 4);

	/* Create a data message */
	uint8_t myDataMessage[64] = {0};
	uint8_t localAck[10] = {0};

	uint8_t *ledBuffer = new uint8_t[ds.getSizeInBytes()];
    ds.toArray(ledBuffer);

    uint16_t crc;

    
/* 	/\* ################################################ *\/ */
/* 	/\* #                SEND FIRST BUFFER             # *\/ */
/* 	/\* ################################################	 *\/ */
	
	/* /\* Manually set header *\/ */
	/* myDataMessage[0] = 1; */
	/* myDataMessage[1] = 1; */
	/* myDataMessage[2] = 0x42; */
	/* myDataMessage[3] = 0; */
	/* myDataMessage[4] = 92; */

	/* /\* Copy data into the buffer *\/ */
    /* ds.toArray(ledBuffer); */
	/* memcpy(&myDataMessage[5], ledBuffer, 57); */

	/* /\* Set CRC *\/ */
	/* crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t)); */
	
/* 	myDataMessage[62] = crc >> 8; */
/* 	myDataMessage[63] = crc & 0xFF; */

/* #if DEBUG */
/* 	/\* Print the message *\/ */
/* 	printf("My Data Message:"); */
/* 	for (int i = 0; i < 64; ++i) */
/* 		printf("%u |", myDataMessage[i]); */
/* 	printf("\n"); */
/* #endif */
	
/* 	/\* Send it over USB *\/ */
/* 	write(fd, &myDataMessage[0], 64); */

/* 	/\* Retrieve the ACK *\/ */
/* 	while (!lock_ack.try_lock()); */
/* 	memcpy(&localAck[0], ack[ack_index--], 10); */
/* 	lock_ack.unlock(); */

/* 	if (memcmp(&localAck[0], &ACK_OK_HEADER[0], 5)) { */
/* 	fprintf(stderr, "[TEST FAILED]: First buffer\n"); */
/* 	ack_thread.detach(); */
/* 	return EXIT_FAILURE; */
/* } */
	
/* #if DEBUG */
/* 	/\* Print the ACK *\/ */
/* 	fprintf(stdout, "ACK: "); */
/* 	for (int i = 0; i < 10; ++i) */
/* 		fprintf(stdout, "%u |", localAck[i]); */
/* 	fprintf(stdout, "\n"); */
/* #endif */


	
	/* ###################################################### */
	/* #                RESET CONNECTION                    # */
	/* ###################################################### */
	
	/* Reset the connection */
    uint8_t resetConnection[7] = {0};

	/* Manually set header */
	resetConnection[0] = 1;
	resetConnection[1] = 1;
	resetConnection[2] = 0xFF;
	resetConnection[3] = 0;
	resetConnection[4] = 0;

	/* Set CRC */
	crc = computeCRC(&resetConnection[0], 5*sizeof(uint8_t));
	
	resetConnection[5] = crc >> 8;
	resetConnection[6] = crc & 0xFF;
	
#if DEBUG
	/* Print the message */
	printf("My Data Message:");
	for (int i = 0; i < 7; ++i)
		printf("%u |", resetConnection[i]);
	printf("\n");
#endif

	/* Send it over USB */
	write(fd, &resetConnection[0], 7);

	while (!lock_ack.try_lock());
	memcpy(&localAck[0], ack[ack_index--], 10);
	lock_ack.unlock();

#if DEBUG
	fprintf(stdout, "ACK: ");
	for (int i = 0; i < 10; ++i)
		fprintf(stdout, "%u |", localAck[i]);
	fprintf(stdout, "\n");
#endif

	if (memcmp(&localAck[0], &ACK_OK_HEADER[0], 5)) {
	fprintf(stderr, "[TEST FAILED]: Reset connection\n");
	ack_thread.detach();
	return EXIT_FAILURE;
}
	
	/* ##################################################### */
	/* #               SEND ENTIRE MESSAGE                 # */
	/* ##################################################### */

	/* Manually set header */
	myDataMessage[0] = 1;
	myDataMessage[1] = 1;
	myDataMessage[2] = 0x42;
	myDataMessage[3] = 0;
	myDataMessage[4] = 92;

	/* Copy data into the buffer */
	memcpy(&myDataMessage[5], ledBuffer, 57);

	/* Set CRC */
	crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t));
	
	myDataMessage[62] = crc >> 8;
	myDataMessage[63] = crc & 0xFF;

#if DEBUG
	/* Print the message */
	printf("My Data Message:");
	for (int i = 0; i < 64; ++i)
		printf("%u |", myDataMessage[i]);
	printf("\n");
#endif
	
	/* Send it over USB */
	write(fd, &myDataMessage[0], 64);

	while (!lock_ack.try_lock());
	memcpy(&localAck[0], ack[ack_index--], 10);
	lock_ack.unlock();

#if DEBUG
	fprintf(stdout, "ACK: ");
	for (int i = 0; i < 10; ++i)
		fprintf(stdout, "%u |", localAck[i]);
	fprintf(stdout, "\n");
#endif

	if (memcmp(&localAck[0], &ACK_OK_HEADER[0], 5)) {
	fprintf(stderr, "[TEST FAILED]: First buffer (second time)\n");
	ack_thread.detach();
	return EXIT_FAILURE;
}

	/* Prepare next buffer to send */
	myDataMessage[0] = 0;
	myDataMessage[4] = 35;

	/* Copy the rest of the data in the buffer */
	memcpy(&myDataMessage[5], ledBuffer + 57, 35);

	/* Set the CRC */
	crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t));

	myDataMessage[62] = crc >> 8;
	myDataMessage[63] = crc & 0xFF;

#if DEBUG
	/* Print the buffer sent */
	printf("My Data Message:");
	for (int i = 0; i < 64; ++i)
		printf("%u |", myDataMessage[i]);
	printf("\n");
#endif
	
	/* Send the buffer */
	write(fd, &myDataMessage[0], 64);

	while (!lock_ack.try_lock());
	memcpy(&localAck[0], ack[ack_index--], 10);
	lock_ack.unlock();

#if DEBUG
	fprintf(stdout, "ACK: ");
	for (int i = 0; i < 10; ++i)
		fprintf(stdout, "%u |", localAck[i]);
	fprintf(stdout, "\n");
#endif

	if (memcmp(&localAck[0], &ACK_OK_HEADER[0], 5)) {
	fprintf(stderr, "[TEST FAILED]: Second buffer\n");
	ack_thread.detach();
	return EXIT_FAILURE;
}
	
	printf("[TEST PASSED]\n");

	/* Let the thread go */
	ack_thread.detach();

	/* Close file descriptor */
	close(fd);

	/* Free allocated memory */
	delete [] ledBuffer;

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
	
	if (select(fd + 1, &set, NULL, NULL, &timeout) > 0)
		read(fd, &ack[++ack_index], ACK_SIZE);

	lock_ack.unlock();
}

	return NULL;
}
