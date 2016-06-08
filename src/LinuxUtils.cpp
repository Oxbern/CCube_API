#include "LinuxUtils.h"
#include "Debug.h"

/*!
 * \brief Lists all devices which are connected via USB
 * \return TODO
 */
bool listAllDevices(Controller &c)
{
    LOG(1, "listAllDevices(Controller &c)\n");

    std::cout << "--- List of USB Connected Devices : ---" << std::endl;
    std::list<Device*>::iterator iter ;
    int i = 1;
    for(iter = c.getListDevices().begin() ; (iter != c.getListDevices().end()) ;iter++){
        std::cout << "Device  "  << i << ": Id = " << (*iter)->getID()
                  << ", Port :" << (*iter)->getPort() <<  "\n";
        i++;
    }
    if (!strcmp((*( c.getListDevices().begin()))->getPort().c_str(),"/dev/stdout") ) {
        std::cout << "No device connected, connection to stdout\n";
        return false;
    }
    return true;
}

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
void listAndGetUSBConnectedDevices(Controller &c)
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
                 c.devices.push_back(new Device(name, DeviceID++));
            }
        }
        pclose(fp);
    }

    /* Free all allocated memory */
    delete [] dic;
}

/*!
 * \brief Gets the port of the connected device from its ID
 * \param c controller
 * \param id of the device to get the port from
 * \return string
 */
std::string getPortFromID(Controller &c, int id)
{
    std::list<Device*>::iterator iter ;
    for(iter = c.getListDevices().begin() ; (iter != c.getListDevices().end()) ;iter++){
        if (id == (*iter)->getID())
            return (*iter)->getPort();
    }
    return "No Device with this ID";
}
