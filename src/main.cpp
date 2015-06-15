
#include <SFML/Graphics.hpp>

// Close the rendering window and therefore exits the program
void exit(sf::Event event, sf::Window& window) {
    // Close window: exit
    bool close = event.type == sf::Event::Closed;
    // Escape pressed: exit
    bool escape = event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape;
    // check one or the other
    if (close || escape) {
        window.close();
    }
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Game");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            exit(event, window);
        }

        // Clear screen
        window.clear();

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

