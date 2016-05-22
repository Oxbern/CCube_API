#include "Point.h"
#include <iostream>
#include <cmath>

using namespace std;

Point::Point() : x(0), y(0), z(0)
{}

Point::Point(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z)
{
    if (x < 0 || x > 8){
	perror("Index (x) of led out of bounds");
	exit(EXIT_FAILURE);
    }
	if (y < 0 || y > 8){
	perror("Index (y) of led out of bounds");
	exit(EXIT_FAILURE);
    }
    if (z < 0 || z > 8){
	perror("Index (z) of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

bool Point::isOutOfBounds(uint8_t x,uint8_t y, uint8_t z){
    if (x < 0 || x > 8)
	return true;
    if (y < 0 || y > 8)
	return true;
    if (z < 0 || z > 8)
	return true;
    return false;
}

void Point::setX(uint8_t x)
{
    if (x >= 0 && x < 9)
	this->x = x;
    else{
	perror("Index (x) of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

void Point::setY(uint8_t y)
{
    if (y >= 0 && y < 9)
	this->y = y;
    else{
	perror("Index (y) of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

void Point::setZ(uint8_t z)
{
    if (z >= 0 && z < 9)
	this->z = z;
    else{
	perror("Index (z) of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

uint8_t Point::getX() const
{
    return this->x;
}

uint8_t Point::getY() const
{
    return this->y;
} 

uint8_t Point::getZ() const
{
    return this->z;
}

void Point::describe() const
{
    cout << "x,y,z = " << this->x << "," << this->y <<"," << this->z << endl;
}

bool Point::operator== (Point p){
    return (this->x == p.getX() &&
     	    this->y == p.getY() &&
    	    this->z == p.getZ());
}
