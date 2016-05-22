#include "Vec3.h"
#include <iostream>
#include <cmath>

using namespace std;

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(int x, int y, int z) : x(x), y(y), z(z) {}

void Vec3::setX(int x)
{
    this->x = x;
}

void Vec3::setY(int y)
{
    this->y = y;
}

void Vec3::setZ(int z)
{
    this->z = z;
}

int Vec3::getX() const
{
    return this->x;
}

int Vec3::getY() const
{
    return this->y;
} 

int Vec3::getZ() const
{
    return this->z;
}

void Vec3::describe() const
{
    cout << "x,y,z = " << this->x << "," << this->y <<"," << this->z << endl;
}

bool Vec3::operator== (Vec3 p){
    return (this->x == p.getX() &&
     	    this->y == p.getY() &&
    	    this->z == p.getZ());
}
