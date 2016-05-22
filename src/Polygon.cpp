#include "Polygon.h"
using namespace std;

Polygon::Polygon(Cube cube): Shape(cube) {}

Polygon::Polygon(Cube cube, list<Point> l) : Shape(cube,l) {}

void Polygon::on(){
    std::list<Point>::iterator iter ;
    for(iter = getPoints().begin() ; (iter != getPoints().end()) ;iter++){
    	getCube().on(iter->getX(), iter->getY(), iter->getZ());
    }
}
void Polygon::addPoint(Point p)
{
    this->getPoints().push_back(p);
}

void Polygon::removePoint(Point p)
{
    this->getPoints().remove(p);
}


void Polygon::describe() const
{
    std::list<Point>::const_iterator iter ;
    for(iter = getPoints().begin() ; (iter != getPoints().end()) ;iter++){
	cout << "x,y,z = " << iter->getX() << "," << iter->getY() <<"," << iter->getZ() << endl;
    }
}
