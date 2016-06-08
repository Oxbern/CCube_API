#include <mutex>
#include <atomic>

#include "Controller.h"
#include "LinuxUtils.h"

#include "Question.h"
#include "Request.h"

#include "ErrorException.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \def MAX_TRY
 * \brief TODO, explain timeout
 */
#define MAX_TRY 10

/*!
 * \def MAX_WAIT
 * \brief TODO, explain timeout
 */
#define MAX_WAIT 1000000

/*!
 * \def MAX_SENDING_TRIES
 * \brief TODO
 */
#define MAX_SENDING_TRIES 5



/*!
 * \brief Constructor
 *
 * Creates a controller,
 * lists all USB connected devices and adds them to the Device list
 *
 */
Controller::Controller()
{
#ifdef _WIN32
    Device *d = new Device("COM7",1);
    devices.push_back(d);
#else
    listAndGetUSBConnectedDevices(*this);
#endif

    this->connectedDevice = NULL;
    this->secure = false;

    LOG(1, "Controller()");
}




/*!
 * \brief Connects the controller to a device with its ID
 * \param id ID of the device to connect
 * \return
 */
bool Controller::connectDevice(int id)
{

    LOG(1, "connectDevice(int id) \n");
    Device *chosen = NULL;

    std::list<Device*>::iterator iter ;
    for(iter = devices.begin(); (iter != devices.end()); iter++){
        if (id == (*iter)->getID())
            chosen = *iter;
    }

    if (chosen != NULL) {
        if (chosen->connect()){
            this->connectedDevice = chosen;
            return true;
        }
    }
    return false;
}

/*!
 * \brief Connects the controller to a device with its ID
 * \param id ID of the device to connect
 * \paran secure Flag to set ACK security
 * \return
 */
bool Controller::connectDevice(int id, bool secure)
{
    LOG(1, "connectDevice(int id) \n");
    Device *chosen = NULL;

    this->secure = secure;

    std::list<Device*>::iterator iter ;
    for(iter = devices.begin(); (iter != devices.end()); iter++){
        if (id == (*iter)->getID())
            chosen = *iter;
    }

    if (chosen != NULL) {
        if (chosen->connect()){
            this->connectedDevice = chosen;
            return true;
        }
    }
    return false;
}

/*!
 * \brief Connects the controller to a device with its ID
 * \param id ID of the device to connect
 * \paran secure Flag to set ACK security
 * \return
 */
bool Controller::connectDevice(char *port, bool secure)
{
    LOG(1, "connectDevice(char *port) \n");
    Device *chosen = NULL;

    this->secure = secure;

    std::list<Device*>::iterator iter ;
    for(iter = devices.begin(); (iter != devices.end()); iter++){
        if (!strcmp(port,(*iter)->getPort().c_str()))
            chosen = *iter;
    }

    if (chosen != NULL) {
        if (chosen->connect()){
            this->connectedDevice = chosen;
            return true;
        }
    }
    return false;
}


/*!
 * \brief TODO
 * \param mess Message
 * \return
 */
bool Controller::send(OutgoingMessage *mess)
{
    if (this->connectedDevice == NULL)
        return false;

    LOG(2, "[SEND] Send a message :\n" + mess->toStringDebug());

    int nbBuffer = mess->NbBuffers();
    for (int currentBuffNb = 0; currentBuffNb < nbBuffer; currentBuffNb++) {
        LOG(5, "[SEND] Buffer N° " + std::to_string(currentBuffNb));

        //Convert the buffer i to an array
        int sizeBuffer = mess->getListBuffer()[currentBuffNb].getSizeBuffer();
        uint8_t *bufferArray = new uint8_t[sizeBuffer];
        mess->getListBuffer()[currentBuffNb].toArray(bufferArray);

        int nbTry = 0;

        uint8_t *ack = new uint8_t[SIZE_ACK];
        memset(ack, 0, SIZE_ACK);
        uint8_t refAck[SIZE_ACK] = {1, 1, 1, 0, 3, bufferArray[2],
                                    bufferArray[3], bufferArray[4], 0, 0};

        do {
            //Send the message to the Device
            if (!connectedDevice->writeToFileDescriptor(bufferArray,
                                                   sizeBuffer)) {
                    throw ErrorException("Error while sending a message : "
                                         "Number of tries to send "
                                         "the message exceeded");
                    this->disconnectDevice();
            } /* Buffer sent */
            LOG(5, "Buffer sent");

            if (!secure)
                break;

            printBuffer("ACK", ack, SIZE_ACK);

            if (memcmp(ack, refAck, SIZE_ACK - 2))
                nbTry++;
            else
                break;

            std::cout << "Nb Try: " << nbTry << std::endl;
        } while(nbTry < MAX_TRY);

        //If number of tries exceeded
        if (nbTry == MAX_TRY) {
            LOG(2, "[HANDLER] NB TRY EXCEDEED");

            throw ErrorException("Error while receiving a ack: "
                                 "Number of tries to receive "
                                 "the ack exceeded");
        } else if (secure)
            LOG(2, "[HANDLER] Ack handled");

        //Free allocated memory for the bufferArray
        delete []bufferArray;
        delete []ack;
    }

    LOG(1, "[SEND] Message sended");
    return true;
}


/*!
 * \brief Disconnects the controller from the device
 * \return
 */
bool Controller::disconnectDevice()
{
    LOG(1, "disconnectDevice() \n");

    if (this->connectedDevice != NULL)
        while (!connectedDevice->disconnect()); //TODO Timeout

    this->connectedDevice = NULL;
    return true;
}



/* Functionnality methods */

/*!
 * \brief Sets the device's luminosity
 * \param value to set the luminosity to
 * \return bool
 */
bool Controller::setLuminosity(uint8_t value)
{
    if (this->connectedDevice != NULL) {
        // Create a set message, with its crc
        Request sl(connectedDevice->getID(), 1, SET_LUMINOSITY);
        sl.encode(&value);

        //Send the message
        send(&sl);

        return true;
    } else
        throw ErrorException("No device connected");
}


/*!
 * \todo look into the entire list of devices ? or only ask the connected one ?
 * \todo use the available parameter of device
 * \brief TODO
 * \return bool
 */
bool Controller::available()
{
    // // Create a request message, with its crc
    // Question av(connectedDevice->getID(), AVAILABLE);

    // if (!send(&av))
    //     throw ErrorException("Error while checking the "
    //                          "availability of the connected device");

    return true;
}


/*!
 * \brief Returns the luminosity of the LEDs on the Device
 * \return the value of the luminosity
 */
uint8_t Controller::getLuminosity()
{
    if (this->connectedDevice != NULL) {
        // Create a request message, with its crc
        Question gl(connectedDevice->getID(), GET_LUMINOSITY);

        //Send the message
        if (!send(&gl))
            throw ErrorException("Error while asking the luminosity "
                                         "of the connected device");

        return 1; //TODO To modify with the good value
    } else
        throw ErrorException("No device connected");
}


/*!
 * \brief Returns the version of the firmware
 * \return the version
 */
uint8_t Controller::getVersionFirmware()
{
    if (this->connectedDevice != NULL) {
        // Create a request message, with its crc
        Question vf(connectedDevice->getID(),
                          FIRMWARE_VERSION);

        if (!send(&vf))
            throw ErrorException("Error while asking the firmware version "
                                         "of the connected device");

        return 1;
    } else
        throw ErrorException("No device connected");
}


/*!
 * \brief Send the firmware update
 * \return bool
 */
bool Controller::updateFirmware(const std::string& myFile)
{
    if (connectedDevice != NULL) {
        std::streampos size;
        char *memblock;

        uint8_t *data;

        std::ifstream file(myFile, std::ios::in | std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            size = file.tellg();
            memblock = new char[size]();

            file.seekg(0, std::ios::beg);
            file.read(memblock, size);
            file.close();
            data = new uint8_t[size]();

            memcpy(data, (const uint8_t *) memblock, size);

            LOG(3, "the entire file content is in memblock \n");

            delete[] memblock;

            LOG(3, "size is " + std::to_string(size) + " bytes.");

            // Create a data message
            Request uf(connectedDevice->getID(),
                           size,
                           UPDATE_FIRMWARE);
            uf.encode(data);

            LOG(3, "firmware update message : " + uf.toStringDebug());

            delete[] data;


        } else
            throw ErrorException("Unable to open file " + myFile);

        return true;
    } else
        throw ErrorException("No device connected");
}



/* Destructor */

/*!
 * \brief Destructor
 *
 */
Controller::~Controller()
{
    LOG(1,"~Controller()");
    while(!devices.empty()) delete devices.front(), devices.pop_front();
    delete this->connectedDevice;
}



/* Device specific methods */

/*!
 * \brief Switches on a led on the current connected device
 * \param x
 * \param y
 * \param z
 * \return bool
 */
bool Controller::on(int x, int y, int z)
{
    if (connectedDevice != NULL)
        return connectedDevice->on(x,y,z);
    else
        throw ErrorException("No device connected");
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
    if (connectedDevice != NULL)
        return connectedDevice->off(x,y,z);
    else
        throw ErrorException("No device connected");
}


/*!
 * \brief Switches off the entire device
 * \return bool
 */
bool Controller::off()
{
    if (connectedDevice != NULL)
        return connectedDevice->off();
    else
        throw ErrorException("No device connected");
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
    if (connectedDevice != NULL)
        return connectedDevice->toggle(x,y,z);
    else
        throw ErrorException("No device connected");
}


/*!
 * \brief TODO
 * \return bool
 */
bool Controller::display()
{
    if (connectedDevice != NULL) {
        //Create a Request
        Request dm(connectedDevice->getID(),
                       connectedDevice->getcurrentConfig()->getSizeInBytes(),
                       OPCODE(SET_LEDSTATS));

        //Encode the message with the DeviceShape of the Device
        uint8_t *ledsBuffer = new uint8_t[connectedDevice->
                                          getcurrentConfig()->getSizeInBytes()];

        connectedDevice->getcurrentConfig()->toArray(ledsBuffer);
        dm.encode(ledsBuffer);

        //Deallocate memory
        delete[] ledsBuffer;

        //Send the message
        send(&dm);

        return true;
    } else
        throw ErrorException("No device connected");
}



/* Getters */

/*!
 * \brief Accessor to the current connected device
 * \return the current connected device
 */
Device* Controller::getConnectedDevice()
{
    LOG(1, "getConnectedDevice() \n");
    return this->connectedDevice;
}


/*!
 * \brief Accessor to the list of USB connected devices
 * \return the list of USB connected devices
 */
std::list<Device*> Controller::getListDevices()
{
    LOG(1, "getListDevices() \n");

    return this->devices;
}
