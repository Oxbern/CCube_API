#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main () {

	int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	char c = 's';
	
	write(fd, &c, sizeof(char));

	return 0;
}
