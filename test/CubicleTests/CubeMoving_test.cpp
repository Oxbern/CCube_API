#ifndef _WIN32
#include "Controller.h"
#include <ncurses.h>
#include "Cube.h"
// #include <iostream>

#define TIME ((const struct timespec[]){{0, 100000000L}})

int main(int argc, char** argv) {
    
    Controller c;
    c.connectDevice(1);
    Point *p = new Point(3,3,3);
    initscr();
    bool end = false;
    c.on(p->getX(),p->getY(),p->getZ());
    c.display();
    sleep(3);
    while(!end){
        //printcmd();
        keypad(stdscr, TRUE);
        noecho();
      switch(getch()) { 
      case 'm':
          p->setZ(p->getZ() + 1);
          break;
      case 'l':
          p->setZ(p->getZ() - 1);
          break;
      case 's':
          p->setY(p->getY() + 1);
          break;
      case 'z':
          p->setY(p->getY() - 1);
            break;	    
      case 'd':
          p->setX(p->getX() + 1);
          break;
      case 'q':
          p->setX(p->getX() - 1);
          break;
      case 't':
          end = true;
      default:
          break;
      }
      c.on(p->getX(),p->getY(),p->getZ());
      c.display();
    }
    endwin();
    
    
    c.disconnectDevice();
    return 0;
}
#else
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "No curses for windows, this test can't be compiled for Windows" << std::endl;
}
#endif
