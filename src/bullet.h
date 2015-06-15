
#ifndef __git_tank__bullet__
#define __git_tank__bullet__

#include <SFML/Graphics.hpp>
class Tank;

#define BULLET_SPEED 750.0f

class Bullet : public sf::CircleShape {
public:
    Bullet(float x, float y, sf::Vector2f direction);
public:
    bool intersects(Tank& other);
    void update(sf::Time& elapsed, float width, float height);
private:
    sf::Vector2f direction;
};

#endif /* defined(__git_tank__bullet__) */

