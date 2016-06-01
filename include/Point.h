#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#include <iostream>

/**
 * @class Point
 */
class Point
{
 private: 
    uint8_t x;
    uint8_t y;
    uint8_t z;

 public:
    Point();
    Point(uint8_t x, uint8_t y, uint8_t z);

    // virtual ~Point();

    bool isOutOfBounds(uint8_t x, uint8_t y, uint8_t z);
  
    void setX(int x);
    void setY(int y);
    void setZ(int z);
  
    void incrX();
    void incrY();
    void incrZ();
    void decrX();
    void decrY();
    void decrZ();


    uint8_t getX() const;
    uint8_t getY() const;
    uint8_t getZ() const;
    
    bool operator==(Point p);

    Point& operator=(const Point &p);
  
    void print(std::ostream &str) const;
};

std::ostream& operator << (std::ostream &out, const Point &p);

Point operator + (const Point &p1, const Point &p2);
    
#endif
