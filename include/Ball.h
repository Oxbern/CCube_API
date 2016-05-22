#ifndef BALL_H
#define BALL_H

#include "Ball.h"
#include "Shape.h"
#include "Vec3.h"
#include "Player.h"

class Ball : Shape {

private:
    Point positionBall;
    Vec3 directionBall;

public:
    Ball(Cube cube);
    Vec3 getDirection();
    Point getPosition();
    
    void animateBall();
    void handleCollisions(Player p1, Player p2);
    

};


#endif
