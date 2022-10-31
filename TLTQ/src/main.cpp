#include <SFML/Graphics.hpp>
#include "Game1.h"

int main()
{
    int windowStatus = 0;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Climate Stompers");
    sf::Vector2i position;

    sf::Texture mainTexture;
    mainTexture.loadFromFile("../TLTQ/graphics/climateStompersMainMenu.png");
    sf::Sprite mainSprite(mainTexture);

    Game1 game1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Check if the window was closed by clicking "X"
            if (event.type == sf::Event::Closed)
                window.close();

            // Check if window was closed by hitting "esc" key
            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();

            }

            // TEMP SOLUTION TO MOVE TO GAME 1
            if (event.type == sf::Event::KeyPressed) {
                windowStatus = 1;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                position = sf::Mouse::getPosition(window);
            }
        }

        // Display main menu
        if (windowStatus == 0) {
            window.clear();
            window.draw(mainSprite);
            window.display();
        }

        // Run game 1
        if (windowStatus == 1) {
            game1.update(window, position);
            game1.draw(window);
        }
    }

    return 0;
}