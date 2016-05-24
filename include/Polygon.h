#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"

using namespace std;

class Polygon : Shape
{

private: 
    
public:
  Polygon(Cube *cube);
  Polygon(Cube *cube, list<Point> vertices);

  void on();
  void addPoint(Point p);
  void removePoint(Point p);

  void describe() const;

};

#endif
