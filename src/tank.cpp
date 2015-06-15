
#include "tank.h"
#include "math.h"

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

void Tank::update(sf::Time elapsed) {
    float e = elapsed.asSeconds();
    // update position
    if (!(movingUp ^ movingDown)) {
        // don't move if orders are contradictory
    } else {
        if (movingUp) {
            velocity = sf::Vector2f(0.0, -1.0);
        }
        if (movingDown) {
            velocity = sf::Vector2f(0.0,  1.0);
        }
        float current_x = velocity.x;
        float current_y = velocity.y;
        // transform the rotation in radian
        float rotation = this->getRotation() * 3.14159 / 180;
        // rotation matrix of the velocity vector
        float x_offset = current_x * cos(rotation) - current_y * sin(rotation);
        float y_offset = current_x * sin(rotation) + current_y * cos(rotation);

        this->move(x_offset, y_offset);
    }
    // update rotation
    if (turningLeft ^ turningRight) {
        float angle = 0.0;
        if (turningLeft) {
            angle = -100 * e;
        }
        if (turningRight) {
            angle =  100 * e;
        }
        this->rotate(angle);
    }
}

