
#include "bullet.h"
#include "math.h"
#include "tank.h"

float norm2(float x, float y) {
    return x * x + y * y;
}

Bullet::Bullet(float x, float y, sf::Vector2f direction) : sf::CircleShape(10) {
    this->setPosition(x, y);
    float dx = direction.x;
    float dy = direction.y;
    float norm = BULLET_SPEED/sqrt(norm2(dx, dy));
    this->direction = direction * norm;
}

bool Bullet::intersects(Tank& other) {
    sf::Vector2f tp = this->getPosition();
    sf::Vector2f op = other.getPosition();
    float vx = tp.x - op.x;
    float vy = tp.y - op.y;
    float r = this->getRadius() + other.getRadius();
    return norm2(vx, vy) <= r * r;
}

void Bullet::update(sf::Time& elapsed, float width, float height) {
    float e = elapsed.asSeconds();
    this->move(this->direction * e);
    
    // bounce on the walls
    sf::Vector2f p = this->getPosition();
    float r = this->getRadius();
    if (p.x < r) {
        direction = sf::Vector2f(-direction.x, direction.y);
        p.x = r;
    }
    if (p.y < r) {
        direction = sf::Vector2f(direction.x, -direction.y);
        p.y = r;
    }
    if (p.x > width - r) {
        direction = sf::Vector2f(-direction.x, direction.y);
        p.x = width - r;
    }
    if (p.y > height - r) {
        direction = sf::Vector2f(direction.x, -direction.y);
        p.y = height - r;
    }
    this->setPosition(p.x, p.y);
}

