
#include "obstacle.h"

Obstacle::Obstacle(float x, float y) : sf::CircleShape(80, 8) {
    this->setPosition(x, y);
}