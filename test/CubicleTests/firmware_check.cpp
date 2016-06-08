#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "DeviceShape.h"
#include "Utils.h"

#ifdef _WIN32
#include "Controller.h"
#endif

/* User variable definition */
#define ACK_SIZE 10

#define DEBUG 1

/* File descriptor used  */
int fd = -1;

uint8_t ACK_OK_HEADER[5] = {1, 1, 1, 0, 3};



/**
 * @brief  Manually set a message and send it over USB
 *         Get the ACK sent back
 */
int main ()
{
                                /* Open connection */

    /* Open connection in blocking mode */
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

    /* Check for error */
    if (fd < 0) {
        fprintf(stderr, "[TEST FAILED]: Unable to open connection\n");
        return EXIT_FAILURE;
    }

    fcntl(fd, F_SETFL, 0);

    /* Define variables used here */

    /* Create a device shape */
    DeviceShape ds(9, 9, 9);

    /* Turn on one LED */
    ds.on(1, 1, 1);

    /* Create array needed below */
    uint8_t myDataMessage[64] = {0};
    uint8_t emptyAck[10] = {0};

    uint8_t *ledBuffer = new uint8_t[92];
    /* Compute ledBuffer array */
    ds.toArray(ledBuffer);

    uint16_t crc;


                                /* First buffer */

    /* Manually set header */
    myDataMessage[0] = 1;
    myDataMessage[1] = 1;
    myDataMessage[2] = 0x21;
    myDataMessage[3] = 0;
    myDataMessage[4] = 92;

    /* Copy data into the buffer */
    memcpy(&myDataMessage[5], ledBuffer, 57);

    /* Compute CRC */
    crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t));

    /* And set CRC */
    myDataMessage[62] = crc >> 8;
    myDataMessage[63] = crc & 0xFF;

#if DEBUG
    printBuffer("BUFFER", &myDataMessage[0], 64);
#endif

    /* Send it over USB */
    write(fd, &myDataMessage[0], 64);

    read(fd, &emptyAck[0], SIZE_ACK);

#if DEBUG
    printBuffer("ACK", &emptyAck[0], SIZE_ACK);
#endif


                                /* Second buffer */

    /* Prepare next buffer to send */
    myDataMessage[0] = 0;
    myDataMessage[4] = 35;

    /* Copy the rest of the data in the buffer */
    memcpy(&myDataMessage[5], ledBuffer + 57, 35);

    /* Compute CRC */
    crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t));

    /* And set CRC */
    myDataMessage[62] = crc >> 8;
    myDataMessage[63] = crc & 0xFF;

#if DEBUG
    printBuffer("BUFFER", &myDataMessage[0], 64);
#endif

    /* Send it over USB */
    write(fd, &myDataMessage[0], 64);

    read(fd, &emptyAck[0], SIZE_ACK);

#if DEBUG
    printBuffer("ACK", &emptyAck[0], SIZE_ACK);
#endif

    printf("[TEST PASSED]\n");


                                /* End connection */

    /* Close file descriptor */
    close(fd);

    /* Free allocated memory */
    delete [] ledBuffer;

    return 0;
}
