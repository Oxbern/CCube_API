#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>


#include "Device.h"
#include "Utils.h"

//Windows def
#ifndef O_NOCTTY
#define O_NOCTTY 0
#endif
#ifndef O_NDELAY
#define O_NDELAY 0
#endif
int main(int argc, char *argv[]) {

    OutgoingMessage m(1, SIZE_BUFFER, 20, 0x1);

    /* std::fstream file;
       file.open("/dev/ttyACM0", std::ios::in | std::ios::out);

       if (!file.is_open()) {
       perror("Erreur");
       return EXIT_FAILURE;
       }*/

    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd != -1) {

        uint8_t * buff = new uint8_t[64];

        Buffer buffer(64);
        buffer.setHeader(1);
        buffer.setOpCode(1);
        buffer.setSizeLeft(50);
        buffer.setCrc(0);



        buffer.toArray(buff);

        for (int i = 0; i < 64; i++)
            std::cout << (int)buff[i];

        for (int i = 4; i < 57; i++)
            buffer.setData(i-4, 1);

        std::cout << buffer.toString() << "\n";

        write(fd, buff, 64);

    }else{
        perror("Unable to open file");
        return EXIT_FAILURE;
    }


    /*

      for (int i = 0; i < 64; i++)
      std::cout << (int)buff[i];
      std::cout << "\n";

      std::cout << buffer.toStringDebug(0);



      file.write((char *)buff, 64);

      file.close();
    */
    close(fd);

    return EXIT_SUCCESS;
}
