#include "Ball.h"

Ball::Ball() : ShapeToDisplay(1, Point(4, 4, 4), true, 9, 9, 9), direction(Point(1, 1, 1)) {
    LOG(1, "ball()");
    on(origin.getX(), origin.getY(), origin.getZ());
}

Ball::~Ball() {
    LOG(1, "~ball()");
}

void Ball::action() {
    origin = origin + direction;
    bounce();
    initialisation();
    std::cout << "Origin : " << origin << std::endl;
}

void Ball::initialisation() {
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

void Ball::bounce() {
    LOG(1, "Ball::bounce()");
    if (origin.getX() == 0 || origin.getX() == 8)
        direction.setX(-direction.getX());
    if (origin.getY() == 0 || origin.getY() == 8)
        direction.setY(-direction.getY());
    if (origin.getZ() == 0 || origin.getZ() == 8)
        direction.setZ(-direction.getZ());

    //ShapeToDisplay::print(std::cout);
}

Point Ball::getDirection() const {
    return direction;
}

void Ball::setDirection(Point & p) {
    direction = p;
}

void Ball::setOrigin(Point &p)
{
    origin = p;
}