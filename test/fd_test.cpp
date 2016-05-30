#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "DeviceShape.h"


#define Response_MAX_SIZE 512

int main () {

	int fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY);

	if (fd < 0) {
		fprintf(stderr, "Error openning file\n");
		return EXIT_FAILURE;
	}
		
	DeviceShape ds(9, 9, 9);

	ds.on(4, 4, 4);

	uint8_t *myDataMessage = (uint8_t *)calloc(92, sizeof(uint8_t));

	myDataMessage[0] = 1;
	myDataMessage[1] = 1;
	myDataMessage[2] = 0x10;
	myDataMessage[3] = 0;
	myDataMessage[4] = 92;

	memcpy(&myDataMessage[5], ds.toArray(), 57);

	printf("My Data Message:");
	for (int i = 0; i < 64; ++i)
		printf("%u |", myDataMessage[i]);
	printf("\n");

	write(fd, &myDataMessage[0], 64);


	uint8_t ack[10];

	fcntl(fd, F_SETFL, 0);

	read(fd, &ack[0], Response_MAX_SIZE);

	printf("ACK:");
	for (int i = 0; i < 10; ++i)
		printf("%u |", ack[i]);
	printf("\n");



	myDataMessage[0] = 0;
	myDataMessage[4] = 35;

	memcpy(&myDataMessage[5], ds.toArray() + 57, 57);

	printf("My Data Message:");
	for (int i = 0; i < 64; ++i)
		printf("%u |", myDataMessage[i]);
	printf("\n");


	write(fd, &myDataMessage[0], 64);

	read(fd, &ack[0], Response_MAX_SIZE);

	printf("ACK:");
	for (int i = 0; i < 10; ++i)
		printf("%u |", ack[i]);
	printf("\n");
	
	close(fd);

	return 0;
}
