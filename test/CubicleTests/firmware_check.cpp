#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "DeviceShape.h"
#include "Utils.h"

/* User variable definition */
#define ACK_SIZE 10

#define DEBUG 1

/* File descriptor used  */
int fd = -1;

uint8_t ACK_OK_HEADER[5] = {1, 1, 1, 0, 3};


/* User function */
void handleAck(uint8_t *emptyAck, uint8_t *myDataMessage);


/**
 * @brief  Manually set a message and send it over USB
 *         Get the ACK sent back
 */
int main ()
{
                                /* Open connection */

    /* Open connection in non blocking mode */
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

    /* Check for error */
    if (fd < 0) {
        fprintf(stderr, "[TEST FAILED]: Unable to open connection\n");
        return EXIT_FAILURE;
    }

    /* Set non blocking mode */
    fcntl(fd, F_SETFL, 0);


                                /* Define variables used here */

    /* Create a device shape */
    DeviceShape ds(9, 9, 9);

    /* Turn on one LED */
    ds.on(4, 4, 4);

    /* Create a data message */
    uint8_t myDataMessage[64] = {0};
    uint8_t emptyAck[10] = {0};

    uint8_t *ledBuffer = new uint8_t[92];
    ds.toArray(ledBuffer);

    uint16_t crc;


                                /* First buffer */

    /* Manually set header */
    myDataMessage[0] = 1;
    myDataMessage[1] = 1;
    myDataMessage[2] = 0x42;
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

    handleAck(&emptyAck[0], &myDataMessage[0]);


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

    handleAck(&emptyAck[0], &myDataMessage[0]);

    printf("[TEST PASSED]\n");


                                /* End connection */

    /* Close file descriptor */
    close(fd);

    /* Free allocated memory */
    delete [] ledBuffer;

    return 0;
}

uint8_t *send(uint8_t *myDataMessage)
{
    uint8_t *ack = (uint8_t *)calloc(10, sizeof(uint8_t));

    /* Send it over USB */
    write(fd, &myDataMessage[0], 64);

    /* Wait for ACK response */
    read(fd, &ack[0], 10);

    printBuffer("ACK", ack, 10);

    return ack;
}

void handleAck(uint8_t *emptyAck, uint8_t *myDataMessage)
{
    if (memcmp(&emptyAck[0], &ACK_OK_HEADER[0], 5)) {
        return handleAck(send(myDataMessage), myDataMessage);
    }

    return;
}
