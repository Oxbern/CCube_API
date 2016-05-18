#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>

void set_led_line(int fd) {
    int i = 0;
    uint8_t buffer[64];

    //Beginning frame
    buffer[i] = 0x01;
    i++;

    //Operation code
    buffer[i] = 0x10;
    i++;

    //Size od data
    buffer[i] = 0x5c;
    i++;

    //Data
    for (int ind = 0; ind < 92; ind++) {
        if (i == 64) {
            printf("Data sent :");
            for(int d =0; d < 64; d++)
                printf("%x ", (int)buffer[d]);
            printf("\n");

            write(fd, buffer, 64);
            i = 0;
        }

        if (ind == 0)
            buffer[i] = 0xaa;
        else {
            if (i != 91)
                buffer[i] = 0x0;
            else
                buffer[i] = 0x01;
        }
        i++;
    }

    //CRC (0 for the while)
    buffer[i] = 0x00;
        i++;
    buffer[i] = 0x00;
        i++;

    printf("Data sent :");
    for(int d =0; d < 64; d++)
        printf("%x ", (int)buffer[d]);
    printf("\n");

    write(fd, buffer, i);
}

int main(int argc, char* argv[])
{
    int fd = -1;

    // Parsing of arguments
    if (argc != 9){
	printf("Usage : ./main --dev /dev/ttyACM0 -x x -y y -z z\n");
	exit(0);
    }
  
    if (strcmp(argv[1], "--dev")){
	printf("Precise which cube you want to use with --dev CubeToUse\n");
	exit(0);
    }
    const char* port = argv[2];

    int x = 0, y = 0, z = 0;
    if (strcmp(argv[3], "-x")){
	printf("Precise coords with -x x -y y -z z\n");
	exit(0);
    }
    x = atoi(argv[4]);

    if (strcmp(argv[5], "-y")){
	printf("Precise coords with -x x -y y -z z\n");
	exit(0);
    }
    y = atoi(argv[6]);

    if (strcmp(argv[7], "-z")){
	printf("Precise coords with -x x -y y -z z\n");
	exit(0);
    }
    z = atoi(argv[8]);


    //Connection
    if (fd != -1) {
        close(fd);
    }
    fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("Wrong file descriptor\n");
        return -1;
    }

    printf("------ Connection successfull ------ \n");

    set_led_line(fd);

    close(fd);

    printf("------ Connection closed ------ \n");
    return EXIT_SUCCESS;
}

    
