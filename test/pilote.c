#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "cube.h"
#include "test_display.h"
#include "pilote.h"

void printcmd(){
    printf(" Available key bindings:\n");
    printf("- Move on x : z/s\n");
    printf("- Move on y : q/d\n");
    printf("- Move on z : l/m\n");
    printf("- Scale +/-\n");
    printf("- Change forme : c\n");
    printf("- Full/Empty : f\n");
}

int pilote(){
    cube *cube = new_cube();
    display("/dev/ttyACM0", new_cube());
    
    //cube = test_ok(cube);
    Point origine;
    origine.x = 3;
    origine.y = 3;
    origine.z = 3;
    uint8_t rayon = 1;
    uint32_t compteur = 0;
    char s;
    initscr();
    uint8_t forme = 1;
    uint8_t nb_formes = 2;
    bool full = false;
    
    
    while(true){
	printcmd();
	keypad(stdscr, TRUE);
	noecho();
      switch(getch()) { 
      case 'm':
	  origine.z++;
	  break;
        case 'l':
	    origine.z--;
            break;
      case 's':
	  origine.x++;
	  break;
      case 'z':
	    origine.x--;
	    break;	    
      case 'd':
	  origine.y++;
	  break;
      case 'q':
	  origine.y--;
	  break;
      case '+':
	  rayon++;
	  break;
      case '-':
	  rayon--;
	  break;
      case 'c':
	  forme++;
	  forme = forme % nb_formes;
      case 'f':
	  full = !full;
      }
      if (forme == 1)
	  cube = test_sphere(origine,rayon,full);
      else
	  cube = test_cube(origine,rayon,full);
      display("/dev/ttyACM0", cube);
    }
    display("/dev/ttyACM0", new_cube());
    
    free(cube);
    
    return 0;
}

