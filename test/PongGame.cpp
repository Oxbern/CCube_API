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
    Point origine(2,3,3);
    Vec3 dir(-1,1,-1);
    Ball b(cube);

    bool endGame = false;
    
     while(!endGame){
	 //Animate the ball
	 b.animateBall();
	 b.handleCollisions(p1,p2);
	 keypad(stdscr, TRUE);
	 noecho();

	 //Move players
	 char moveP1 = '&';
	 moveP1 = getch();
	 char moveP2 = '&';
	 moveP2 = getch();
	 
	 p1.movePlayer(moveP1);
	 p2.movePlayer(moveP2);

	 if (moveP1 == '<' || moveP2 == '<')
	     endGame = true;
     }
     
     // Shape s(cube);
     // s.on();
     // s.addPoint(Point(3,3,3));
     // s.describe();
     // s.clearShape();
     // s.describe();
     // s.loadOkShape();
     // s.describe();

    return 0;
}


