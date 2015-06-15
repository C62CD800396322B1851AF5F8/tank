
#ifndef __git_tank__tank__
#define __git_tank__tank__

#include <SFML/Graphics.hpp>
class Bullet;

#define TANK_SPEED 200.0f
#define TANK_SIZE 50
#define TANK_VELOCITY sf::Vector2f(0.0, -1.0)
#define TO_RADIAN * 3.14159 / 180

class Tank : public sf::RectangleShape {
public:
    Tank() : RectangleShape(sf::Vector2f(TANK_SIZE, TANK_SIZE)) {
        this->setPosition(100, 100);
        this->setOrigin(TANK_SIZE/2, TANK_SIZE/2);
        this->velocity = sf::Vector2f(0.0, -1.0);
    }
public:
    void moveUp();
    void stopUp();
    void moveDown();
    void stopDown();
    void turnLeft();
    void stopLeft();
    void turnRight();
    void stopRight();
public:
    float getRadius();
public:
    Bullet fire();
    void update(sf::Time elapsed, float width, float height);
private:
    bool movingUp = false;
    bool movingDown = false;
    bool turningLeft = false;
    bool turningRight = false;
    sf::Vector2f velocity;
};

#endif /* defined(__git_tank__tank__) */

