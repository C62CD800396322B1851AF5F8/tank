
#ifndef __git_tank__obstacle__
#define __git_tank__obstacle__

#include <SFML/Graphics.hpp>

class Obstacle : public sf::CircleShape {
public:
    Obstacle(float x, float y);
};

#endif /* defined(__git_tank__obstacle__) */
