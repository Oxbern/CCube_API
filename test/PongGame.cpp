#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>

#include "Point.h"
#include "Vec3.h"
#include "Cube.h"
#include "Player.h"
#include "Ball.h"

int main(int argc, char *argv[]) {
    
    Cube cube;
    Player p1(cube,1);
    Player p2(cube,2);
    Point origine(3,3,6);
    Vec3 dir(0,0,-1);
    Ball b(cube,origine,dir);
    bool endGame = false;
 
    initscr();   // mandatory curses init
    //char chr;
    // int a = 0, s = 0, nul = 0, er = 0, pass = 0;
    // while(true){
    // 	cbreak();         // don't interrupt for user input
    // 	//noecho();
    // 	timeout(100);     // wait 500ms for key press
    // 	//keypad(stdscr, TRUE);
    // 	chr = getch();
    // 	switch (chr){
    // 	case 'a' :
    // 	    a++;
    // 	    break;
    // 	case 's' :
    // 	    s++;
    // 	    break;
    // 	case ERR:
    // 	    er++;
    // 	    break;
    // 	default :
    // 	    nul++;
    // 	};
    // 	pass++;
    // 	printf("a = %i, s = %i, nul = %i, er = %i, pass = %i\n",a,s,nul,er, pass);
    // 	//refresh();
    // }
        
    while(!endGame){
	//Animate the ball
	b.animateBall();
	b.handleCollisions(p1,p2);
        cout << b.getDirection().getX() << "," << b.getDirection().getY() << "," << b.getDirection().getZ() << "\n";
        b.display("/dev/ttyACM0");
        sleep(1);
	//Move players
	// char movePlayer;
	// cbreak();
	// timeout(100);
	// movePlayer = getch();
	// cout << "Getch :" << movePlayer << "\n";
	
	// p1.movePlayer(movePlayer);
	// p2.movePlayer(movePlayer);
	
	// if (movePlayer == 't' || movePlayer == 't')
	//      endGame = true;
        // p1.display("/dev/ttyACM0");
        // p2.display("/dev/ttyACM0");

    }
    
    return 0;
}


