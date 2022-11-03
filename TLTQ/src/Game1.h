#pragma once
#include <SFML/Graphics.hpp>

class Game1 {
private:
    int questionNumber;
    bool questionResponse;
    bool leftAnswer;
    bool rightAnswer;
    bool next;

    sf::Event event;

    sf::Texture game1Texture;
    sf::Sprite game1Sprite;

    sf::Font font;
    sf::Text question1;
    sf::Text correctText1;
    sf::Text incorrectText1;
    //sf::Text question2;
    sf::Text correctText2;
    sf::Text incorrectText2;

    sf::Vector2i m_position;

public:
    // Constructor
    Game1();

    // Public Functions
    void update(sf::RenderWindow &window, sf::Vector2i position);
    void draw(sf::RenderWindow &window);
};


