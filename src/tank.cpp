
#include "tank.h"
#include "math.h"
#include "bullet.h"

sf::Vector2f rotateVector(sf::Vector2f v, float angle) {
    float current_x = v.x;
    float current_y = v.y;
    // rotation matrix of the velocity vector
    float x_offset = current_x * cos(angle) - current_y * sin(angle);
    float y_offset = current_x * sin(angle) + current_y * cos(angle);
    return sf::Vector2f(x_offset, y_offset);
}

void Tank::moveUp() {
    movingUp = true;
}
void Tank::stopUp() {
    movingUp = false;
}
void Tank::moveDown() {
    movingDown = true;
}
void Tank::stopDown() {
    movingDown = false;
}
void Tank::turnLeft() {
    turningLeft = true;
}
void Tank::stopLeft() {
    turningLeft = false;
}
void Tank::turnRight() {
    turningRight = true;
}
void Tank::stopRight() {
    turningRight = false;
}

float Tank::getRadius() {
    sf::Vector2f tsize = this->getSize();
    return sqrt(tsize.x*tsize.x + tsize.y*tsize.y)/2;
}

Bullet Tank::fire() {
    float rotation = this->getRotation() TO_RADIAN;
    sf::Vector2f direction = rotateVector(TANK_VELOCITY, rotation);
    sf::Vector2f p = this->getPosition();
    Bullet b(p.x, p.y, direction);
    float r = this->getRadius() + b.getRadius();
    b.move(direction * r);
    return b;
}

void Tank::update(sf::Time elapsed, float width, float height) {
    float e = elapsed.asSeconds();
    // update position
    if (!(movingUp ^ movingDown)) {
        // don't move if orders are contradictory
    } else {
        if (movingUp) {
            velocity = TANK_VELOCITY;
        }
        if (movingDown) {
            velocity = TANK_VELOCITY * (-1.0f);
        }
        
        float rotation = this->getRotation() TO_RADIAN;
        sf::Vector2f offset = rotateVector(velocity, rotation);
        
        this->move(offset * TANK_SPEED * e);
        
        // stay in the arena
        sf::Vector2f p = this->getPosition();
        float r = this->getRadius();
        if (p.x < r) {
            p.x = r;
        }
        if (p.y < r) {
            p.y = r;
        }
        if (p.x > width-r) {
            p.x = width-r;
        }
        if (p.y > height-r) {
            p.y = height-r;
        }
        this->setPosition(p.x, p.y);
    }
    // update rotation
    if (turningLeft ^ turningRight) {
        float angle = 0.0;
        if (turningLeft) {
            angle = -100;
        }
        if (turningRight) {
            angle =  100;
        }
        this->rotate(angle * e);
    }
}

