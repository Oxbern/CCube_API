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
struct timeval timeout = {0, 1000000L};

uint8_t ACK_OK_HEADER[5] = {1, 1, 1, 0, 3};


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
        fprintf(stderr, "[TEST FAILED]: Unable to open connection\n");
        return EXIT_FAILURE;
    }

    /* Set blocking mode */
    fcntl(fd, F_SETFL, 0);

    /* clear the set */
    FD_ZERO(&set);
    /* add our file descriptor to the set */
    FD_SET(fd, &set);


                                /* Reset the connection */

    uint8_t resetConnection[7] = {0};

    /* Manually set header */
    resetConnection[0] = 1;
    resetConnection[1] = 1;
    resetConnection[2] = 0xFF;
    resetConnection[3] = 0;
    resetConnection[4] = 0;

    /* Send it over USB (Don't wait for ACK)*/
    write(fd, &resetConnection[0], 7);


                                /* Send message to turn on one led */

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

    /* Manually set header */
    myDataMessage[0] = 1;
    myDataMessage[1] = 1;
    myDataMessage[2] = 0x42;
    myDataMessage[3] = 0;
    myDataMessage[4] = 92;

    /* Copy data into the buffer */
    ds.toArray(ledBuffer);
    memcpy(&myDataMessage[5], ledBuffer, 57);

    /* Set CRC */
    crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t));

    myDataMessage[62] = crc >> 8;
    myDataMessage[63] = crc & 0xFF;

#if DEBUG
    printBuffer("BUFFER", &myDataMessage[0], 64);
#endif

    /* Send it over USB */
    if (write(fd, &myDataMessage[0], 64) == -1)
        printf("Error while send buffer over USB\n");

    /* Wait for ACK response */
    if (select(fd + 1, &set, NULL, NULL, &timeout) > 0)
        read(fd, &localAck[0], ACK_SIZE);

#if DEBUG
    printBuffer("ACK", &localAck[0], 10);
#endif

    /* Not a ACK_OK */
    if (memcmp(&localAck[0], &ACK_OK_HEADER[0], 5)) {
        fprintf(stderr, "[TEST FAILED]: First buffer\n");
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
    printBuffer("BUFFER", &myDataMessage[0], 64);
#endif

    /* Send it over USB */
    if (write(fd, &myDataMessage[0], 64) == -1)
        printf("Error while send buffer over USB\n");

    /* Wait for ACK response */
    if (select(fd + 1, &set, NULL, NULL, &timeout) > 0)
        read(fd, &localAck[0], ACK_SIZE);

#if DEBUG
    printBuffer("ACK", &localAck[0], 10);
#endif

    /* Not a ACK_OK */
    if (memcmp(&localAck[0], &ACK_OK_HEADER[0], 5)) {
        fprintf(stderr, "[TEST FAILED]: Second buffer\n");
        return EXIT_FAILURE;
    }

    printf("[TEST PASSED]\n");

    /* Close file descriptor */
    close(fd);

    /* Free allocated memory */
    delete [] ledBuffer;

    return 0;
}
