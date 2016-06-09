#ifndef BALL_H
#define	BALL_H

/*!
 * \file Ball.h
 * \brief A test class
 * 
 * \version 0.1
 */

#include "ShapeToDisplay.h"

/*!
 * \class Ball
 * \brief Class describing a ball with bounces on the device 
 */
class Ball : public ShapeToDisplay
{
    private:
        Point direction; /*!< 3D vectors which shows were the ball goes */
    
    public:
    /*! 
     * \brief Constructor
     * Constructor of the class Ball
     */
    Ball();

    /*!
     * \brief Destructor
     * Destructor of the class Ball
     */
    virtual ~Ball();

    /*! 
     * \fn int getDirection() const
     * 
     * \brief Returns the direction of the ball
     *
     * \return Point direction : where the ball goes
     */
    Point getDirection() const;
    
    /*! 
     * \fn void setDirection(Point &p)
     * 
     * \brief Sets the direction of the ball to the vector p
     */
    void setDirection(Point &p);

    /*! 
     * \fn void action()
     * 
     * \brief Moves the ball (origin becomes origin + direction)
     */
    void action();

    /*! 
     * \fn void bounce()
     * 
     * \brief Changes the direction if the ball touches the limits of the device
     */    
    void bounce();
    
    /*! 
     * \fn void initialisation()
     * 
     * \brief Initialises the 3D array of the device 
     */
    void initialisation();
    
    /*! 
     * \fn void setOrigin(Point &p)
     * 
     * \brief Sets the origin of the ball to the Point p
     */    
    void setOrigin(Point &p);
};

#endif	/* BALL_H */

