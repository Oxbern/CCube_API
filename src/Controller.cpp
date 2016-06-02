#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <ErrorException.h>

#include "Controller.h"

#define MAX_TRY 10

/**
 * @brief Constructor of Controller object, list all USB connected devices and
 *        add them to the Device list
 */
Controller::Controller()
{
	listAndGetUSBConnectedDevices();

	Device *dev = new Device("/dev/stdout", 1);

    if (devices.size() == 0){
        // Connect to stdout to write messages
        devices.push_back(dev);
        connectDevice(dev);
    }

    this->connectedDevice = dev;

    LOG(1, "Controller()");
}

/**
 * @brief Destructor of Controller object
 */ 
Controller::~Controller()
{
    LOG(1,"~Controller()");
    while(!devices.empty()) delete devices.front(), devices.pop_front();
    delete this->connectedDevice;
}


/**
 * @brief Read a ACK message from USB
 */
void *Controller::waitForACK()
{
	while (1) {		
		if (this->connectedDevice == NULL)
			break;
		
		while (!lock_ack.try_lock()); //LOG(2, "Try to lock (in Thread)");

        uint8_t *buff = new uint8_t[10];
        if (this->connectedDevice != NULL) {
            this->connectedDevice->readFromFileDescriptor(buff);
            buffReceived.push(buff);
        }

		lock_ack.unlock();
	}

	return NULL;
}

/**
 * @brief TODO
 */
bool Controller::send(Message* mess)
{
    LOG(1, "Sending message");
    //Check if the device is connected
    if (this->getConnectedDevice() != NULL) {
	    while (!this->getConnectedDevice()->connect()); //TODO Timeout
    }

    int n = mess->NbBuffers();

    //Boolean to kwnow if each buffer is well received by the Device
    bool isAcknowledged = false;
    /* //Boolean to kwnow if the lock on the queue of ack is taken */
    /* bool isLockTaken = false; */

    for (int i = 0; i < n; i++) {
        isAcknowledged = false;

        //Convert the buffer i to an array
        int sizeBuffer = mess->getListBuffer()[i].getSizeBuffer();
        uint8_t * bufferArray = new uint8_t[sizeBuffer];
        mess->getListBuffer()[i].toArray(bufferArray);

        LOG(3, mess->toStringDebug());

        //Check weither the Device is virtual or not
        if ((this->getConnectedDevice()->getPort().compare("/dev/stdin") == 0)
            || (this->getConnectedDevice()->getPort().compare("/dev/stdout") == 0)) {
            //VirtualCube

            LOG(2, "Buffer send (size = " + std::to_string(sizeBuffer)
                + " Bytes) : " + uint8ArrayToString(bufferArray, sizeBuffer));
            LOG(1, "Virtual sending");

        } else {
            //Physical Device
            //Send the message to the Device
	        while (!connectedDevice->writeToFileDescriptor(bufferArray,
                                                           sizeBuffer));
        }

        /* Counter for the number of tries
          retransmission of a buffer */
        int nbTry = 0;

        //Wait for the receipt acknowledgement
        while (!isAcknowledged && nbTry < MAX_TRY) {
            /* isLockTaken = false; */

            //Check for new message
            if (!buffReceived.empty()) {
                LOG(2, "Handle an ack");

                //Try to take the lock
                while (!lock_ack.try_lock());// LOG(2, "Try to lock (in Send)"); //TODO timeout
                /* isLockTaken = true; */
                LOG(2, "Lock Taken");

                //The oldest ack received
                uint8_t *ack = buffReceived.front();
                //Remove the oldest ack in the queue
                buffReceived.pop();

                lock_ack.unlock();
                /* isLockTaken = false; */

                /* Print ack */
                this->getConnectedDevice()->handleResponse(ack); //TODO to remove

                //Check the header bit
                if(ack[HEADER_INDEX] == 1) {
                    LOG(2, "[HANDLER] header bit ok");
                    //check id message
                    //ConnectedDevice may not be NULL
                    if (ack[ID_INDEX] == connectedDevice->getID()) {
                        LOG(2, "[HANDLER] DeviceID bit ok");
                        //Check opcode validity
                        uint8_t  opcode = ack[OPCODE_INDEX];

                        if (isAValidAnswerOpcode(opcode)) {
                            //if valid opcode
                            LOG(2, "[HANDLER] Opcode ok");

                            if (isAnAckOpcode(opcode)) {
                                //Create an AckMessage instance
                                LOG(2, "[HANDLER] Is an Ack Opcode ok");
                                uint16_t sizeLeftPack =
                                        convertTwo8to16(ack[DATA_INDEX+1],
                                                        ack[DATA_INDEX+2]);
                                AckMessage ackMess(connectedDevice->getID(), opcode);
                                ackMess.encodeAck(sizeLeftPack, ack[DATA_INDEX]);

                                //Handle the ack
                                isAcknowledged = connectedDevice->handleAck(mess,
                                                                            ackMess, i);
                            } else {
                                //Response message
                                //TODO handle the response
                                isAcknowledged = connectedDevice->handleResponse(ack);
                            }
                        }
                    }
                }
                //Increment the number of tries if not aknowledged
                if (!isAcknowledged)
                    nbTry++;
            }
        }

        /* //Empty the queue */
        /* while (!buffReceived.empty()) */
        /*     buffReceived.pop(); */

        /* LOG(2, "Queue emptied"); */


        //Free allocated memory for the bufferArray
        delete []bufferArray;

        //If number of tries exceeded
        if (nbTry == MAX_TRY)
            std::cerr << "Number of tries to send the message exceeded\n";
            /*throw ErrorException("Error while sending a message : "
                                         "Number of tries to send "
                                         "the message exceeded");*/

    }
    LOG(1, "Message sended");
    return true;
}


/**
 * @brief TODO
 */
bool Controller::displayDevice()
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

/**
 * @brief Add a Listener to the Controller's list of Listener
 * @param Listener to add
 */ 
bool Controller::addListener(Listener &l)
{
    LOG(1, "addListener(Listener &l) \n");
    return false;
}

/**
 * @brief Remove a Listener to the Controller's list of Listener
 * @param Listener to remove
 */ 
bool Controller::removeListener(Listener &l)
{
    LOG(1, "removeListener(Listener &l) \n");
    return false;
}

/**
 * @brief List all devices which are connected via USB
 */ 
bool Controller::listAllDevices()
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

/**
 * @brief Connects the controller to a device chosen from the list
 * @param Device to connect
 */ 
bool Controller::connectDevice()
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

/**
 * @brief Gets the port of the connected device from its ID
 * @param ID of the device to get the port
 */ 
std::string Controller::getPortFromID(int id)
{
    std::list<Device*>::iterator iter ;
    for(iter = devices.begin() ; (iter != devices.end()) ;iter++){
        if (id == (*iter)->getID())
            return (*iter)->getPort();
    }
    return "No Device with this ID";
}
    
/**
 * @brief Connects the controller to a device with its ID
 * @param ID of the device to connect
 */ 
bool Controller::connectDevice(int id)
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

/**
 * @brief Connects the controller to the Device specified in argument  
 * @param Device to connect
 */ 
bool Controller::connectDevice(Device *d)
{
    LOG(1, "connectDevice(Device*) \n");

    if ((*d).connect()){
        this->connectedDevice = d;
        ack_thread = std::thread(&Controller::waitForACK, this);
        //this->t = std::thread(&Controller::readingTask, this);
        return true;
    }
    return false; 
}

bool Controller::disconnectDevice()
{
    LOG(1, "disconnectDevice() \n");
    ack_thread.detach();
    while (!connectedDevice->disconnect()); //TODO Timeout
    this->connectedDevice = NULL;
    return true;
}

/**
 * @brief Accessor to the current connected device
 * @return The current connected device
 */ 
Device* Controller::getConnectedDevice()
{
    LOG(1, "getConnectedDevice() \n");
    return this->connectedDevice;
}

/**
 * @brief Switches on a led on the current connected device
 * @param x,y,z, position of the led
 */ 
bool Controller::on(int x, int y, int z)
{
    return connectedDevice->on(x,y,z);
}

/**
 * @brief Accessor to the list of USB connected sevices
 * @return The list of USB Connected Devices
 */ 
std::list<Device*> Controller::getListDevices()
{
    LOG(1, "getListDevices() \n");

    return this->devices;
}

/*****************************************************
 *****************************************************
 **   Auxiliar functions to get connected devices   **
 *****************************************************
 ****************************************************/

/**
 * @brief Gets the next word in a char * line from the j's char
 * @param path : the line to parse
 * @param j : begining of the future parsing
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

/**
 * @brief Gets the result of a "lsusb | grep STM" system call in a Dictionnary(Bus:Device) structure
 * @param nbSTM : number of STM devices connected to return
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

    /* Print dictionnary */
    for (int i = 0; i < lines; ++i) 
	    std::cout << "Dic[" << i << "]: BUS: " << dic[i].bus
	              << " DEVICE: " << dic[i].Device << std::endl;
    
    
    /* Return created dic */
    return dic;
}

/**
 * @brief Return true if the ttyPort corresponds to a STM device
 * @param echo : the ttyPort
 * @param dic : the Dictionnary to look in
 * @param sizOfDic : size of the Dictionnary
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


/**
 * @brief Display the list of all USB connected devices and push them in the device list 
 */ 
void Controller::listAndGetUSBConnectedDevices()
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

    /* Free all alocated memory */
    delete [] dic;
}
