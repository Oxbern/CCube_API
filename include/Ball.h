#ifndef BALL_H
#define BALL_H

#include "Ball.h"
#include "Shape.h"
#include "Vec3.h"
#include "Player.h"

class Ball : public Shape {

private:
    Point positionBall;
    Vec3 directionBall;

public:
    Ball(Cube *cube,Point origine,Vec3 dir);

    Vec3 getDirection();
    Point getPosition();
    void setDirection(Vec3 v);
    void animateBall();
    void handleCollisions(Player p1, Player p2);
    

};


#endif
