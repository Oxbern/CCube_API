#include "Ball.h"

/*! 
 * \brief Constructor
 * Constructor of the class Ball
 */
Ball::Ball() : ShapeToDisplay(1, Point(4, 4, 4), true, 9, 9, 9), direction(Point(1, 1, 1)) 
{
    LOG(1, "ball()");
    on(origin.getX(), origin.getY(), origin.getZ());
}

/*!
 * \brief Destructor
 * Destructor of the class Ball
 */
Ball::~Ball() 
{
    LOG(1, "~ball()");
}

/*! 
 * \fn void action()
 * 
 * \brief Moves the ball (origin becomes origin + direction)
 */
void Ball::action() 
{
    origin = origin + direction;
    bounce();
    initialisation();
    std::cout << "Origin : " << origin << std::endl;
}

/*! 
 * \fn void initialisation()
 * 
 * \brief Initialises the 3D array of the device 
 */
void Ball::initialisation() 
{
    LOG(1, "Ball::initialisation()");
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            for (int z = 0; z < sizeZ; z++) {
                if (x == origin.getX() && y == origin.getY() && z == origin.getZ())
                    status[x][y][z] = true;
                else
                    status[x][y][z] = false;
            }
        }
    }
}

/*! 
 * \fn void bounce()
 * 
 * \brief Changes the direction if the ball touches the limits of the device
 */
void Ball::bounce() 
{
    LOG(1, "Ball::bounce()");
    if (origin.getX() == 0 || origin.getX() == 8)
        direction.setX(-direction.getX());
    if (origin.getY() == 0 || origin.getY() == 8)
        direction.setY(-direction.getY());
    if (origin.getZ() == 0 || origin.getZ() == 8)
        direction.setZ(-direction.getZ());

    //ShapeToDisplay::print(std::cout);
}

/*! 
 * \fn int getDirection() const
 * 
 * \brief Returns the direction of the ball
 *
 * \return Point direction : where the ball goes
 */
Point Ball::getDirection() const 
{
    return direction;
}

/*! 
 * \fn void setDirection(Point &p)
 * 
 * \brief Sets the direction of the ball to the vector p
 */
void Ball::setDirection(Point & p) 
{
    direction = p;
}

/*! 
 * \fn void setOrigin(Point &p)
 * 
 * \brief Sets the origin of the ball to the Point p
 */
void Ball::setOrigin(Point &p) 
{
    origin = p;
}