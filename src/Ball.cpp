#include "Ball.h"
#include "Debug.h"
#include <time.h>
#include <cstdlib>

#define SIZE_SNAKE 5
/*! 
 * \brief Constructor
 * Constructor of the class Ball
 */
Ball::Ball() :
    ShapeToDisplay(1, Point(4, 4, 2), true, 9, 9, 9), direction(Point(0, 1, 0)) 
{
    LOG(1, "ball()");
    Point **snake = new Point*[SIZE_SNAKE];
    this->snake = snake;
    for(int i = 0; i<SIZE_SNAKE; i++)
        snake[i] = new Point(4,i,4);
    on(snake[0]->getX(), snake[0]->getY(), snake[0]->getZ());
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
 * \brief Moves the ball (snake becomes snake + direction)
 */
void Ball::action() 
{
    
    for(int i = 0; i<SIZE_SNAKE-1; i++){
        snake[i]->setX(snake[i+1]->getX());
        snake[i]->setY(snake[i+1]->getY());
        snake[i]->setZ(snake[i+1]->getZ());

    }
    srand(time(NULL));
    int changex = ((rand() % 4) == 0)? 1 : 0;
    int changey = ((rand() % 4) == 1)? 1 : 0;
    //int changez = ((rand() % 9) == 2)? 1 : 0;

    if (changex && !direction.getX()){
        int nb_aleax = (rand() % 2)? 1 : -1;
        direction.setX(nb_aleax);
        direction.setY(0);
        direction.setZ(0);

    } else if (changey && !direction.getY()) {
        int nb_aleay = (rand() % 2)? 1 : -1;
        direction.setY(nb_aleay);
        direction.setX(0);
        direction.setZ(0);
    } // else if (changez && !direction.getZ()) {
    //     int nb_aleaz = (rand() % 2)? 1 : -1;
    //     direction.setZ(nb_aleaz);
    //     direction.setY(0);
    //     direction.setX(0);
    // }
    snake[SIZE_SNAKE-1]->setX((snake[SIZE_SNAKE-1]->getX() + direction.getX())%9);
    snake[SIZE_SNAKE-1]->setY((snake[SIZE_SNAKE-1]->getY() + direction.getY())%9);
    snake[SIZE_SNAKE-1]->setZ((snake[SIZE_SNAKE-1]->getZ() + direction.getZ())%9);
    //bounce();
    
    initialisation();
}

/*! 
 * \brief Initialises the 3D array of the device 
 */
void Ball::initialisation() 
{
    LOG(1, "Ball::initialisation()");
    // for (int x = 0; x < sizeX; x++) {
    //     for (int y = 0; y < sizeY; y++) {
    //         for (int z = 0; z < sizeZ; z++) {
    //             if (x == snake.getX() && y == snake.getY() && z == snake.getZ())
    //                 status[x%9][y%9][z%9] = true;
    //             else
    //                 status[x%9][y%9][z%9] = false;
    //         }
    //     }
    // }
    off();
    for(int i = 0; i<SIZE_SNAKE; i++)
        on(snake[i]->getX()%9,snake[i]->getY()%9,snake[i]->getZ()%9);
}

/*! 
 * \brief Changes the direction if the ball touches the limits of the device
 */
void Ball::bounce() 
{
    // srand(time(NULL));
    // int nb_alea = (rand() % 2)? 1 : 0;
    // LOG(1, "Ball::bounce()");
    // if (origin.getX() == 0 || origin.getX() == 8){
    //     direction.setX(-direction.getX());
    //     // direction.setY( nb_alea);
    //     // direction.setZ( nb_alea);
    // }
    // if (origin.getY() == 0 || origin.getY() == 8){
    //     direction.setY(-direction.getY());
    //     // direction.setX( nb_alea);
    //     // direction.setZ( nb_alea);
    // }
    // if (origin.getZ() == 0 || origin.getZ() == 8){
    //     direction.setZ(-direction.getZ());
    //     // direction.setY( nb_alea);
    //     // direction.setX( nb_alea);
    // }
}

/*! 
 * \brief Returns the direction of the ball
 *
 * \return Point direction : where the ball goes
 */
Point Ball::getDirection() const 
{
    return direction;
}

/*! 
 * \brief Sets the direction of the ball to the vector p
 */
void Ball::setDirection(Point & p) 
{
    direction = p;
}

/*! 
 * \brief Sets the origin of the ball to the Point p
 */
void Ball::setOrigin(Point &p) 
{
    origin = p;
}
