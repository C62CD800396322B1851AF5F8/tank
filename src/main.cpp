
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "bullet.h"
#include "obstacle.h"
#include "tank.h"

#define WIDTH 800
#define HEIGHT 600

// Close the rendering window and therefore exits the program
void exit(sf::Event& event, sf::Window& window) {
    // Close window: exit
    bool close = event.type == sf::Event::Closed;
    // Escape pressed: exit
    bool escape = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
    // check one or the other
    if (close || escape) {
        window.close();
    }
}

void moveTank(sf::Event& event, Tank& tank) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                tank.moveUp();
                break;
            case sf::Keyboard::Down:
                tank.moveDown();
                break;
            case sf::Keyboard::Left:
                tank.turnLeft();
                break;
            case sf::Keyboard::Right:
                tank.turnRight();
                break;
            default:
                break;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                tank.stopUp();
                break;
            case sf::Keyboard::Down:
                tank.stopDown();
                break;
            case sf::Keyboard::Left:
                tank.stopLeft();
                break;
            case sf::Keyboard::Right:
                tank.stopRight();
                break;
            default:
                break;
        }
    }
}

void actionTank(sf::Event& event, std::vector<Bullet>& bullets, Tank& tank, sf::Texture& bullet_texture) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
        Bullet b = tank.fire();
        b.setTexture(&bullet_texture);
        bullets.push_back(b);
    }
}

void testFireBullet(sf::Window& window, sf::Event& event, std::vector<Bullet>& bullets, Tank& tank) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i p = sf::Mouse::getPosition(window);
        sf::Vector2f p_t = tank.getPosition();
        Bullet b(p.x, p.y, sf::Vector2f(p_t.x-p.x, p_t.y-p.y));
        bullets.push_back(b);
    }
}

void repaint(sf::RenderWindow& window, std::vector<Bullet>& bullets, std::vector<Obstacle>& obstacles, std::vector<Tank>& tanks) {
    // Clear screen
    window.clear();

    // Draw the sprites
    for (std::size_t i = 0; i < bullets.size(); i++) {
        Bullet& b = bullets[i];
        window.draw(b);
    }
    for (std::size_t i = 0; i < tanks.size(); i++) {
        Tank& t = tanks[i];
        window.draw(t);
    }
    for (std::size_t i = 0; i < obstacles.size(); i++) {
        Obstacle& o = obstacles[i];
        window.draw(o);
    }

    // Update the window
    window.display();
}

void update(sf::Time& elapsed, std::vector<Bullet>& bullets, std::vector<Obstacle>& obstacles, std::vector<Tank>& tanks) {
    // move everything
    for (std::size_t i = 0; i < bullets.size(); i++) {
        Bullet& b = bullets[i];
        b.update(elapsed, WIDTH, HEIGHT);
    }
    for (std::size_t i = 0; i < tanks.size(); i++) {
        Tank& t = tanks[i];
        t.update(elapsed, WIDTH, HEIGHT, obstacles);
    }
    // check for collisions
    for (std::size_t i = 0; i < bullets.size(); i++) {
        Bullet& b = bullets[i];
        for (std::size_t j = 0; j < tanks.size(); j++) {
            Tank& t = tanks[j];
            if (b.intersects(t)) {
                bullets.erase(bullets.begin() + i);
                tanks.erase(tanks.begin() + j);
            }
        }
        for (std::size_t j = 0; j < obstacles.size(); j++) {
            Obstacle& o = obstacles[j];
            if (b.intersects(o)) {
                bullets.erase(bullets.begin() + i);
            }
        }
    }
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tank Game");

    // track elapsed time
    sf::Clock clock;

    // create a Tank
    std::vector<Tank> tanks(1);

    // add a texture to the tank
    sf::Texture tank_texture;
    if (!tank_texture.loadFromFile(resourcePath() + "tank_texture.png")) {
        return EXIT_FAILURE;
    }
    for (std::size_t i = 0; i < tanks.size(); i++) {
        Tank& t = tanks[i];
        t.setTexture(&tank_texture);
    }

    // create the bullet list
    std::vector<Bullet> bullets;

    // create a bullet texture
    sf::Texture bullet_texture;
    if (!bullet_texture.loadFromFile(resourcePath() + "bullet_texture.png")) {
        return EXIT_FAILURE;
    }

    // create an obstacle
    std::vector<Obstacle> obstacles;
    obstacles.push_back(Obstacle(WIDTH/3, HEIGHT/2));
    // or two
    obstacles.push_back(Obstacle(2*WIDTH/3, HEIGHT/2));

    // create an obstacle texture
    sf::Texture obstacle_texture;
    if (!obstacle_texture.loadFromFile(resourcePath() + "obstacle_texture.png")) {
        return EXIT_FAILURE;
    }

    for (std::size_t i = 0; i < obstacles.size(); i++) {
        Obstacle& o = obstacles[i];
        o.setTexture(&obstacle_texture);
    }

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            exit(event, window);
            moveTank(event, tanks[0]);
            actionTank(event, bullets, tanks[0], bullet_texture);
            testFireBullet(window, event, bullets, tanks[0]);
        }

        sf::Time elapsed = clock.restart();

        update(elapsed, bullets, obstacles, tanks);
        repaint(window, bullets, obstacles, tanks);
    }

    return EXIT_SUCCESS;
}
