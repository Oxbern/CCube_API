#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "Controller.h"

#define TIME ((const struct timespec[]){{0, 100000000L}})

void displayC(Device *d )
{
    d->on(2,8,6);
     
     
    d->on(3,8,7);
     
     
    d->on(4,8,7);
     
     
    d->on(5,8,7);
     
     
    d->on(6,8,6);
     
     
    d->on(6,8,5);
     
     
    d->on(6,8,4);
     
     
    d->on(6,8,3);
     
     
    d->on(6,8,2);
     
     
    d->on(5,8,1);
     
     
    d->on(4,8,1);
     
     
    d->on(3,8,1);
     
     
    d->on(2,8,2);
     
    d->display();

}

void displayU(Device *d )
{
    d->on(0,6,7);
     
     
    d->on(0,6,6);
     
     
    d->on(0,6,5);
     
     
    d->on(0,6,4);
     
     
    d->on(0,6,3);
     
     
    d->on(0,6,2);
     
     
    d->on(0,5,1);
     
     
    d->on(0,4,1);
     
     
    d->on(0,3,1);
     
     
    d->on(0,2,2);
     
     
    d->on(0,2,3);
     
     
    d->on(0,2,4);
     
     
    d->on(0,2,5);
     
     
    d->on(0,2,6);
     
     
    d->on(0,2,7);
     
     
}

void displayB(Device *d )
{
    d->on(2,0,7);
     
     
    d->on(2,0,6);
     
     
    d->on(2,0,5);
     
     
    d->on(2,0,4);
     
     
    d->on(2,0,3);
     
     
    d->on(2,0,2);
     
     
    d->on(2,0,1);
     
     
    d->on(2,0,7);
     
     
    d->on(3,0,7);
     
     
    d->on(4,0,7);
     
     
    d->on(5,0,6);
     
     
    d->on(5,0,5);
     
     
    d->on(4,0,4);
     
     
    d->on(3,0,4);
     
     
    d->on(2,0,4);
     
     //BOUCLE1
    d->on(5,0,4);
     
     
    d->on(6,0,3);
     
     
    d->on(6,0,2);
     
     
    d->on(6,0,1);
     
     
    d->on(5,0,1);
     
     
    d->on(4,0,1);
     
     
    d->on(3,0,1);
     
    d->display();

}


void displayE(Device *d )
{
    d->on(8,1,7);
     
     
    d->on(8,1,6);
     
     
    d->on(8,1,5);
     
     
    d->on(8,1,4);
     
     
    d->on(8,1,3);
     
     
    d->on(8,1,2);
      // barre 1
     
    d->on(8,2,7);
     
     
    d->on(8,3,7);
     
     
    d->on(8,4,7);
      // barre 2
     
    d->on(8,3,4);
      
         
    d->on(8,4,4);
      
     
    d->on(8,4,7);
      // barre 3
     
    d->on(8,1,1);
      
         
    d->on(8,2,1);
      
     
    d->on(8,3,1);
      
         
    d->on(8,4,1);
      
     
    d->on(8,5,1);
    d->display();
}


int main(int argc, char* argv[])
{    
    
    Device *dc = new Device("/dev/ttyACM0",1);
    dc->connect();
    dc->on(4,4,4);
    dc->on(3,4,4);
    dc->on(4,3,4);
    dc->on(5,4,4);
    dc->on(4,5,4);
    dc->on(3,3,4);
    dc->on(5,5,4);

    displayC(dc);
    nanosleep(TIME, NULL); 

    displayU(dc);
    displayB(dc);
    displayE(dc);

    
    dc->display();
    dc->disconnect();
    return 0;
}

/*

  echo /dev/bus/usb/`udevadm info --name=/dev/ttyUSB0 --attribute-walk | sed -n 's/\s*ATTRS{\(\(devnum\)\|\(busnum\)\)}==\"\([^\"]\+\)\"/\4/p' | head -n 2 | awk '{$1 = sprintf("%03d", $1); print}'` | tr " " "/"

*/
