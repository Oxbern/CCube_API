#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <mutex>

#include "DeviceShape.h"
#include "DataMessage.h"
#include "AckMessage.h"
#include "RequestMessage.h"

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
    /* /\* Turns on one LED *\/ */
    /* for (int i = 0; i < 9 ; i++) { */
    /*     ds.on(i,i,8-i); */
    /*     ds.on(i,i,i); */
    /*     ds.on(i,8-i,i); */
    /*     ds.on(8-i, i, i); */
    /* } */
    /* Creates a DataMessage */ 
    DataMessage myDataMessage(1, 92, BUFF_SENDING);

    /* Encodes data into the buffers created by the DataMessage */
    uint8_t  *ledBuffer = new uint8_t [ds.getSizeInBytes()];
    ds.toArray(ledBuffer);
    myDataMessage.encode(ledBuffer);


    /* Prints the message */

#if DEBUG
    std::cout << "My DataMessage : " << myDataMessage.toStringDebug() << "\n";
#endif

    uint8_t* buffLinear = new uint8_t[SIZE_BUFFER];
    
    /* Resets the connection */
    RequestMessage resetConnection(1, RESET);

    /* Sents it over USB */
    write(fd, &resetConnection.getListBuffer()[0], SIZE_REQUEST);

    /* Retrieves the ACK */
    while (!lock_ack.try_lock()) {
    }

    /* Creates an ACK */
    AckMessage localAck(1, ack[ack_index][2]);
    
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

    /* Sends the DataMessage */
    for (int i = 0; i<myDataMessage.NbBuffers(); i++) {

        /* Prints */
#if DEBUG
        std::cout << "My DataMessage buffer " << i << " : " 
                  << myDataMessage.getListBuffer()[i].toStringDebug(i) << "\n";
#endif

        /* Sends it over USB */
        myDataMessage.getListBuffer()[i].toArray(buffLinear);
        write(fd, buffLinear, SIZE_BUFFER);        

        /* Retrieves the ACK */
        while (!lock_ack.try_lock()) {
        }

        /* Creates an ACK */
        AckMessage localAck(1, ack[ack_index][2]);
    
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
