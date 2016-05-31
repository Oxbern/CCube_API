#include <mutex>
#include <unistd.h>
#include <fcntl.h>

#include "Controller.h"

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
    
    ack_index = 0;

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			ack[i][j] = 0;

    
    ack_thread = std::thread(&Controller::waitForACK, this);
    
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
		
		if (!this->connectedDevice)
			break;
		
		while (!lock_ack.try_lock());
		this->getConnectedDevice()->readFromFileDescriptor(ack[ack_index++]);
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
    if (!this->getConnectedDevice()->getFile()) {
	    while (!this->getConnectedDevice()->connect()) {
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

        if ((this->getConnectedDevice()->getPort().compare("/dev/stdin") == 0)
            || (this->getConnectedDevice()->getPort().compare("/dev/stdout") == 0)) {
            //VirtualCube
            LOG(2, "Buffer send (size = " + std::to_string(sizeBuffer)
                + " Bytes) : " + uint8ArrayToString(buffString, sizeBuffer));

            LOG(1, "Virtual sending");

        } else {
            
	        while (!this->getConnectedDevice()->writeToFileDescriptor(buffString, sizeBuffer)) {
	            continue;
            }
        }

        while (!lock_ack.try_lock());
        this->getConnectedDevice()->handleResponse(ack[--ack_index]);
        lock_ack.unlock();

        delete []buffString;
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

	uint8_t *buffer = device->getcurrentConfig()->toArray();

    dm.encode(buffer);
    delete[](buffer);

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
 * @brief Connects the controller to the device 
 * @param Device to connect
 */ 
bool Controller::connectDevice(Device *d)
{
    LOG(1, "connectDevice() \n");

    if ((*d).connect()){
        this->connectedDevice = d;
        //this->t = std::thread(&Controller::readingTask, this);
        return true;
    }
    return false; 
}

bool Controller::disconnectDevice()
{
    LOG(1, "disconnectDevice() \n");
    ack_thread.detach();
    return this->connectedDevice->disconnect();
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
