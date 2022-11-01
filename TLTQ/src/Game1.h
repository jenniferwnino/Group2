#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Set individual question characteristics
struct Game1Question {
    sf::Text correctText;
    sf::Text incorrectText;

    bool leftCorrect;

    Game1Question(std::string correct, std::string incorrect, sf::Font font, int fontSize, sf::Vector2f pos);
};


class Game1 {
private:
    int questionNumber;
    int questionFontSize;
    int answerFontSize;
    sf::Vector2f questionPos;
    sf::Vector2f answerPos;

    bool questionResponse;
    bool leftAnswer;
    bool rightAnswer;
    bool next;

    std::string correctTemp;
    std::string incorrectTemp;

    sf::Event event;

    sf::Texture game1Texture;
    sf::Sprite game1Sprite;

    sf::Font font;
    sf::Text question;

    sf::Text correctText1;
    sf::Text incorrectText1;
    sf::Text correctText2;
    sf::Text incorrectText2;

    sf::Vector2i m_position;

    std::vector<Game1Question> questions;


public:
    // Constructor
    Game1();

    // Public Functions
    void update(sf::RenderWindow &window, sf::Vector2i position);
    void draw(sf::RenderWindow &window);
};


