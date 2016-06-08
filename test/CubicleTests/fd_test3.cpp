#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <thread>
#include <mutex>
#include <queue>

#include "DeviceShape.h"
#include "Request.h"
#include "Utils.h"
#include "Controller.h"

#define DEBUG 1

/* File descriptor used */
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
 * \brief  Test function
 * 
 * Sets a message and send it over USB
 *         Get the ACK sent back
 */
int main()
{
    /* Opens the connection in non blocking mode */
#ifdef _WIN32
    fd = open("COM7", O_RDWR | O_NOCTTY);
#else
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
#endif
    /* Check for error */
    if (fd < 0) {
        fprintf(stderr, "[TEST FAILED]: Unable to open connection\n");
        return EXIT_FAILURE;
    }

    /* Sets blocking mode */
#ifdef _WIN32
    //To make blocking:
    unsigned long off = 0;
    if (ioctlsocket(fd, FIONBIO, &off) != 0)
        {
            /* Handle failure. */
        }
#else
    fcntl(fd, F_SETFL, 0);
#endif

    /* clear the set */
    FD_ZERO(&set); 
    /* add our file descriptor to the set */
    FD_SET(fd, &set); 

    /* Defines ACK thread */
    std::thread ack_thread(waitForACK);
	
    /* Creates a device shape */
    DeviceShape ds(9, 9, 9);

    ds.on(4, 4, 4);
    /* Turns on one LED */
    for (int i = 0; i < 9 ; i++) {
        ds.on(i,i,8-i);
        ds.on(i,i,i);
        ds.on(i,8-i,i);
        ds.on(8-i, i, i);
    }
    
    /* Creates a Request */ 
    Request myRequest(1, 92, SET_LEDSTATS);

    /* Encodes data into the buffers created by the Request */
    uint8_t  *ledBuffer = new uint8_t [ds.getSizeInBytes()];
    ds.toArray(ledBuffer);
    myRequest.encode(ledBuffer);

    /* Prints the message */

#if DEBUG
    std::cout << "My Request : " << myRequest.toStringDebug() << "\n";
#endif

    //     uint8_t* reqLinear = new uint8_t[SIZE_REQUEST];
    //     reqLinear={0};
    
    //     /* Resets the connection */
    //     RequestMessage resetConnection(1, RESET);
    //     resetConnection.encodeCrc();
    //     resetConnection.getListBuffer()[0].toArray(reqLinear);

    // #if DEBUG
    //     std::cout << "Reset Connection : " << resetConnection.toStringDebug() << "\n";
    // #endif

    /* Sents it over USB */
    //    write(fd, reqLinear, SIZE_REQUEST);
    // message_lock.lock();
    // message_queue.push(buffLinear);
    // message_lock.unlock();

    uint8_t* buffLinear = new uint8_t[SIZE_BUFFER]();
    
    /* Sends the Request */
    for (int i = 0; i<myRequest.NbBuffers(); i++) {

        /* Prints */
#if DEBUG
        std::cout << "My Request buffer " << i << " : " 
                  << myRequest.getListBuffer()[i].toStringDebug(i) << "\n";
#endif

        /* Sends it over USB */
        myRequest.getListBuffer()[i].toArray(buffLinear);

#if DEBUG
        printBuffer("BUFFER ", buffLinear, SIZE_BUFFER);
#endif
        /* Send it over USB */
        if (write(fd, buffLinear, SIZE_BUFFER) == -1)
            std::cout << "error while sending buffer number " << i << " over USB \n";

        message_lock.lock();
        message_queue.push(buffLinear);
        message_lock.unlock();

    }    

    std::cout << "[TEST PASSED]\n";
    ack_thread.detach();
    close(fd);

    delete [] buffLinear;
    //    delete [] reqLinear;
    delete [] ledBuffer;
    
    return 0;
}








/*!
 * \fn void *waitForACK()
 * \brief Read a ACK message from USB
 */
void *waitForACK()
{
    uint8_t ack[10] = {0};

    while (1) {

        if (select(fd + 1, &set, NULL, NULL, &timeout) > 0) {
            read(fd, &ack[0], SIZE_ACK);
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
