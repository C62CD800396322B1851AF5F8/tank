
#include <SFML/Graphics.hpp>
#include "tank.h"

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

void repaint(sf::RenderWindow& window, std::vector<Tank>& tanks) {
    // Clear screen
    window.clear();

    // Draw the sprites
    for (std::size_t i = 0; i < tanks.size(); i++) {
        Tank& t = tanks[i];
        window.draw(t);
    }

    // Update the window
    window.display();
}

void update(sf::Time& elapsed, std::vector<Tank>& tanks) {
    for (std::size_t i = 0; i < tanks.size(); i++) {
        Tank& t = tanks[i];
        t.update(elapsed);
    }
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Game");

    // track elapsed time
    sf::Clock clock;

    // create a Tank
    std::vector<Tank> tanks(1);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            exit(event, window);
            moveTank(event, tanks[0]);
        }

        sf::Time elapsed = clock.restart();

        update(elapsed, tanks);
        repaint(window, tanks);
    }

    return EXIT_SUCCESS;
}

