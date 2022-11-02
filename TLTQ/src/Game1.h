#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Game1 {
public:
    // For individual question characteristics
    struct Game1Question {
    public:
        sf::Text correctText;
        sf::Text incorrectText;
        bool answeredCorrectly;
        bool leftCorrect;

        Game1Question(std::string& correct, std::string& incorrect, bool left, sf::Font& font, int& fontSize, sf::Vector2f& pos);
    };

    // Constructor
    Game1();

    // Public Functions
    void update(sf::RenderWindow &window, sf::Vector2i position);
    void draw(sf::RenderWindow &window);


private:
    int questionNumber;
    int maxNumQs;
    int questionFontSize;
    int answerFontSize;
    sf::Vector2f questionPos;
    sf::Vector2f answerPos;

    //bool questionResponse;
    bool leftAnswer;
    bool rightAnswer;
    bool next;

    std::string correctTemp;
    std::string incorrectTemp;

    sf::Event event;

    sf::Texture game1Texture;
    sf::Sprite game1Sprite;
    sf::Texture game1WinTexture;
    sf::Sprite game1WinSprite;
    sf::Texture game1LoseTexture;
    sf::Sprite game1LoseSprite;

    sf::Font font;
    sf::Text question;

    sf::Vector2i m_position;

    std::vector<Game1Question> questions;
};