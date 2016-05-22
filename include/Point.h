#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>


class Point {

private: 
    uint8_t x;
    uint8_t y;
    uint8_t z;

public:
  Point();
  Point(uint8_t x, uint8_t y, uint8_t z);

  bool isOutOfBounds(uint8_t x, uint8_t y, uint8_t z);
  
  void setX(uint8_t x);
  void setY(uint8_t y);
  void setZ(uint8_t z);

  uint8_t getX() const;
  uint8_t getY() const;
  uint8_t getZ() const;

  bool operator==(Point p);
  
  void describe() const;

};

#endif
