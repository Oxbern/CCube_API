#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <mutex>

#include "DeviceShape.h"
#include "Utils.h"

#include "Request.h"
#include "Answer.h"
#include "Ack.h"
#include "Question.h"

#define DEBUG 1

/* File descriptor used */
int fd = 0;
fd_set set;

/* Up to 10 ACKs can be stored */
uint8_t ack[10][10];   
uint8_t ack_index = 0;
struct timeval timeout = {0, 10000};

std::recursive_mutex lock_ack;

/* User functions */
void *waitForACK();

/**
 * \brief  Test function
 * 
 * Sets a message and send it over USB
 *         Get the ACK sent back
 */
int main()
{
    /* Opens the connection in non blocking mode */
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

    /* Checks for error */
    if (fd < 0) 
        fd = open("/dev/stdout", O_RDWR | O_NOCTTY);
    
    /* Sets blocking mode */
    fcntl(fd, F_SETFL, 0);

    /* clear the set */
    FD_ZERO(&set); 
    /* add our file descriptor to the set */
    FD_SET(fd, &set); 

    /* Defines ACK thread */
    std::thread ack_thread(waitForACK);
	
    /* Creates a device shape */
    DeviceShape ds(9, 9, 9);

    ds.on(4, 4, 4);
    // /\* Turns on one LED *\/
    // for (int i = 0; i < 9 ; i++) {
    //     ds.on(i,i,8-i);
    //     ds.on(i,i,i);
    //     ds.on(i,8-i,i);
    //     ds.on(8-i, i, i);
    // }
    
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
    uint8_t* reqLinear = new uint8_t[SIZE_QUESTION]();

    uint8_t* buffLinear = new uint8_t[SIZE_BUFFER]();
    
    /* Resets the connection */
    Request resetConnection(1, 0, RESET);
    resetConnection.getListBuffer()[0].toArray(reqLinear);

#if DEBUG
    std::cout << "Reset Connection : " << resetConnection.toStringDebug() << "\n";
#endif

    /* Sents it over USB */
    //    write(fd, reqLinear, SIZE_QUESTION);

    /* Retrieves the ACK */
    while (!lock_ack.try_lock()) {
    }

    /* Creates an ACK */
    Ack localAck(1, ack[ack_index][2]);
    
    ack_index--;
    
    lock_ack.unlock();

    if (!(localAck.getListBuffer()[0].getHeader() == 1 &&
          localAck.getID() == 1 &&
          localAck.getAckType() == ACK_OK &&
          localAck.getListBuffer()[0].getSizeLeft() == 3))
        {
            std::cout << "[TEST FAILED] : Reset connection\n";
            ack_thread.detach();
            return EXIT_FAILURE;
        }

#if DEBUG
    std::cout << "ACK : " << localAck.toStringDebug() << "\n";
#endif

    /* Sends the Request */
    for (int i = 0; i<myRequest.NbBuffers(); i++) {

        /* Prints */
#if DEBUG
        std::cout << "My Request buffer " << i << " : " 
                  << myRequest.getListBuffer()[i].toStringDebug(i) << "\n";
#endif

        /* Sends it over USB */
        myRequest.getListBuffer()[i].toArray(buffLinear);
        write(fd, buffLinear, SIZE_BUFFER);        

        /* Retrieves the ACK */
        while (!lock_ack.try_lock()) {
        }

        /* Creates an ACK */
        Ack localAck(1, ack[ack_index][2]);
    
        ack_index--;
    
        lock_ack.unlock();

        if (!(localAck.getListBuffer()[0].getHeader() == 1 &&
              localAck.getID() == 1 &&
              localAck.getAckType() == ACK_OK &&
              localAck.getListBuffer()[0].getSizeLeft() == 3))    
            {
                std::cout << "[TEST FAILED] : Buffer number : "<< i <<"\n";
                ack_thread.detach();
                return EXIT_FAILURE;
            }
        /* Prints the ACK */
#if DEBUG
        std::cout << "ACK : " << localAck.toStringDebug() << "\n";
#endif
    }    

    std::cout << "[TEST PASSED]\n";
    ack_thread.detach();
    close(fd);

    delete [] buffLinear;
    delete [] reqLinear;
    delete [] ledBuffer;
    
    return 0;
}








/*!
 * \fn void *waitForACK()
 * \brief Read a ACK message from USB
 */
void *waitForACK()
{
	/* uint8_t emptyAck[10] = {0}; */

	while (1) {
		
	while (!lock_ack.try_lock());
	
	if (select(fd + 1, &set, NULL, NULL, &timeout) > 0)
		read(fd, &ack[++ack_index], SIZE_ACK);

	lock_ack.unlock();
}

	return NULL;
}
