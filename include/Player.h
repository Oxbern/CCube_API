#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <ncurses.h>
#include "Shape.h"

class Player : public Shape {

private: 
    Point positionPlayer;
    int sizePlayer;
    
public:
    
    Player(Cube cube, int number);
    Point getPosition() const;
    int getSize() const;
    
    void movePlayer(char c);
    //void getsBigger();
  
};

#endif
