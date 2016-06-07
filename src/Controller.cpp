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
 * \def std::atomic<bool> notified
 * \brief TODO
 */
std::atomic<bool> notified = ATOMIC_VAR_INIT(false);

/*!
 * \brief Constructor
 *
 * Creates a controller,
 * lists all USB connected devices and adds them to the Device list
 *
 */
Controller::Controller()
{
    listAndGetUSBConnectedDevices(*this);

    /*Device *dev = new Device("/dev/stdout", 1);

      if (devices.size() == 0){
      // Connect to stdout to write messages
      devices.push_back(dev);
      connectDevice(dev);
      }
    */

    this->connectedDevice = NULL;

    LOG(1, "Controller()");
}

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

/*!
 * \brief Reads an ACK message from USB
 */
void *Controller::waitForACK()
{
    while (1) {
        if (this->connectedDevice == NULL)
            break;

        uint8_t *buff = new uint8_t[SIZE_ACK];
        if (this->connectedDevice != NULL) {

            if (this->connectedDevice->readFromFileDescriptor(buff)) {

                lock_ack.lock();
                buffReceived.push(buff);
                lock_ack.unlock();

                printBuffer("ACK PUSHED", buffReceived.front(), SIZE_ACK);
                LOG(1, "[THREAD] Lock released");
            }
        }

        delete []buff;
    }

    return NULL;
}

/*!
 * \brief TODO
 * \param mess Message
 * \return
 */
bool Controller::send(OutgoingMessage* mess)
{
    if (this->connectedDevice == NULL)
        return false;

    LOG(2, "[SEND] Send a message :\n" + mess->toStringDebug());

    int nbBuffer = mess->NbBuffers();
    for (int currentBuffNb = 0; currentBuffNb < nbBuffer; currentBuffNb++) {
        LOG(2, "[SEND] Buffer N° " + std::to_string(currentBuffNb));

        //Convert the buffer i to an array
        int sizeBuffer = mess->getListBuffer()[currentBuffNb].getSizeBuffer();
        uint8_t *bufferArray = new uint8_t[sizeBuffer];
        mess->getListBuffer()[currentBuffNb].toArray(bufferArray);

        int sendingTries = 0;
        int nbTry = 0;

        uint8_t *ack = new uint8_t[SIZE_ACK];
        memset(ack, 0, SIZE_ACK);
        uint8_t refAck[SIZE_ACK] = {1, 1, 1, 0, 3, bufferArray[2],
                                    bufferArray[3], bufferArray[4], 0, 0};

        do {
            //Send the message to the Device
            while (!connectedDevice->writeToFileDescriptor(bufferArray,
                                                           sizeBuffer)) {
                if (++sendingTries > MAX_SENDING_TRIES)
                    throw ErrorException("Error while sending a message : "
                                         "Number of tries to send "
                                         "the message exceeded");
            } /* Buffer sent */
            LOG(5, "Buffer sent");


            lock_ack.lock();
            if (!buffReceived.empty()) {
                ack = buffReceived.front();
                buffReceived.pop();
            }
            lock_ack.unlock();

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
        } else
            LOG(2, "[HANDLER] Ack handled");

        //Free allocated memory for the bufferArray
        delete []bufferArray;
        delete []ack;
    }

    LOG(1, "[SEND] Message sended");
    return true;
}

/*!
 * \brief TODO
 * \param mess
 * \param currentBuff
 * \param nbTry
 * \param nbWait
 * \param isAcknowledged
 * \return bool
 */
bool Controller::handleNewMessage(OutgoingMessage *mess, int currentBuff, int *nbTry, int *nbWait, bool *isAcknowledged)
{
    bool retValue = true;

    *nbWait = 0;
    LOG(1, "[HANLDER] Handle an ack");
    uint8_t *ack;

    //The oldest ack received
    ack = buffReceived.front();

    //Try to take the lock
    lock_ack.lock();  //TODO timeout
    //Remove the oldest ack in the queue
    buffReceived.pop();
    //Release the lock
    lock_ack.unlock();

    LOG(1, "[THREAD] Lock released");

    //Check the header bit
    if(ack[HEADER_INDEX] == 1) {
        uint16_t sizeLeftPack =
            convertTwo8to16(ack[DATA_INDEX+1],
                            ack[DATA_INDEX+2]);

        //check id message
        //ConnectedDevice may not be NULL
        if (ack[ID_INDEX] == connectedDevice->getID()
            && ack[DATA_INDEX] == mess->getListBuffer()[currentBuff].getOpCode()
            && sizeLeftPack == mess->getListBuffer()[currentBuff].getSizeLeft()) {

            /* /\* Print ack *\/ */
            /* this->getConnectedDevice()->handleResponse(ack); //TODO to remove */

            //Check opcode validity
            uint8_t  opcode = ack[OPCODE_INDEX];

            if (isAValidAnswerOpcode(opcode)) {
                //if valid opcode

                if (isAnAckOpcode(opcode)) {
                    //Create an Ack instance
                    Ack ackMess(connectedDevice->getID(), opcode);
                    ackMess.encodeAck(sizeLeftPack, ack[DATA_INDEX]);

                    //Handle the ack
                    *isAcknowledged = connectedDevice->handleAck(mess,
                                                                 ackMess,
                                                                 currentBuff);
                    //Increment the number of tries if not aknowledged
                    if ((*isAcknowledged) == false)
                        *nbTry = *nbTry + 1;
                } else {
                    //Response message
                    //TODO handle the response
                }
            }
        }
    }

    return retValue;
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
            ack_thread = std::thread(&Controller::waitForACK, this);
            return true;
        }
    }
    return false;
}

/*!
 * \brief Disconnects the controller from the device
 * \return
 */
bool Controller::disconnectDevice()
{
    LOG(1, "disconnectDevice() \n");
    ack_thread.detach();
    if (this->connectedDevice != NULL)
        while (!connectedDevice->disconnect()); //TODO Timeout

    this->connectedDevice = NULL;
    return true;
}

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
