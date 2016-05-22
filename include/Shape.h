#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

#include <cmath>
#include <list>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "Point.h"
#include "Cube.h"

using namespace std;

class Shape
{

private: 
    list<Point> vertices;
    Cube cube;
public:
  Shape(Cube cube);
  Shape(Cube cube, list<Point> vertices);

  void on();
  void addPoint(Point p);
  void addPoint(uint8_t x, uint8_t y, uint8_t z);

  void removePoint(Point p);
  void clearShape();

  //OkShape
  void loadOkShape();

  //Circular Shapes
  void circularShape(int r, Point origin, int type);
  void loadSphereShape(int radius, Point origin, bool full);
  void loadCircleShape(int radius, Point origine, Point orientation, bool full);

  //Polygonal Shapes
  void loadCubeShape(int radius, Point origin, bool full);

  list<Point> getPoints() const;
  Cube getCube() const;

  void describe() const;

};

Point CircSpherPoint(int r, Point origin, uint8_t theta, uint8_t phi);

#endif
