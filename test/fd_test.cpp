#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <pthread.h>

#include "DeviceShape.h"

#define Response_MAX_SIZE 512

pthread_t ack_thread;


void *waitForACK(void *arg) {

	int *fd = (int *)arg;

	uint8_t ack[10] = {0};
	uint8_t emptyAck[10] = {0};
		
	// Get ack
	read(*fd, &ack[0], Response_MAX_SIZE);

	if (memcmp(ack, emptyAck, 10)) {
		fprintf(stdout, "ACK: ");
		for (int i = 0; i < 10; ++i)
			fprintf(stdout, "%u |", ack[i]);
		fprintf(stdout, "\n");
	}

	return NULL;
}

int getAck(int fd){
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


int main () {

	int fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY);
	fcntl(fd, F_SETFL, 0);

	if(pthread_create(&ack_thread, NULL, waitForACK, &fd)) {
		fprintf(stderr, "Error creating thread\n");
		return EXIT_FAILURE;	
	}
	
	if (fd < 0) {
		fprintf(stderr, "Error opening file\n");
		close(fd);
		return EXIT_FAILURE;
	}
		
	DeviceShape ds(9, 9, 9);

	ds.on(4, 4, 4);

	uint8_t *myDataMessage = (uint8_t *)calloc(92, sizeof(uint8_t));

	myDataMessage[0] = 1;
	myDataMessage[1] = 1;
	myDataMessage[2] = 0x42;
	myDataMessage[3] = 0;
	myDataMessage[4] = 92;

	memcpy(&myDataMessage[5], ds.toArray(), 57);

	printf("My Data Message:");
	for (int i = 0; i < 64; ++i)
		printf("%u |", myDataMessage[i]);
	printf("\n");

	write(fd, &myDataMessage[0], 64);

	getAck(fd);
	
	// myDataMessage[0] = 0;
	myDataMessage[4] = 35;

	memcpy(&myDataMessage[5], ds.toArray() + 57, 57);

	printf("My Data Message:");
	for (int i = 0; i < 64; ++i)
		printf("%u |", myDataMessage[i]);
	printf("\n");
	
	write(fd, &myDataMessage[0], 64);

	getAck(fd);
	
	close(fd);

	return 0;
}
