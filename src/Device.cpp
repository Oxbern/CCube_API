#include <cstring>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <aio.h>


#include "Device.h"
#include "ErrorException.h"
#include "Utils.h"
#include "VirtualCube.h"
#include "Message.h"

/**
 * @brief TODO
 */
Device::Device(std::string port, int id)
{
    LOG(1, "Device constructor called");
    //Copy device's port
    if (port.length() > 0) {
        this->port = std::string(port);
    } else {
        throw ErrorException("Wrong port");
    }

    //Copy device's id
    if (id > 0) {
        this->id = id;
    } else {
        throw ErrorException("Wrong id");
    }

    //Size initialization
    //TODO Ask the size to the device
    this->sizeX = 9;
    this->sizeY = 9;
    this->sizeZ = 9;

    //Luminosity initialization
    this->luminosity = -1.0;

    //Not available by default
    this->isAvailable = false;

    this->currentConfig = new DeviceShape(sizeX,sizeY,sizeZ);
}

/**
 * @brief TODO
 */
Device::~Device()
{
    LOG(1, "Device destructor called");
    delete this->currentConfig;
}

/**
 * @brief TODO
 */
bool Device::available()
{
    DataMessage dm(this->id, 0, OPCODE(AVAILABLE));

    if (!send(&dm)){
        std::cerr << "Error while checking if the device availability" << std::endl;
        return false; //TODO See if unavailable or just error while sending buffer
    }
    return this->isAvailable;
}

/**
 * @brief TODO
 */
bool Device::connect(){
    LOG(1, "Trying to connect the device");
    if (!file.is_open()) {
        file.open(port, std::ios::in | std::ios::out); //TODO app flag usefull ?
    }

    LOG(1, "Device " + std::string((file.is_open() ? "connected" : "not connected")));
    return (file.is_open());
}

/**
 * @brief TODO
 */
bool Device::disconnect()
{
    LOG(1, "Trying to disconnect the device");
    if (file.is_open()) {
        file.close();
    }
    LOG(1, "Device disconnected");
    return (!file.is_open());
}

/**
 * @brief TODO
 */
bool Device::display()
{
    DataMessage dm (this->id, currentConfig->getSizeInBytes(), OPCODE(BUFF_SENDING));
    uint8_t *buffer = currentConfig->toArray();
    dm.encode(buffer);
    delete[](buffer);

    if (!send(&dm)){
        std::cerr << "Error while sending ledBuffer" << std::endl;
        return false;
    }
    
    return true;
}

/**
 * @brief TODO
 */
bool Device::updateFirmware()
{
    return false;
}

/**
 * @brief TODO
 */
float Device::getLuminosity()
{
    DataMessage dm(this->id, 0, OPCODE(LIGHT_RECEPTION));

    if (!send(&dm)){
        std::cerr << "Error while asking the device brightness" << std::endl;
        return false; //TODO See if unavailable or just error while sending buffer
    }
    return this->luminosity;
}

/**
 * @brief TODO
 */
std::string Device::getFirmwareVersion()
{
    return 0;
}

/**
 * @brief TODO
 */
bool Device::askForDisplaySize()
{
    return false;
}

/**
 * @brief TODO
 */
bool Device::write(uint8_t* data, int dataSize)
{
    if(this->file.is_open()) {
        LOG(2, "Buffer send (size = " + std::to_string(dataSize)
               + " Bytes) : " + uint8ArrayToString(data, dataSize));

        if (this->file.write((char *)data, dataSize)){
            LOG(1, "Data written to file");
            return true;
        }else{
            LOG(1, "Error while writing data to file");
        }

    }else {
        LOG(1, "Unable to write data to file");
    }
    return false;
}

/**
 * @brief TODO
 */
bool Device::send(Message* mess)
{
	
	LOG(1, "Sending message");
    if (!file.is_open()) {
        while (!connect()) {
            //TODO Timeout
            continue;
        }
    }
    int n = mess->NbBuffers();
    for (int i = 0; i < n; i++) {
        int sizeBuffer = mess->getBuffer()[i].getSizeBuffer();
        uint8_t * buffString = new uint8_t[sizeBuffer];
        mess->getBuffer()[i].toArray(buffString);

        LOG(3, mess->toStringDebug());

        if ((this->port.compare("/dev/stdin") == 0) || (this->port.compare("/dev/stdout") == 0)) {
            //VirtualCube
            LOG(2, "Buffer send (size = " + std::to_string(sizeBuffer)
                   + " Bytes) : " + uint8ArrayToString(buffString, sizeBuffer));

	        LOG(1, "Virtual sending");
            //Virtual sending
            uint8_t* buffer = CDC_Receive_FS(buffString);
            delete []buffer;

        } else {
	        write(buffString, sizeBuffer);
	        uint8_t ack[10] = "initializ";

	        // // Send the buffer
	        // write(buffString, sizeBuffer);
	
	        // Disconnect from the cube
	        file.close();

	        //memcpy(ack, getAck(fd), 10);

	        int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

	        uint8_t *output = new uint8_t[sizeBuffer];
	        aiocb output_cb;
	        
	        memcpy(output, buffString, sizeBuffer);

	        memset(&output_cb, 0, sizeof(aiocb));
	        output_cb.aio_nbytes = sizeBuffer;
	        output_cb.aio_fildes = fd;
	        output_cb.aio_offset = 0;
	        output_cb.aio_buf = output;

	        aio_write(&output_cb);
	        fdatasync(fd);
	        
	        // create the buffer
	        uint8_t* input = new uint8_t[10];
	
	        // create the control block structure
	        aiocb input_cb;
	
	        memset(&input_cb, 0, sizeof(aiocb));
	        input_cb.aio_nbytes = 10;
	        input_cb.aio_fildes = fd;
	        input_cb.aio_offset = 0;
	        input_cb.aio_buf = input;
	
	        // read!
	        if (aio_read(&input_cb) == -1)
		        {
			        std::cout << "Unable to create request!" << std::endl;
			        close(fd);
		        }
	
	        std::cout << "Request enqueued!" << std::endl;
	
	        // wait until the request has finished
	        while(aio_error(&input_cb) == EINPROGRESS)
		        {
			        std::cout << "Working..." << std::endl;
		        }
	
	        // success?
	        int numBytes = aio_return(&input_cb);
	
	        if (numBytes != -1)
		        std::cout << "Success!" << std::endl;
	        else
		        std::cout << "Error!" << std::endl;
	
	        // now clean up
	        close(fd);
	        
	        // // Wait for the ack response
	        // uint8_t ack[10];

	        // memcpy(ack, getAck(), 10);

	        // Print ack message
	        for (int k = 0; k < 10; ++k)
		        std::cout << (int)input[k] << "| ";
	        std::cout << "\n";

	        // Re-connect with the cube
	        this->connect();
	        
        }
        delete []buffString;
    }
    LOG(1, "Message sended" );

    return true;
}

uint8_t *Device::getAck() {
	// Open connection (not blocking mode)
	int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	fcntl(fd, F_SETFL, FNDELAY);

	// create the buffer
	char* buffer = new char[10];
	
	// create the control block structure
	aiocb cb;
	
	memset(&cb, 0, sizeof(aiocb));
	cb.aio_nbytes = 10;
	cb.aio_fildes = fd;
	cb.aio_offset = 0;
	cb.aio_buf = buffer;
	
	// read!
	if (aio_read(&cb) == -1)
	{
		std::cout << "Unable to create request!" << std::endl;
		close(fd);
	}
	
	std::cout << "Request enqueued!" << std::endl;
	
	// wait until the request has finished
	while(aio_error(&cb) == EINPROGRESS)
	{
		std::cout << "Working..." << std::endl;
	}
	
	// success?
	int numBytes = aio_return(&cb);
	
	if (numBytes != -1)
		std::cout << "Success!" << std::endl;
	else
		std::cout << "Error!" << std::endl;
	
	// now clean up
	close(fd);

	return (uint8_t *)buffer;
	
	
	// if(fd == -1) {
	// 	printf( "failed to open port\n" );
	// }

	// // Config the serial communication
	// struct termios  config;

	// // Check if this actually is a TTY device
	// if(!isatty(fd)) { printf("Not a TTY device\n"); }

	// // Get the current configuration
	// if(tcgetattr(fd, &config) < 0) { printf("Unable to retrieve the configuration\n"); }

	// // Config input flags
	// config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
	//                     INLCR | PARMRK | INPCK | ISTRIP | IXON);
	// config.c_iflag |= IGNPAR;
	// config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	// config.c_cflag &= ~(CSIZE | PARENB);
	// config.c_cflag |= CS8 | CREAD | CLOCAL;

	// config.c_cc[VMIN]  = 0;
	// config.c_cc[VTIME] = 1;
 
	// if(cfsetispeed(&config, B9600) < 0 || cfsetospeed(&config, B9600) < 0) {
	// 	printf("Unable to set the speed\n");
	// }

	// if(tcsetattr(fd, TCSANOW, &config) < 0) { printf("Unable to set the config\n"); }


	// FILE *input = fdopen(fd, "w+");
	
	// // int index = 0,
	// // 	c = 0;
	
	// uint8_t *buf = (uint8_t *)calloc(10, sizeof(uint8_t));
	
	// // fcntl(fd, F_SETFL, 0);

	// // while (read(fd, &c, 1) > 0) {
	// // 	buf[index] = c;
	// // 	index ++;
	// // 	printf("Byte read: %d\n", c);
	// // }

	// int c;
	// do {
	// 	c = fgetc(input);
	// 	printf("Byte read: %d\n", c);
	// } while (c != EOF);
	
	// close(fd);
	
	// return buf;
}

/**
 * @brief TODO
 */
int Device::getID() const
{
    return this->id;
}

/**
 * @brief TODO
 */
std::string Device::getPort() const
{
    return this->port;
}

/**
 * @brief TODO
 */
DeviceShape *Device::getcurrentConfig() const{
    return this->currentConfig;
}

/**
 * @brief TODO
 */
bool Device::on(int x, int y, int z)
{
    return currentConfig->on(x, y, z);
}

/**
 * @brief TODO
 */
bool Device::off()
{
    return currentConfig->off();
}

/**
 * @brief TODO
 */
bool Device::off(int x, int y, int z)
{
    return currentConfig->off(x, y, z);
}

/**
 * @brief TODO
 */
bool Device::toggle(int x, int y, int z)
{
    return currentConfig->toggle(x, y, z);
}

/**
 * @brief TODO
 */
std::fstream& Device::getFile()
{
    return this->file;
}
