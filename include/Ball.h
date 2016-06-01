// Class for demo

#ifndef BALL_H
#define	BALL_H

#include "ShapeToDisplay.h"

class Ball : public ShapeToDisplay
{
    private:
        Point direction;
    
    public:
    Ball();
    //Ball(const Ball& orig);
    virtual ~Ball();

    
    Point getDirection() const;
    void setDirection(Point &p);
    
    void action();
    
    void bounce();
    
    void initialisation();
    
    void setOrigin(Point &p);
};

#endif	/* BALL_H */

