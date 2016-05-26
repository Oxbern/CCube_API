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
#include "Controller.h"


int main(int argc, char* argv[]) {
    
    Controller c;
    
    return 0;
}

/*

echo /dev/bus/usb/`udevadm info --name=/dev/ttyUSB0 --attribute-walk | sed -n 's/\s*ATTRS{\(\(devnum\)\|\(busnum\)\)}==\"\([^\"]\+\)\"/\4/p' | head -n 2 | awk '{$1 = sprintf("%03d", $1); print}'` | tr " " "/"

 */
