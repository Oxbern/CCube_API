#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>

struct Dictionnaire{
    int bus;
    int Device;
} typedef Dictionnaire;




void display(const char * dev) {
    int fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
    char c = 'a';
    
    write(fd, &c, 64);
    
    close(fd);
}

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

    char ** ttyList = (char **) malloc(i*sizeof(char *));
    /* Open the command for reading. */
    fp = popen("ls /dev/tty*  ", "r"); 
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    
    for (int j = 0; j < *size; j++) {
        ttyList[j] = (char * ) malloc(20*sizeof(char));
        char * chaine = fgets(path, 19, fp);
        strcpy(ttyList[j],chaine);
    }        
    pclose(fp);
    
    return ttyList;
}

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


Dictionnaire *getDictSTM( int *nbSTM){
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

    Dictionnaire *dic = (Dictionnaire *) malloc(*nbSTM * sizeof(struct Dictionnaire));
     //Open the command for reading.
    fp = popen("lsusb | grep STM ", "r"); 
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    int j = 0, k = 0;
    //Read the output a line at a time - output it.
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("STM : %s",path);
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

bool isInDico(std::string echo, Dictionnaire *dic, int sizeOfDic){
    const char * busSDev = echo.c_str();
    int bus = 0;
    char wordB[10];
    int w = 0;
    while(busSDev[w] != '/'){
        wordB[w]=busSDev[w];
        w++;
    }
    wordB[w]='\0';
    char * wordBreturn = (char *)malloc(10*sizeof(char));
    strcpy(wordBreturn,wordB);
    bus = atoi(wordBreturn);
    int Device = 0;
    char wordD[10];
    w+=1;
    int k = 0;
    while(busSDev[w] != '/'){
        wordD[k]=busSDev[w];
        w++;
        k++;
    }
    wordD[w]='\0';
    char * wordDreturn = (char *)malloc(10*sizeof(char));
    strcpy(wordDreturn,wordD);
    Device = atoi(wordDreturn);
    for (int i = 0; i<sizeOfDic; i++){
        if (bus == dic[i].bus && Device == dic[i].Device )
            return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    
    int size = 0;
    char ** ttyList = getTtyList(&size);

    
    
    int nbSTM = 0;
    Dictionnaire *dic = getDictSTM(&nbSTM);
    
    printf("--- Liste des cubes disponibles : ---\n");
    
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
                if (isInDico(t,dic,nbSTM))
                    printf("%s\n",name.c_str());
            }
        }
        
    }
    printf("Entrez un device : \n");
    std::string dev ;
    std::cin >> dev;
    display(dev.c_str());
    
    return 0;
}

/*

echo /dev/bus/usb/`udevadm info --name=/dev/ttyUSB0 --attribute-walk | sed -n 's/\s*ATTRS{\(\(devnum\)\|\(busnum\)\)}==\"\([^\"]\+\)\"/\4/p' | head -n 2 | awk '{$1 = sprintf("%03d", $1); print}'` | tr " " "/"

 */
