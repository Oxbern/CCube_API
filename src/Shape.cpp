#include "Shape.h"
using namespace std;

Shape::Shape(Cube *cube): cube(cube) {}

Shape::Shape(Cube *cube, list<Point> l) : cube(cube), vertices(l) {}

list<Point> Shape::getPoints() const{
    return vertices;
}

Cube *Shape::getCube() const{
    return cube;
}

void Shape::on(){
    std::list<Point>::iterator iter ;
    cube->off();
    for(iter = vertices.begin() ; (iter != vertices.end()) ;iter++){
    	cube->on(iter->getX(), iter->getY(), iter->getZ());
    }
}

void Shape::display(const char *dev){
    cube->display(dev);
}

void Shape::addPoint(Point p)
{
    this->vertices.push_back(p);
}

void Shape::addPoint(uint8_t x, uint8_t y, uint8_t z)
{
    Point p0;
    if (!p0.isOutOfBounds(x,y,z)){
	Point p(x,y,z);
	this->vertices.push_back(p);
    }
    else{
	perror("Error adding Point to Shape : Index of led out of bounds");
	exit(EXIT_FAILURE);
    }
}

void Shape::removePoint(Point p)
{
    this->vertices.remove(p);
}

void Shape::clearShape(){
    this->vertices.clear();
}

void Shape::translateShape(Vec3 v){
    std::list<Point>::iterator iter ;
    for(iter = vertices.begin(); (iter != vertices.end()); *iter++){
	iter->setX(iter->getX() + v.getX());
	iter->setY(iter->getY() + v.getY());
	iter->setZ(iter->getZ() + v.getZ());
    }
    on();
}

void Shape::describe() const
{
    std::list<Point>::const_iterator iter ;
    for(iter = vertices.begin() ; (iter != vertices.end()) ;iter++){
	cout << "x,y,z = " << iter->getX() << "," << iter->getY() <<"," << iter->getZ() << endl;
    }
}


void Shape::loadOkShape(){
    clearShape();
    // The O layer 1
    addPoint(4, 3, 6);
    addPoint(4, 2, 6);
    addPoint(4, 4, 5);
    addPoint(4, 1, 5);
    addPoint(4, 1, 4);
    addPoint(4, 4, 4);
    addPoint(4, 4, 3);
    addPoint(4, 1, 3);
    addPoint(4, 3, 2);
    addPoint(4, 2, 2);

    // The O layer 2
    addPoint(3, 3, 6);
    addPoint(3, 2, 6);
    addPoint(3, 4, 5);
    addPoint(3, 1, 5);
    addPoint(3, 1, 4);
    addPoint(3, 4, 4);
    addPoint(3, 4, 3);
    addPoint(3, 1, 3);
    addPoint(3, 3, 2);
    addPoint(3, 2, 2);


    // The K
    addPoint(4, 5, 6);
    addPoint(4, 5, 5);
    addPoint(4, 5, 4);
    addPoint(4, 5, 3);
    addPoint(4, 5, 2);
    addPoint(4, 7, 6);
    addPoint(4, 6, 5);
    addPoint(4, 6, 3);
    addPoint(4, 7, 2);

    // The K
    addPoint(3, 5, 6);
    addPoint(3, 5, 5);
    addPoint(3, 5, 4);
    addPoint(3, 5, 3);
    addPoint(3, 5, 2);
    addPoint(3, 7, 6);
    addPoint(3, 6, 5);
    addPoint(3, 6, 3);
    addPoint(3, 7, 2);

    on();
}

Point CircSpherPoint(int r, Point origin, uint8_t theta, uint8_t phi, int n){
    uint16_t x,y,z;
    x = round(r * sin(2*theta*M_PI/n) * cos(phi*M_PI/n) + origin.getX());
    y = round(r * sin(2*theta*M_PI/n) * sin(phi*M_PI/n) + origin.getY());
    z = round(r * cos(2*theta*M_PI/n) + origin.getZ());
    Point p(x,y,z);
    return p;
}

void Shape::circularShape(int r, Point origin, int type){
    //Loads a circular shape (circle or sphere)
    //Type 1 = circular, 2 = spherical
    int n = 30;
    for (uint8_t theta = 0; theta < n; theta++)
	if (type == 1)
	    for (uint8_t phi = 0; phi < n; phi++) 
		addPoint(CircSpherPoint(r,origin,theta,phi,n));  
        else if (type == 2)
	    addPoint(CircSpherPoint(r,origin,theta,0,n)); 
}


void Shape::loadSphereShape(int radius, Point origin, bool full){
    clearShape();
    if (!full){
	uint8_t r = radius;
	circularShape(r,origin,1);
    }
    else{
	for (double r = 0; r <= radius; r+=0.5)
	    circularShape(r,origin,1);
    }
    on();
}


void Shape::loadCircleShape(int radius, Point origin, Point orientation, bool full){
    clearShape();
    if (!full){
	uint8_t r = radius;
	circularShape(r,origin,2);
    }
    else{
	for (double r = 0; r <= radius; r+=0.5)
	    circularShape(r,origin,2);
    }
    on();
}

void Shape::loadCubeShape(int radius, Point origin, bool full){
    clearShape();
    uint16_t x,y,z;

    for (uint8_t i = 0; i<=radius;i++){
	for (uint8_t j = 0; j<=radius;j++){
	    for (uint8_t k = 0; k<=radius;k++){
		x = origin.getX()+i;
		y = origin.getY()+j;
		z = origin.getZ()+k;
		addPoint(x,y,z);
	    }
	}
    }
    on();
}
