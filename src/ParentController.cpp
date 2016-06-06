#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <ErrorException.h>
#include <chrono>
#include <atomic>

#include "ParentController.h"

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
ParentController::ParentController()
{
    listAndGetUSBConnectedDevices();

    /*Device *dev = new Device("/dev/stdout", 1);

      if (devices.size() == 0){
      // Connect to stdout to write messages
      devices.push_back(dev);
      connectDevice(dev);
      }
    */

    this->connectedDevice = NULL;

    LOG(1, "ParentController()");
}

/*!
 * \brief Destructor
 *
 */
ParentController::~ParentController()
{
    LOG(1,"~ParentController()");
    while(!devices.empty()) delete devices.front(), devices.pop_front();
    delete this->connectedDevice;
}

/*!
 * \brief Reads an ACK message from USB
 */
void *ParentController::waitForACK()
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
bool ParentController::send(Message* mess)
{
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
        if ((this->getConnectedDevice()->getPort().compare("/dev/stdin") == 0)
            || (this->getConnectedDevice()->getPort().compare("/dev/stdout") == 0)) {
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
        printBuffer("ACK OK", ackOKBuff, SIZE_ACK);

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
                                    throw ErrorException("Error in an ack message "
                                                                 ": buffer to retransmit not found in the message");
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

            std::cerr << "Number of tries to send the message exceeded\n";
            /*throw ErrorException("Error while sending a message : "
              "Number of tries to send "
              "the message exceeded");*/
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
bool ParentController::handleNewMessage(Message *mess, int currentBuff, int *nbTry, int *nbWait, bool *isAcknowledged)
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
 * \brief Lists all devices which are connected via USB
 * \return TODO
 */
bool ParentController::listAllDevices()
{
    LOG(1, "listAllDevices()\n");

    std::cout << "--- List of USB Connected Devices : ---" << std::endl;
    std::list<Device*>::iterator iter ;
    int i = 1;
    for(iter = devices.begin() ; (iter != devices.end()) ;iter++){
        std::cout << "Device  "  << i << ": Id = " << (*iter)->getID()
                  << ", Port :" << (*iter)->getPort() <<  "\n";
        i++;
    }
    if (!strcmp((*(devices.begin()))->getPort().c_str(),"/dev/stdout") ) {
        std::cout << "No device connected, connection to stdout\n";
        return false;
    }
    return true;
}

/*!
 * \brief Connects the controller to a device chosen from the list
 * \return
 */
bool ParentController::connectDevice()
{
    LOG(1, "connectDevice() \n");
    Device *chosen;

    if (listAllDevices()){

        int choice = 0;
        std::cout << "Enter the device's ID you want to connect : " << std::endl;
        std::cin >> choice;

        std::list<Device*>::iterator iter ;
        for(iter = devices.begin() ; (iter != devices.end()) ;iter++){
            if (choice == (*iter)->getID())
                chosen = *iter;
        }

        std::cout << "You choose Device " << (int) chosen->getID() << std::endl;
        if (connectDevice(chosen)){
            std::cout << "You are connected to " << getConnectedDevice()->getPort()  << std::endl;
            return true;
        }
    }
    return false;
}

/*!
 * \brief Gets the port of the connected device from its ID
 * \param id of the device to get the port from
 * \return string
 */
std::string ParentController::getPortFromID(int id)
{
    std::list<Device*>::iterator iter ;
    for(iter = devices.begin() ; (iter != devices.end()) ;iter++){
        if (id == (*iter)->getID())
            return (*iter)->getPort();
    }
    return "No Device with this ID";
}

/*!
 * \brief Connects the controller to a device with its ID
 * \param id ID of the device to connect
 * \return 
 */
bool ParentController::connectDevice(int id)
{
    LOG(1, "connectDevice(int id) \n");
    Device *chosen;

    std::list<Device*>::iterator iter ;
    for(iter = devices.begin(); (iter != devices.end()); iter++){
        if (id == (*iter)->getID())
            chosen = *iter;
    }

    return connectDevice(chosen);
}

/*!
 * \brief Connects the controller to the Device specified in argument
 * \param d device to connect
 * \return bool
 */
bool ParentController::connectDevice(Device *d)
{
    LOG(1, "connectDevice(Device*) \n");

    if ((*d).connect()){
        this->connectedDevice = d;
        ack_thread = std::thread(&ParentController::waitForACK, this);
        return true;
    }
    return false;
}

/*!
 * \brief Disconnects the controller from the device
 * \return 
 */
bool ParentController::disconnectDevice()
{
    LOG(1, "disconnectDevice() \n");
    ack_thread.detach();
    while (!connectedDevice->disconnect()); //TODO Timeout
    this->connectedDevice = NULL;
    return true;
}

/*!
 * \brief Accessor to the current connected device
 * \return the current connected device
 */
Device* ParentController::getConnectedDevice()
{
    LOG(1, "getConnectedDevice() \n");
    return this->connectedDevice;
}

/*!
 * \brief Accessor to the list of USB connected devices
 * \return the list of USB connected devices
 */
std::list<Device*> ParentController::getListDevices()
{
    LOG(1, "getListDevices() \n");

    return this->devices;
}

/*****************************************************
 *****************************************************
 **   Auxiliar functions to get connected devices   **
 *****************************************************
 ****************************************************/

/*!
 * \fn void getNextWord(char *path, int *j, char * wordreturn)
 * \brief Gets the next word in a char
 * \param path the line to parse
 * \param j the beginning of the future parsing
 * \param wordreturn
 */
void getNextWord(char *path, int *j, char *wordreturn)
{
    char word[10] = {'0'};
    int w = 0, k = *j;

    /* Read char until space */
    while (path[k] != ' ')
        word[w++]=path[k++];
    word[k]='\0';

    /* Set return values */
    *j = k;
    strcpy(wordreturn, word);
}

/*!
 * \fn Dictionnary *getDictSTM(int *nbSTM)
 * \brief Gets the result of a "lsusb | grep STM" system call in a Dictionnary(Bus:Device) structure
 * \param nbSTM the number of STM devices connected to return
 * \return
 */
Dictionnary *getDictSTM(int *nbSTM)
{
    FILE *fp = popen("lsusb | grep STM ", "r");
    if (fp == NULL) {
        std::cerr << "Failed to run command\n";
        exit(1);
    }

    char path[100];
    int lines = 0;
    /* Get the number of line */
    while (fgets(path, sizeof(path)-1, fp) != NULL)
        lines++;
    *nbSTM = lines;

    /* Close the file */
    pclose(fp);


    /* Create a new dictionnary */
    Dictionnary *dic = new Dictionnary[lines];

    //Re-Open the command for reading.
    fp = popen("lsusb | grep STM ", "r");
    if (fp == NULL) {
        std::cerr << "Failed to run command\n";
        exit(1);
    }

    bool new_entry = false;
    int j = 0, k = 0;
    /* Read each line */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        new_entry = false;
        /* Until end of line char appear or one device is found */
        while(path[j] != '\0' && !new_entry){

            /* Check if path if long enough to execute memcmp */
            for (int i = j; i < j + 4; ++i)
                if (path[++i] == '\0') {
                    j = i;
                    continue;
                }

            if (!memcmp(&path[j], "Bus", 3)) {
                j += 4;
                /* Get bus name */
                char bus[10];
                getNextWord(path, &j, (char *)&bus);
                dic[k].bus = atoi(bus);
            }


            /* Check if path if long enough to execute memcmp */
            for (int i = j; i < j + 7; ++i)
                if (path[++i] == '\0') {
                    j = i;
                    continue;
                }

            if (!memcmp(&path[j], "Device", 6)) {
                j += 7;
                char device[10];
                getNextWord(path,&j,(char *) &device);
                dic[k].Device = atoi(device);
                new_entry = true;
            }

            j++;
        }
        /* Go to the next line */
        j = 0;
        /* And add a new device */
        ++k;
    }

    /* Close the file */
    pclose(fp);

    /* Return created dic */
    return dic;
}

/*!
 * \fn bool isInDico(std::string echo, Dictionnary *dic, int sizeOfDic)
 * \brief Tests if the ttyPort corresponds to a STM device
 * \param echo the ttyPort
 * \param dic the Dictionnary to look into
 * \param sizeOfDic the Dictionnary's size
 * \return true if the ttyPort corresponds to a STM device
 */
bool isInDico(std::string echo, Dictionnary *dic, int sizeOfDic)
{
    /* Copy tty port into local variable */
    char busSDev[echo.length() + 1];
    strcpy(busSDev, echo.c_str());

    /* Get the name of the Bus */
    int bus = 0;
    char wordB[10];
    int w = 0;

    while (busSDev[w] != '/') {
        wordB[w]=busSDev[w];
        ++w;
    }
    wordB[w]='\0';

    /* Copy the bus into a new variable to use atoi function */
    char wordBreturn[w + 1];
    strcpy(wordBreturn, wordB);
    bus = atoi(wordBreturn);

    /* Get the name of the Device */
    int Device = 0;
    char wordD[10] = {'0'};
    ++w;

    int k = 0;
    while(busSDev[w] != '\0')
        wordD[k++] = busSDev[w++];
    wordD[k]='\0';

    /* Copy the device into a new variable to use atoi function */
    char wordDreturn[k + 1];
    strcpy(wordDreturn, wordD);
    Device = atoi(wordDreturn);

    /* Actually check if the interface is in the dictionnary */
    for (int i = 0; i < sizeOfDic; ++i)
        if (bus == dic[i].bus && Device == dic[i].Device )
            return true;


    /* Default return value */
    return false;
}

/*!
 * \brief Displays the list of all USB connected devices 
 * and pushes them in the device list
 */
void ParentController::listAndGetUSBConnectedDevices()
{
    LOG(1, "listAndGetUSBConnectedDevices() \n");

    /* Open the command for reading. */
    FILE *fp = popen("ls /dev/tty*  ", "r");
    if (!fp) {
        std::cerr << "Failed to run command\n";
        exit(1);
    }

    char path[20];
    int lines = 0;

    /* Calculate number of lines in the file */
    while (fgets(path, sizeof(path)-1, fp))
        lines++;

    /* Close the file and re-open it */
    pclose(fp);
    fp = popen("ls /dev/tty*  ", "r");

    char ttyList[lines][20];

    for (int j = 0; j < lines; j++)
        /* Copy TTY path in TTY list */
        strcpy(&ttyList[j][0], fgets(path, sizeof(path)-1, fp));

    /* Close the file */
    pclose(fp);

    int nbSTM = 0;
    Dictionnary *dic =  getDictSTM(&nbSTM);

    int DeviceID = 1;

    for (int i = 0; i < lines; i++){
        std::string name = ttyList[i];

        name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());

        std::string cmd = "echo /dev/bus/usb/`udevadm info --name="
            + name +   " --attribute-walk | sed -n 's/\\s*ATTRS{\\(\\(devnum\\) "
            + "\\|\\(busnum\\)\\)}==\\\"\\([^\\\"]\\+\\)\\\"/\\4/p' | head -n 2 "
            + "| awk '{$1 = sprintf(\"%03d\", $1); print}'` | tr \" \" \"\\/\"";

        //Open the command for reading.
        fp = popen(cmd.c_str(), "r");
        if (fp == NULL) {
            std::cerr << "Failed to run command\n";
            exit(1);
        }

        char path[50];

        //Read the output a line at a time - output it.
        while (fgets(path, sizeof(path)-1, fp) != NULL) {

            if (strcmp(path, "/dev/bus/usb/\n")){
                std::string t = path;
                std::string s = "/dev/bus/usb/";

                std::string::size_type i = t.find(s);

                if (i != std::string::npos)
                    t.erase(i, s.length());

                std::cout << name << std::endl;
                /* if (isInDico(t, dic, nbSTM)) */
                // We have a device here with his port name (string)
                devices.push_back(new Device(name, DeviceID++));
            }
        }

        pclose(fp);
    }

    /* Free all allocated memory */
    delete [] dic;
}
