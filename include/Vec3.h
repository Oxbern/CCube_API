#ifndef VEC3_H
#define VEC3_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>


class Vec3 {

private: 
    int x;
    int y;
    int z;
    
public:
  Vec3();
  Vec3(int x, int y, int z);
  
  void setX(int x);
  void setY(int y);
  void setZ(int z);

  int getX() const;
  int getY() const;
  int getZ() const;

  bool operator==(Vec3 p);
  
  void describe() const;

};

#endif
