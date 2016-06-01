#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <ErrorException.h>

#include "Controller.h"

#define MAX_TRY 3

/**
 * @brief Constructor of Controller object, list all USB connected devices and
 *        add them to the Device list
 */
Controller::Controller()
{
	listAndGetUSBConnectedDevices();

    if (devices.size() == 0){
        // Connect to stdout to write messages
        Device *dev = new Device("/dev/stdout", 1);
        devices.push_back(dev);
        connectDevice(dev);
    }

    LOG(1, "Controller()");
}

/**
 * @brief Destructor of Controller object
 */ 
Controller::~Controller()
{
    LOG(1,"~Controller()");
    while(!devices.empty()) delete devices.front(), devices.pop_front();
}


/**
 * @brief Read a ACK message from USB
 */
void *Controller::waitForACK()
{
	while (1) {		
		if (this->connectedDevice == NULL)
			break;
		
		while (!lock_ack.try_lock());

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
    //Boolean to kwnow if the lock on the queue of ack is taken
    bool isLockTaken = false;

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
        while (!isAcknowledged && nbTry < MAX_TRY) { //TODO Timeout time

            //Check for new message
            if (!buffReceived.empty()) {
                LOG(2, "Handle an ack");

                //Try to take the lock
                while (!lock_ack.try_lock()); //TODO timeout
                isLockTaken = true;

                //The oldest ack received
                uint8_t *ack = buffReceived.front();

                this->getConnectedDevice()->handleResponse(ack); //TODO to remove

                //Check the header bit
                if(ack[HEADER_INDEX] == 1) {
                    //check id message
                    //ConnectedDevice may not be NULL
                    if (ack[ID_INDEX] == connectedDevice->getID()) {
                        //Check opcode validity
                        uint8_t  opcode = ack[OPCODE_INDEX];

                        if (isAValidAnswerOpcode(opcode)) {
                            //if valid opcode

                            if (isAnAckOpcode(opcode)) {
                                //Create an AckMessage instance
                                uint16_t sizeLeftPack =
                                        convertTwo8to16(ack[DATA_INDEX+1],
                                                        ack[DATA_INDEX+2]);
                                AckMessage ackMess(connectedDevice->getID(), opcode);
                                ackMess.encodeAck(sizeLeftPack, ack[DATA_INDEX]);

                                //Release the lock
                                lock_ack.unlock();
                                isLockTaken = false;

                                //Handle the ack
                                isAcknowledged = connectedDevice->handleAck(mess,
                                                                            ackMess);
                            } else {
                                //Response message
                                //TODO handle the response
                                isAcknowledged = connectedDevice->handleResponse(ack);
                            }
                        }
                    }
                }
                //Release the lock
                if (isLockTaken)
                    lock_ack.unlock();
                //Remove the oldest ack in the queue
                buffReceived.pop();
                //Increment the number of tries if not aknowledged
                isAcknowledged ? : nbTry++;
            }
        }

        //Free allocated memory for the bufferArray
        delete []bufferArray;

        //If number of tries exceeded
        if (nbTry == MAX_TRY)
            throw ErrorException("Error while sending a message : "
                                         "Number of tries to send "
                                         "the message exceeded");

    }
    LOG(1, "Message sended");
    return true;
}


/**
 * @brief TODO
 */
bool Controller::displayDevice()
{
	Device *device = this->getConnectedDevice();
	
	DataMessage dm(device->getID(),
	               device->getcurrentConfig()->getSizeInBytes(),
	               OPCODE(BUFF_SENDING));

	uint8_t *ledsBuffer = new uint8_t[device->getcurrentConfig()->getSizeInBytes()];
    device->getcurrentConfig()->toArray(ledsBuffer);

    dm.encode(ledsBuffer);
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
    for(iter = devices.begin() ; (iter != devices.end()) ;iter++){
        if (id == (*iter)->getID())
            chosen = *iter;
    }
    
    if (connectDevice(chosen)){
        return true;
    }
    return false;
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
 * @brief Get the list of tty ports open on the computer
 * @param size : number of tty ports to return 
 */ 
char ** getTtyList(int *size)
{
    FILE *fp;
    char path[20];
    int i = 0;
    /* Open the command for reading. */
    fp = popen("ls /dev/tty*  ", "r"); 
    if (fp == NULL) {
        std::cerr << "Failed to run command\n";
        exit(1);
    }
    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        i++;
    }
    *size = i;
    /* close */
    pclose(fp);

    char ** ttyList= new char*[i];
    /* Open the command for reading. */
    fp = popen("ls /dev/tty*  ", "r"); 
    if (fp == NULL) {
        std::cerr << "Failed to run command\n";
        exit(1);
    }
    
    for (int j = 0; j < *size; j++) {
        ttyList[j] = new char[20];
        char * chaine = fgets(path, 19, fp);
        strcpy(ttyList[j],chaine);
    }        
    pclose(fp);
        
    return ttyList;
}

/**
 * @brief Gets the next word in a char * line from the j's char
 * @param path : the line to parse
 * @param j : begining of the future parsing
 */ 
void getNextWord(char *path, int *j, char * wordreturn)
{
    char word[10] = "initializ";
    int w = 0;
    
    while(path[*j] != ' '){
        word[w]=path[*j];
        w++;
        (*j)++;
    }
    word[*j]='\0';
    //char * wordreturn = (char *)malloc(10*sizeof(char));
    strcpy(wordreturn,word);
    //return wordreturn;
}

/**
 * @brief Gets the result of a "lsusb | grep STM" system call in a Dictionnary(Bus:Device) structure
 * @param nbSTM : number of STM devices connected to return
 */ 
Dictionnary *getDictSTM( int *nbSTM)
{
    FILE *fp;
    char path[100];
    int i = 0;
    //Open the command for reading.
    fp = popen("lsusb | grep STM ", "r"); 
    if (fp == NULL) {
        std::cerr << "Failed to run command\n";
        exit(1);
    }
    
    //Read the output a line at a time - output it.
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        i++;
    }
    *nbSTM = i;
    /* close */
    pclose(fp);

    Dictionnary *dic = new Dictionnary[*nbSTM];
    //Open the command for reading.
    fp = popen("lsusb | grep STM ", "r"); 
    if (fp == NULL) {
        std::cerr << "Failed to run command\n";
        exit(1);
    }
    int j = 0, k = 0;
    //Read the output a line at a time - output it.
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        while(path[j] != '\0'){
            if (path[j] == 'B'){
                j++;
                if (path[j] == 'u'){
                    j++;
                    if (path[j] == 's'){
                        j++;
                        j++;
                        char bus[10];
                        getNextWord(path,&j, (char *) &bus);
                        dic[k].bus = atoi(bus);
                        //delete [] bus;
                    }
                }
            }
            if (path[j] == 'D'){
                j++;
                if (path[j] == 'e'){
                    j++;
                    if (path[j] == 'v'){
                        j++;
                        if (path[j] == 'i'){
                            j++;
                            if (path[j] == 'c'){
                                j++;
                                if (path[j] == 'e'){
                                    j++;
                                    j++;
                                    char device[10];
                                    getNextWord(path,&j,(char *) &device);
                                    dic[k].Device = atoi(device);
                                    //delete [] device;
                                }
                            }
                        }
                    }
                }
            }
            j++;
        }
        j = 0;
        k++;
    }
    /* close */
    pclose(fp);
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
    char busSDev[echo.length()+1];
    strcpy(busSDev,echo.c_str());
    int bus = 0;
    char wordB[10];
    int w = 0;
    while(busSDev[w] != '/'){
        wordB[w]=busSDev[w];
        w++;
    }
    wordB[w]='\0';
    char wordBreturn[w+1];
    strcpy(wordBreturn,wordB);
    bus = atoi(wordBreturn);
    int Device = 0;
    char wordD[10] = "initializ";
    w++;
    int k = 0;
    while(busSDev[w] != '\0'){
        wordD[k]=busSDev[w];
        w++;
        k++;
    }
    wordD[w]='\0';
    char wordDreturn[k+1];
                            
    strcpy(wordDreturn,wordD);
    Device = atoi(wordDreturn);
    for (int i = 0; i<sizeOfDic; i++){
        if (bus == dic[i].bus && Device == dic[i].Device ){
            return true;
        }
    }
    return false;
}


/**
 * @brief Display the list of all USB connected devices and push them in the device list 
 */ 
void Controller::listAndGetUSBConnectedDevices()
{
    LOG(1, "listAndGetUSBConnectedDevices() \n");

    int size = 0;
    char ** ttyList = getTtyList(&size);

    int nbSTM = 0;
    Dictionnary *dic =  getDictSTM(&nbSTM);
    
    int DeviceID = 1;

    for (int i = 0; i < size; i++){
        std::string name = ttyList[i];

        name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
        std::string cmd = "echo /dev/bus/usb/`udevadm info --name="  + name +   " --attribute-walk | sed -n 's/\\s*ATTRS{\\(\\(devnum\\)\\|\\(busnum\\)\\)}==\\\"\\([^\\\"]\\+\\)\\\"/\\4/p' | head -n 2 | awk '{$1 = sprintf(\"%03d\", $1); print}'` | tr \" \" \"\\/\"";
        //Open the command for reading.
        FILE *fp;
        fp = popen(cmd.c_str(), "r"); 
        if (fp == NULL) {
            std::cerr << "Failed to run command\n";
            exit(1);
        }
        char path[50];
        //Read the output a line at a time - output it.
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
            if (strcmp(path,"/dev/bus/usb/\n")){
                std::string t = path;
                std::string s = "/dev/bus/usb/";
                
                std::string::size_type i = t.find(s);

                if (i != std::string::npos)
                    t.erase(i, s.length());
                
                if (isInDico(t,dic,nbSTM)){
                    //std::cout << "Found Device : " << name.c_str() << std::endl;
                    // We have a device here with his port name (string)
                    Device *d = new Device(name,DeviceID);
                    devices.push_back(d);
                    DeviceID++;
                }
            }
        }
        pclose(fp);
    }
    for (int i = 0; i < size; i++)
        delete [] (ttyList[i]);
    delete [] (ttyList);
    delete [] dic;
}
