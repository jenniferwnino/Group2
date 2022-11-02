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
        bool answered;
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
    int numCorrect;
    int questionNumber;
    float winCondition;

    bool leftAnswer;
    bool rightAnswer;
    bool next;

    int questionFontSize;
    int answerFontSize;
    sf::Vector2f questionPos;
    sf::Vector2f answerPos;
    sf::Font font;
    sf::Text question;

    std::string correctTemp;
    std::string incorrectTemp;

    sf::Texture game1Texture;
    sf::Sprite game1Sprite;
    sf::Texture game1WinTexture;
    sf::Sprite game1WinSprite;
    sf::Texture game1LoseTexture;
    sf::Sprite game1LoseSprite;

    std::vector<Game1Question> questions;

    // Private functions
    void correctResponse(sf::RenderWindow &window, Game1Question& question, int& numCorrect);
    void incorrectResponse(sf::RenderWindow &window, Game1Question& question);
};