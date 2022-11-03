#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    enum class m_GameState
    {
        Menu = 0, MainGame, Paused
    };

    struct m_Questions
    {
        const std::string correctText{};
        const std::string incorrectText{};
        bool answered{ false };
        bool answeredCorrect{ false };
        const bool leftIsCorrect{ false };
    };

    m_GameState state;
    const uint32_t defaultFontSize = 24;
    uint32_t numCorrect{ 0 };
    uint32_t questionNum{ 0 };
    std::vector<m_Questions> questions;

    sf::Texture mainTexture;
    sf::Sprite mainSprite;
    sf::Font mainFont;
    sf::Vector2i mousePosition;

private:
    void eventHandler();
    void update();
    void draw();



public:
    // Constructor
    Game()
    {
        window.create({ 1920, 1080 }, "Climate Stompers");
        state = m_GameState::Menu;
    }
    void run()
    {
        while (window.isOpen())
        {
            eventHandler();
            update();
            draw();
        }
    }
};


