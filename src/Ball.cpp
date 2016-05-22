#include "Ball.h"

Ball::Ball(Cube cube) : Shape(cube) {
    this->positionBall = Point(3,3,3);
    this->directionBall = Vec3(-1,1,-1);
}

Vec3 Ball::getDirection(){
    return this->directionBall;
}

Point Ball::getPosition(){
    return this->positionBall;
}

void Ball::animateBall(){

}

void Ball::handleCollisions(Player p1, Player p2){

}
