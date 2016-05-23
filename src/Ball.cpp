#include "Ball.h"

Ball::Ball(Cube cube,Point origine, Vec3 dir) : Shape(cube) {
    this->positionBall = origine;
    this->directionBall = dir;
    this->loadCubeShape(0,origine,true);
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

void Ball::setDirection(Vec3 v){
    this->directionBall = v;
}

void handleCollisionFloorAndWalls(Ball &b, Vec3 direction){
    if (b.getPosition().getX() == 0 || b.getPosition().getX() == 8 ){
	b.setDirection(Vec3(-direction.getX(),direction.getY(),direction.getZ()));
    }
    if (b.getPosition().getY() == 0 || b.getPosition().getY() == 8 ){
        b.setDirection(Vec3(direction.getX(),-direction.getY(),direction.getZ()));
    }
    if (b.getPosition().getZ() == 0 || b.getPosition().getZ() == 8 ){
        b.setDirection(Vec3(direction.getX(),direction.getY(),-direction.getZ()));
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
    handleCollisionFloorAndWalls(*this, directionBall);
    // handleCollisionPlayer(*this,p1);
    // handleCollisionPlayer(*this,p2);
}


