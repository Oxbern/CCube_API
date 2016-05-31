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
    nanosleep(TIME, NULL);
    d->display();
    d->on(3,8,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(4,8,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(5,8,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(6,8,6);
    nanosleep(TIME, NULL);
    d->display();
    d->on(6,8,5);
    nanosleep(TIME, NULL);
    d->display();
    d->on(6,8,4);
    nanosleep(TIME, NULL);
    d->display();
    d->on(6,8,3);
    nanosleep(TIME, NULL);
    d->display();
    d->on(6,8,2);
    nanosleep(TIME, NULL);
    d->display();
    d->on(5,8,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(4,8,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(3,8,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,8,2);
    nanosleep(TIME, NULL);
    d->display();
}

void displayU(Device *d )
{
    d->on(0,6,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,6,6);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,6,5);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,6,4);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,6,3);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,6,2);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,5,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,4,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,3,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,2,2);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,2,3);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,2,4);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,2,5);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,2,6);
    nanosleep(TIME, NULL);
    d->display();
    d->on(0,2,7);
    nanosleep(TIME, NULL);
    d->display();
}

void displayB(Device *d )
{
    d->on(2,0,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,0,6);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,0,5);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,0,4);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,0,3);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,0,2);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,0,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,0,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(3,0,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(4,0,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(5,0,6);
    nanosleep(TIME, NULL);
    d->display();
    d->on(5,0,5);
    nanosleep(TIME, NULL);
    d->display();
    d->on(4,0,4);
    nanosleep(TIME, NULL);
    d->display();
    d->on(3,0,4);
    nanosleep(TIME, NULL);
    d->display();
    d->on(2,0,4);
    nanosleep(TIME, NULL);
    d->display();//BOUCLE1
    d->on(5,0,4);
    nanosleep(TIME, NULL);
    d->display();
    d->on(6,0,3);
    nanosleep(TIME, NULL);
    d->display();
    d->on(6,0,2);
    nanosleep(TIME, NULL);
    d->display();
    d->on(6,0,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(5,0,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(4,0,1);
    nanosleep(TIME, NULL);
    d->display();
    d->on(3,0,1);
    nanosleep(TIME, NULL);
    d->display();
}


void displayE(Device *d )
{
    d->on(8,1,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(8,1,6);
    nanosleep(TIME, NULL);
    d->display();
    d->on(8,1,5);
    nanosleep(TIME, NULL);
    d->display();
    d->on(8,1,4);
    nanosleep(TIME, NULL);
    d->display();
    d->on(8,1,3);
    nanosleep(TIME, NULL);
    d->display();
    d->on(8,1,2);
    nanosleep(TIME, NULL); // barre 1
    d->display();
    d->on(8,2,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(8,3,7);
    nanosleep(TIME, NULL);
    d->display();
    d->on(8,4,7);
    nanosleep(TIME, NULL); // barre 2
    d->display();
    d->on(8,3,4);
    nanosleep(TIME, NULL); 
    d->display();    
    d->on(8,4,4);
    nanosleep(TIME, NULL); 
    d->display();
    d->on(8,4,7);
    nanosleep(TIME, NULL); // barre 3
    d->display();
    d->on(8,3,1);
    nanosleep(TIME, NULL); 
    d->display();    
    d->on(8,4,1);
    nanosleep(TIME, NULL); 
    d->display();
    d->on(8,5,1);
    nanosleep(TIME, NULL); 
    d->display();    
    d->on(8,6,1);
    nanosleep(TIME, NULL); 
    d->display();
    d->on(8,7,1);
    nanosleep(TIME, NULL); 
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
