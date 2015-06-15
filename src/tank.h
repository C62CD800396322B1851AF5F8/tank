
#ifndef __git_tank__tank__
#define __git_tank__tank__

#include <SFML/Graphics.hpp>

#define SIZE 50

class Tank : public sf::RectangleShape {
public:
    Tank() : RectangleShape(sf::Vector2f(SIZE,SIZE)) {
        this->setPosition(100, 100);
        this->setOrigin(SIZE/2, SIZE/2);
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
    float getRadius();
    void update(sf::Time elapsed);
private:
    bool movingUp = false;
    bool movingDown = false;
    bool turningLeft = false;
    bool turningRight = false;
    sf::Vector2f velocity;
};

#endif /* defined(__git_tank__tank__) */

