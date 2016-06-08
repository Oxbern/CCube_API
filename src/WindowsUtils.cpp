#include "WindowsUtils.h"
#include "Debug.h"

/*!
 * \brief Lists all devices which are connected via USB
 * \return TODO
 */
bool listAllDevices(Controller &c)
{
    // LOG(1, "listAllDevices(Controller &c)\n");

    std::cout << "---  List of USB Connected Devices : ---" << std::endl;
    std::list<Device*>::iterator iter ;
    int i = 1;
    for(iter = c.getListDevices().begin() ; (iter != c.getListDevices().end()) ;iter++){
        std::cout << "Device  "  << i << ": Id = " << (*iter)->getID()
                  << ", Port :" << (*iter)->getPort() <<  "\n";
        i++;
    }
    if (c.getListDevices().size() == 0) {
        std::cout << "No device connected\n";
        return false;
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
    // char word[10] = {'0'};
    // int w = 0, k = *j;

    // /* Read char until space */
    // while (path[k] != ' ')
    //     word[w++]=path[k++];
    // word[k]='\0';

    // /* Set return values */
    // *j = k;
    // strcpy(wordreturn, word);
}



/*!
 * \brief Displays the list of all USB connected devices 
 * and pushes them in the device list
 */
void listAndGetUSBConnectedDevices(Controller &c)
{
    // LOG(1, "listAndGetUSBConnectedDevices() \n");

    // /* Open the command for reading. */
    // FILE *fp = popen("ls /dev/tty*  ", "r");
    // if (!fp) {
    //     std::cerr << "Failed to run command\n";
    //     exit(1);
    // }

    // char path[20];
    // int lines = 0;

    // /* Calculate number of lines in the file */
    // while (fgets(path, sizeof(path)-1, fp))
    //     lines++;

    // /* Close the file and re-open it */
    // pclose(fp);
    // fp = popen("ls /dev/tty*  ", "r");

    // char ttyList[lines][20];

    // for (int j = 0; j < lines; j++)
    //     /* Copy TTY path in TTY list */
    //     strcpy(&ttyList[j][0], fgets(path, sizeof(path)-1, fp));

    // /* Close the file */
    // pclose(fp);

    // int nbSTM = 0;
    // Dictionnary *dic =  getDictSTM(&nbSTM);

    // int DeviceID = 1;

    // for (int i = 0; i < lines; i++){
    //     std::string name = ttyList[i];

    //     name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());

    //     std::string cmd = "echo /dev/bus/usb/`udevadm info --name="
    //         + name +   " --attribute-walk | sed -n 's/\\s*ATTRS{\\(\\(devnum\\) "
    //         + "\\|\\(busnum\\)\\)}==\\\"\\([^\\\"]\\+\\)\\\"/\\4/p' | head -n 2 "
    //         + "| awk '{$1 = sprintf(\"%03d\", $1); print}'` | tr \" \" \"\\/\"";

    //     //Open the command for reading.
    //     fp = popen(cmd.c_str(), "r");
    //     if (fp == NULL) {
    //         std::cerr << "Failed to run command\n";
    //         exit(1);
    //     }

    //     char path[50];

    //     //Read the output a line at a time - output it.
    //     while (fgets(path, sizeof(path)-1, fp) != NULL) {

    //         if (strcmp(path, "/dev/bus/usb/\n")){
    //             std::string t = path;
    //             std::string s = "/dev/bus/usb/";

    //             std::string::size_type i = t.find(s);

    //             if (i != std::string::npos)
    //                 t.erase(i, s.length());

    //             std::cout << name << std::endl;
    //             /* if (isInDico(t, dic, nbSTM)) */
    //             // We have a device here with his port name (string)
    //             Device *devFound = new Device(name, DeviceID);
    //             c.devices.push_back(devFound);
    //             DeviceID++;
    //         }
    //     }
    //     pclose(fp);
    // }

    // /* Free all allocated memory */
    // delete [] dic;
}
