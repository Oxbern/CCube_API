#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>


#include "cube.h"
#include "pilote.h"
#include "okShape.h"


void printcmd(){
    printf(" Available key bindings:\n");
    printf("- Move on x : z/s\n");
    printf("- Move on y : q/d\n");
    printf("- Move on z : l/m\n");
    printf("- Scale +/-\n");
    printf("- Change forme : c\n");
    printf("- Full/Empty : f\n");
}


int main(int argc, char *argv[]) {
    //pilote(); // Go through the cube with cmds above
    
    cube *cube = new_cube();
    cube = test_ok();
    display("/dev/ttyACM0", cube);
    sleep(2);
    display("/dev/ttyACM0", new_cube());
 }


