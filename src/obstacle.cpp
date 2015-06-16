
#include "obstacle.h"

Obstacle::Obstacle(float x, float y) : sf::CircleShape(80, 8) {
    this->setOrigin(80, 80);
    this->setPosition(x, y);
}