#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <thread>
#include <mutex>
#include <queue>

#include "DeviceShape.h"
#include "Utils.h"

/* User variable definition */
#define ACK_SIZE 10

#define DEBUG 1


/* File descriptor used  */
int fd = 0;
fd_set set;

struct timeval timeout = {0, 1000000L};

uint8_t ACK_OK_HEADER[5] = {1, 1, 1, 0, 3};

std::queue<uint8_t*> message_queue;
std::mutex message_lock;

/* User functions */
void *waitForACK();
void handleAck(uint8_t *ack);


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


    /* Define ACK thread */
    std::thread ack_thread(waitForACK);

    /* Create a device shape */
    DeviceShape ds(9, 9, 9);

    /* Turn on one LED */
    ds.on(4, 4, 4);

    /* Create a data message */
    uint8_t myDataMessage[64] = {0};

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

    /* Set CRC */
    crc = computeCRC(&myDataMessage[0], 62*sizeof(uint8_t));

    myDataMessage[62] = crc >> 8;
    myDataMessage[63] = crc & 0xFF;

#if DEBUG
    printBuffer("Message", myDataMessage, 64);
#endif

    message_lock.lock();
    message_queue.push(myDataMessage);
    message_lock.unlock();

    /* Send it over USB */
    if (write(fd, &myDataMessage[0], 64) == -1)
        printf("Error while send buffer over USB\n");




                                /* Second buffer */


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
    printBuffer("Message", myDataMessage, 64);
#endif

    /* Send the buffer */
    write(fd, &myDataMessage[0], 64);

    message_lock.lock();
    message_queue.push(myDataMessage);
    message_lock.unlock();



                                /* End connection */

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
    uint8_t ack[10] = {0};

    while (1) {

        if (select(fd + 1, &set, NULL, NULL, &timeout) > 0) {
            read(fd, &ack[0], ACK_SIZE);
            handleAck(ack);
        }
    }

    return NULL;
}


void handleAck(uint8_t *ack)
{
    if (memcmp(ack, ACK_OK_HEADER, 5)) {
        uint8_t buffer[64];
        message_lock.lock();
        memcpy(buffer, message_queue.front(), 64);
        message_queue.pop();
        message_queue.push(buffer);
        message_lock.unlock();
        write(fd, buffer, 64);

        message_lock.lock();
        memcpy(buffer, message_queue.front(), 64);
        message_queue.pop();
        message_queue.push(buffer);
        message_lock.unlock();
        write(fd, buffer, 64);

    } else {
        message_lock.lock();
        message_queue.pop();
        message_queue.pop();
        message_lock.unlock();
    }
}
