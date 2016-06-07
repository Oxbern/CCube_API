#include <mutex>
#include <atomic>

#include "Controller.h"
#include "LinuxUtils.h"
#include "DataMessage.h"
#include "RequestMessage.h"
#include "SetMessage.h"
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
#ifdef _WIN32
    Device *d = new Device("COM7",1);
    devices.push_back(d);
#else
    listAndGetUSBConnectedDevices(*this);
#endif
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
        SetMessage sl(connectedDevice->getID(), LIGHT_SENDING);
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
    // Create a request message, with its crc
    RequestMessage av(connectedDevice->getID(), AVAILABLE);

    if (!send(&av))
        throw ErrorException("Error while checking the "
                             "availability of the connected device");

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
        RequestMessage gl(connectedDevice->getID(), LIGHT_ASKING);

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
        RequestMessage vf(connectedDevice->getID(),
                          FIRMWARE_VERSION_ASKING);

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
            DataMessage uf(connectedDevice->getID(),
                           size,
                           FIRMWARE_UPDATE_SENDING);
            uf.encode(data);

            LOG(3, "firmware update message : " + uf.toStringDebug());

            delete[] data;

            //Send the message
            // if (!send(&uf)) {
            //     std::cerr << "Error while sending request" << std::endl;
            //     return false;
            // }

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

        uint8_t *buff = new uint8_t[10];
        if (this->connectedDevice != NULL) {
            if (this->connectedDevice->readFromFileDescriptor(buff)) {
                lock_ack.lock();
                /* LOG(1, "[THREAD] Lock taken"); */
                buffReceived.push(buff);
                lock_ack.unlock();
                notified = true;
                cond_var.notify_one();
                LOG(1, "[THREAD] Lock released");
            }
        }
    }

    return NULL;
}

/*!
 * \brief TODO
 * \param mess Message
 * \return 
 */
bool Controller::send(Message* mess)
{
    if (this->connectedDevice == NULL)
        return false;

    LOG(2, "[SEND] Send a message :\n" + mess->toStringDebug());

    std::unique_lock<std::mutex> lock(lock_ack);

    //Boolean to kwnow if each buffer is well received by the Device
    bool isAcknowledged = false;

    for (int currentBuffNb = 0; currentBuffNb < mess->NbBuffers(); currentBuffNb++) {
        LOG(2, "[SEND] Buffer N° " + std::to_string(currentBuffNb));

        //Convert the buffer i to an array
        int sizeBuffer = mess->getListBuffer()[currentBuffNb].getSizeBuffer();
        uint8_t * bufferArray = new uint8_t[sizeBuffer];
        mess->getListBuffer()[currentBuffNb].toArray(bufferArray);

        //Check weither the Device is virtual or not
        if ((connectedDevice->getPort().compare("/dev/stdin") == 0)
            || (connectedDevice->getPort().compare("/dev/stdout") == 0)) {
            //VirtualCube

            LOG(1, "Virtual sending");

        } else {
            //Physical Device
            //Send the message to the Device
            lock_ack.lock();
            connectedDevice->writeToFileDescriptor(bufferArray,
                                                   sizeBuffer);
            lock_ack.unlock();
        }

        /* Counter for the number of tries
           retransmission of a buffer */
        int nbTry = 0;

        isAcknowledged = false;

        //Define an Ack_OK
        uint8_t ackOKBuff[SIZE_ACK] = {1,
                                       (uint8_t) connectedDevice->getID(),
                                       ACK_OK, 0, 3,
                                       BUFF_SENDING,
                                       (uint8_t ) (mess->getListBuffer()[currentBuffNb].getSizeLeft() >> 8),
                                       (uint8_t ) (mess->getListBuffer()[currentBuffNb].getSizeLeft() & 0xFF),
                                       0, 0}; //TODO : Add CRC check

        //Wait for the receipt acknowledgement
        //while (!isAcknowledged /*&& nbTry < MAX_TRY*/) {
        /*if (nbWait == MAX_WAIT) {
          LOG(2, "[HANDLER] NB WAIT EXCEDEED");
          if (reSend++ < MAX_TRY)
          connectedDevice->writeToFileDescriptor(bufferArray,
          sizeBuffer);
          else {
          std::cerr << "Unable to send buffer after " << MAX_TRY
          << " attempts" << std::endl;
          if (disconnectDevice())
          std::cerr << "Disconnected" << std::endl;
          exit(1);
          }
          nbWait = 0;
          }*/

        do {
            //wait for new message
            while(!cond_var.wait_for(lock, std::chrono::milliseconds(1000), [](){return notified == true;})) {
                bufferArray[HEADER_INDEX] = 2;

                //Try to retransmit the wrong buffer
                LOG(2, "[HANLDER] RESEND");
                lock_ack.lock();
                connectedDevice->writeToFileDescriptor(bufferArray,
                                                       sizeBuffer);
                lock_ack.unlock();
            }

            notified = false;

            LOG(1, "[HANLDER] Handle an ack");
            //The oldest ack received
            uint8_t *ack;

            ack = buffReceived.front();

            //Try to take the lock
            lock_ack.lock();  //TODO timeout
            //Remove the oldest ack in the queue
            buffReceived.pop();
            //Release the lock
            lock_ack.unlock();

            if (memcmp(ack, ackOKBuff, SIZE_ACK)) {
                //ACK_NOK or ACK_ERR
                //Check the header bit
                if (ack[HEADER_INDEX] == 1) {
                    //check id message
                    //ConnectedDevice may not be NULL
                    if (ack[ID_INDEX] == connectedDevice->getID()) {
                        //Check data of ack
                        uint16_t sizeLeftPack = convertTwo8to16(ack[DATA_INDEX + 1],
                                                                ack[DATA_INDEX + 2]);
                        uint8_t opcodePack = ack[DATA_INDEX];

                        if (opcodePack == mess->getListBuffer()[currentBuffNb].getOpCode()
                            && sizeLeftPack == mess->getListBuffer()[currentBuffNb].getSizeLeft()) {

                            //Check opcode validity
                            uint8_t opcode = ack[OPCODE_INDEX];

                            //if valid opcode
                            if (isAnAckOpcode(opcode)) {
                                //ACK_ERR or ACK_NOK

                                //Search the buffer to retransmit from the message
                                Buffer *bufferToRetransmit = mess->getBuffer(opcodePack, sizeLeftPack);
                                if (bufferToRetransmit == NULL) {
                                    std::cerr << "Error in an ack message : "
                                                 ": buffer to retransmit not "
                                                 "found in the message"; //TODO to remove
                                    return false;
                                }

                                //Convert array to retransmit to an array of uint8_t
                                uint8_t buffToRetransmit[mess->getSizeBuffer()];
                                bufferToRetransmit->toArray(buffToRetransmit);

                                //ReSend the message to the Device
                                //The header bit is set to 2
                                buffToRetransmit[HEADER_INDEX] = 2;

                                //Try to retransmit the wrong buffer
                                LOG(2, "[HANLDER] RESEND");
                                lock_ack.lock();
                                connectedDevice->writeToFileDescriptor(buffToRetransmit,
                                                                       sizeBuffer);
                                lock_ack.unlock();
                                //Increment the number of tries if not aknowledged
                                nbTry++;
                            }
                        }
                    }
                }
            } else
                isAcknowledged = true;
        } while(!isAcknowledged);

        //Free allocated memory for the bufferArray
        delete []bufferArray;

        //If number of tries exceeded
        if (nbTry == MAX_TRY) {
            LOG(2, "[HANDLER] NB TRY EXCEDEED");

            std::cerr << "Number of tries to send the message exceeded\n"; //TODO to remove
            /*throw ErrorException("Error while sending a message : "
              "Number of tries to send "
              "the message exceeded");*/
            return false;
        } else
            LOG(2, "[HANDLER] Ack handled");
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
bool Controller::handleNewMessage(Message *mess, int currentBuff, int *nbTry, int *nbWait, bool *isAcknowledged)
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
                    //Create an AckMessage instance
                    AckMessage ackMess(connectedDevice->getID(), opcode);
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

