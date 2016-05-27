#include "Controller.h"

/**
 * @brief Constructor of Controller object, list all USB connected devices and 
 *        add them to the Device list 
 */ 
Controller::Controller()
{
    listAndGetUSBConnectedDevices();
}

/**
 * @brief Destructor of Controller object
 */ 
Controller::~Controller()
{

}

/**
 * @brief Add a Listener to the Controller's list of Listener
 * @param Listener to add
 */ 
bool Controller::addListener(Listener &l)
{
    return false;
}

/**
 * @brief Remove a Listener to the Controller's list of Listener
 * @param Listener to remove
 */ 
bool Controller::removeListener(Listener &l)
{
    return false;
}

/**
 * @brief List all devices which are connected via USB
 */ 
void Controller::listAllDevices()
{
    std::cout << "--- List of USB Connected Devices : ---" << std::endl;
    std::list<Device*>::iterator iter ;
    int i = 1;
    for(iter = devices.begin() ; (iter != devices.end()) ;iter++){
        std::cout << "Device  "  << i << ": Id = " << (*iter)->getID() << ", Port :" << (*iter)->getPort() <<  "\n";
        i++;
    }
}

/**
 * @brief Connected the controller to the device 
 * @param Device to connect
 */ 
bool Controller::connectDevice(Device *d)
{
    if ((*d).connect()){
        this->connectedDevice = d;
        return true;
    }
    return false; 
}

/**
 * @brief Accessor to the current connected device
 */ 
Device* Controller::getConnectedDevice()
{
    return this->connectedDevice;
}

/**
 * @brief Accessor to the list of USB connected sevices
 */ 
std::list<Device*> Controller::getListDevices(){
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
char ** getTtyList(int *size){
    FILE *fp;
    char path[20];
    int i = 0;
    /* Open the command for reading. */
    fp = popen("ls /dev/tty*  ", "r"); 
    if (fp == NULL) {
        printf("Failed to run command\n" );
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
        printf("Failed to run command\n" );
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
char * getNextWord(char *path, int *j){
    char word[10];
    int w = 0;
    
    while(path[*j] != ' '){
        word[w]=path[*j];
        w++;
        (*j)++;
    }
    word[*j]='\0';
    char * wordreturn = (char *)malloc(10*sizeof(char));
    strcpy(wordreturn,word);
    return wordreturn;
}

/**
 * @brief Gets the result of a "lsusb | grep STM" system call in a Dictionnary(Bus:Device) structure
 * @param nbSTM : number of STM devices connected to return
 */ 
Dictionnary *getDictSTM( int *nbSTM){
    FILE *fp;
    char path[100];
    int i = 0;
    //Open the command for reading.
    fp = popen("lsusb | grep STM ", "r"); 
    if (fp == NULL) {
        printf("Failed to run command\n" );
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
        printf("Failed to run command\n" );
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
                        char * bus =  getNextWord(path,&j);
                        dic[k].bus = atoi(bus);
                        delete [] bus;
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
                                    char * device =  getNextWord(path,&j);
                                    dic[k].Device = atoi(device);
                                    delete [] device;
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
bool isInDico(std::string echo, Dictionnary *dic, int sizeOfDic){
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
    char wordD[10];
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
void Controller::listAndGetUSBConnectedDevices(){
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
            printf("Failed to run command\n" );
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
               
    }
    for (int i = 0; i < size; i++)
            delete [] (ttyList[i]);
    delete [] (ttyList);
    delete [] dic;
}
