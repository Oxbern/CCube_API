#include <cstring>
#include <fstream>

#include "Device.h"
#include "ErrorException.h"
#include "Utils.h"
#include "VirtualCube.h"
#include "Message.h"

Device::Device(){
    
}

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
    //if (id.length() > 0) {
    this->id = id;
        //} else {
        //throw ErrorException("Wrong id");
        //}

    //Size initialization
    // if (sizeX < 0 || sizeY < 0 || sizeZ < 0) {
    //     throw ErrorException("Invalid size of display");
    // } else{
    //     this->sizeX = sizeX;
    //     this->sizeY = sizeY;
    //     this->sizeZ = sizeZ;
    // }
        this->sizeX = 9;
        this->sizeY = 9;
        this->sizeZ = 9;
    //Luminosity initialization
    this->luminosity = -1.0;

    //Not available by default
    this->isAvailable = false;

    this->currentConfig = new DeviceShape(sizeX,sizeY,sizeZ);
}

Device::~Device()
{
    LOG(1, "DeviceShape destructor called");
    std::cout << "~Device()\n";
    delete this->currentConfig;
}

bool Device::available()
{
    DataMessage m(this->id, 0, OPCODE(AVAILABLE));
    while (!this->send(&m)) {
        //TODO Timeout
        continue;
    }

    return this->isAvailable;
}

bool Device::connect(){
    LOG(1, "Trying to connect the device");
    if (!file.is_open()) {
        file.open(port, std::ios::in | std::ios::out);
    }

    LOG(1, "Device connected");
    return (file.is_open());
}

bool Device::disconnect()
{
    LOG(1, "Trying to disconnect the device");
    if (file.is_open()) {
        file.close();
    }
    LOG(1, "Device disconnected");
    return (!file.is_open());
}

bool Device::display()
{
    uint16_t size = sizeX*sizeY*sizeZ/8; // Convert to bytes
    DataMessage dm(this->id, size,OPCODE(BUFF_SENDING));
    dm.encode(currentConfig->toArray());
    if (!send(&dm)){
        std::cerr << "Error while sending ledBuffer"<<std::endl;
        return false;
    }
    return true;
}

bool Device::updateFirmware()
{
    return false;
}

float Device::getLuminosity()
{
    return 0.0;
}

std::string Device::getFirmwareVersion()
{
    return 0;
}

bool Device::askForDisplaySize()
{
    return false;
}

bool Device::send(Message *mess)
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

        std::string buffString = mess->getBuffer()[i].toString();
        LOG(1, "Message toString : " + mess->getBuffer()[i].toStringDebug(i));

        if (this->port.compare("/dev/stdin") == 0) {
            //VirtualCube
            uint8_t * bufferArray = new uint8_t[mess->getBuffer()[i].getSizeBuffer()];
            mess->getBuffer()[i].toArray(bufferArray);
            //Virtual sending
            // CDC_Receive_FS(bufferArray);
            delete [] bufferArray;
        } else {
            while (!write(buffString)) {
                //TODO Timeout
                continue;
            }
        }
    }
    LOG(1, "Message sended" );
    return true;
}

int Device::getID() const
{
    return this->id;
}

std::string Device::getPort() const
{
    return this->port;
}

DeviceShape *Device::getcurrentConfig() const{
    return this->currentConfig;
}


bool Device::write(std::string data)
{
    if(this->file.is_open()) {
        this->file << data << std::endl;
        LOG(1, "Data written to file");
        return true;
    }else {
        LOG(1, "Unable to write data to file");
        return false;
    }
}

std::fstream & Device::getFile()
{
    return this->file;
}
