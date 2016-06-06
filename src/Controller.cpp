#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <ErrorException.h>
#include <iostream>
#include <fstream>

#include "Controller.h"
#include "RequestMessage.h"
#include "SetMessage.h"

/*!
 * \brief Constructor
 *
 * Creates a controller, 
 * lists all USB connected devices and adds them to the Device list
 *
 */
Controller::Controller() :
    ParentController()
{
    LOG(1, "Controller()");
}

/*!
 * \brief Destructor
 *
 */
Controller::~Controller()
{
    LOG(1,"~Controller()");
}

/*! 
 * \brief Switches on a led on the current connected device
 * \param x
 * \param y
 * \param z
 * \return bool
 */
bool Controller::on(int x, int y, int z)
{
    return connectedDevice->on(x,y,z);
}

/*! 
 * \brief Switches off a led on the current connected device
 * \param x
 * \param y
 * \param z
 * \return bool
 */
bool Controller::off(int x, int y, int z)
{
    return connectedDevice->off(x,y,z);
}

/*! 
 * \brief Switches off the entire device
 * \return bool
 */
bool Controller::off()
{
    return connectedDevice->off();
}

/*! 
 * \brief Sets the state of a led to its opposite on the current connected device
 * \param x
 * \param y
 * \param z
 * \return bool
 */
bool Controller::toggle(int x, int y, int z)
{
    return connectedDevice->toggle(x,y,z);
}

/*!
 * \brief TODO
 * \return bool
 */
bool Controller::display()
{
    //Create a DataMessage
    DataMessage dm(connectedDevice->getID(),
                   connectedDevice->getcurrentConfig()->getSizeInBytes(),
                   OPCODE(BUFF_SENDING));

    //Encode the message with the DeviceShape of the Device
    uint8_t *ledsBuffer = new uint8_t[connectedDevice->getcurrentConfig()->getSizeInBytes()];
    connectedDevice->getcurrentConfig()->toArray(ledsBuffer);
    dm.encode(ledsBuffer);

    //Deallocate memory
    delete[] ledsBuffer;

    if (!send(&dm)) {
        std::cerr << "Error while sending ledBuffer" << std::endl;
        return false;
    }

    return true;
}

/*!
 * \brief Sets the device's luminosity
 * \return bool
 */
bool Controller::setLuminosity()
{
    // Create a set message, with its crc
    SetMessage sl(connectedDevice->getID(), LIGHT_SENDING);

    // Calcuate its CRC
    if (!send(&sl)) {
        std::cerr << "Error while sending the set message" << std::endl;
        return false;
    }
    
    return true;        
}

/*!
 * \todo look into the entire list of devices ? or only ask the connected one ?
 * \todo use the available parameter of device
 * \brief TODO
 * \return bool
 */
bool Controller::available()
{
    // Create a request message, with its crc
    RequestMessage av(connectedDevice->getID(), AVAILABLE);

    if (!send(&av)) {
        std::cerr << "Error while sending request" << std::endl;
        return false;
    }

    return true;    
}

/*!
 * \brief Returns the luminosity of the LEDs on the Device
 * \return the value of the luminosity
 */
uint8_t Controller::getLuminosity()
{
    // Create a request message, with its crc
    RequestMessage gl(connectedDevice->getID(), LIGHT_ASKING);

    if (!send(&gl)) {
        std::cerr << "Error while sending request" << std::endl;
        return false;
    }

    return 1;
}

/*!
 * \brief Returns the version of the firmware
 * \return the version
 */
uint8_t Controller::getVersionFirmware()
{
    // Create a request message, with its crc
    RequestMessage vf(connectedDevice->getID(), FIRMWARE_VERSION_ASKING);

    if (!send(&vf)) {
        std::cerr << "Error while sending request" << std::endl;
        return false;
    }
    return 1;
}

/*!
 * \brief Send the firmware update
 * \return bool
 */
bool Controller::updateFirmware(const std::string& myFile)
{
    std::streampos size;
    char * memblock;

    uint8_t* data;
    
    std::ifstream file(myFile, std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        size = file.tellg();
        memblock = new char [size]();

        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();
        data = new uint8_t[size]();
        
        memcpy(data, (const uint8_t*)memblock, size);            
        
        LOG(3, "the entire file content is in memblock \n");

        delete [] memblock;
        
        LOG(3, "size is " + std::to_string(size) + " bytes.");
    
        // Create a data message
        DataMessage uf(1, size, FIRMWARE_UPDATE_SENDING);
        uf.encode(data);

        LOG(3, "firmware update message : " + uf.toStringDebug());

        delete [] data ;

        // if (!send(&uf)) {
        //     std::cerr << "Error while sending request" << std::endl;
        //     return false;
        // }
        
        
    } else
        std::cout << "Unable to open file " << myFile << " \n";
    return true;
}
