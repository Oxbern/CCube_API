#include "Player.h"

Player::Player(Cube cube, int number) : Shape(cube) {
    if (number == 1)
	this->positionPlayer = Point(3,0,3);
    else if (number == 2)
	this->positionPlayer = Point(3,8,3);
    else
	this->positionPlayer = Point(3,3,3);
    this->sizePlayer = 1;

    this->addPoint(this->positionPlayer.getX()-1,this->positionPlayer.getY(),this->positionPlayer.getZ()+1);
    this->addPoint(this->positionPlayer.getX(),this->positionPlayer.getY(),this->positionPlayer.getZ()+1);
    this->addPoint(this->positionPlayer.getX()+1,this->positionPlayer.getY(),this->positionPlayer.getZ()+1);
    
    this->addPoint(this->positionPlayer.getX()-1,this->positionPlayer.getY(),this->positionPlayer.getZ()-1);
    this->addPoint(this->positionPlayer.getX(),this->positionPlayer.getY(),this->positionPlayer.getZ()-1);
    this->addPoint(this->positionPlayer.getX()+1,this->positionPlayer.getY(),this->positionPlayer.getZ()-1);

    this->addPoint(this->positionPlayer.getX()-1,this->positionPlayer.getY(),this->positionPlayer.getZ());
    this->addPoint(this->positionPlayer.getX()+1,this->positionPlayer.getY(),this->positionPlayer.getZ());

}

Point Player::getPosition() const{
    return this->positionPlayer;
}
int Player::getSize() const{
    return this->sizePlayer;
}

void Player::movePlayer(char c){
    Vec3 v(0,0,0);
    switch (c) {
    case 'z':
	//Up
	v = Vec3(0,0,1);
	this->translateShape(v);
	break;
    case 's':
	//Down
	v = Vec3(0,0,-1);
	this->translateShape(v);
	break;
    case 'd':
	//Right
	v = Vec3(1,0,0);
	this->translateShape(v);
	break;
    case 'q':
	//Left
	v = Vec3(-1,0,0);
	this->translateShape(v);
	break;
    default:
	break;
    }
}
