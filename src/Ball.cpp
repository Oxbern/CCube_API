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
    this->translateShape(this->directionBall);
}

void handleCollisionFloorAndWalls(Ball &b){
    if (b.getPosition().getX() == 1 || b.getPosition().getX() == 7 ){
	b.getDirection().setX(-b.getDirection().getX());
    }
    if (b.getPosition().getY() == 1 || b.getPosition().getY() == 7 ){
	b.getDirection().setY(-b.getDirection().getY());
    }
    if (b.getPosition().getZ() == 1 || b.getPosition().getZ() == 7 ){
	b.getDirection().setZ(-b.getDirection().getZ());
    }
}

void handleCollisionPlayer(Ball &b, Player p){
    int x = b.getPosition().getX() - p.getPosition().getX();
    int y = b.getPosition().getY() - p.getPosition().getY();
    int z = b.getPosition().getZ() - p.getPosition().getZ();
    if (z < 2 && x < 2 && y < 2)
	b.getDirection().setY(-b.getDirection().getY());

}
void Ball::handleCollisions(Player p1, Player p2){
    handleCollisionFloorAndWalls(*this);
    handleCollisionPlayer(*this,p1);
    handleCollisionPlayer(*this,p2);
}


