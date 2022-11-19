#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    enum class m_GameState
    {
        Menu = 0, Options, Options_Level, MainGame, Game2, Paused
    };

    // For Game 1
    struct m_Questions
    {
        const std::string correctText{};
        const std::string incorrectText{};
        std::string correctImage{};
        std::string incorrectImage{};
        bool answered{ false };
        bool answeredCorrect{ false };
        const bool leftIsCorrect{ false };
    };

    // For Game 2
    struct m_Sortables
    {
        sf::Vector2f unsortPos {};
        sf::Vector2f sortPos {};
        bool recyclable { false };
        bool sorted { false };
        sf::RectangleShape tempShape;
    };

    // General Game Variables
    m_GameState state;
    const uint32_t defaultFontSize{ 24 };
    sf::Vector2i mousePosition;
    sf::Event event;
    sf::Font mainFont;
    sf::Texture pauseTexture;
    sf::Sprite pauseSprite;

    // For Main Menu
    sf::Texture mainTexture;
    sf::Sprite mainSprite;

    // For Options Settings
    sf::RectangleShape optionsL1, optionsL2, optionsL3, returnToMain, returnToOptionsMenu, changeLevel;
    sf::Text mainReturnText, optionsReturnText;

    // For Game 1
    uint32_t numCorrect{ 0 };
    uint32_t questionNum{ 0 };
    uint32_t difficultyLevel{ 1 };                          // Default difficulty is level 1
    float winCondition{ 0.75f };                            // Default win condition for level 1
    std::vector<m_Questions> questions;
    const uint32_t charsPerLine{ 56 };                      // Set number of characters per line for text wrapping answers
    sf::Texture winTexture, loseTexture, correctImageTexture, incorrectImageTexture, progressTexture;
    sf::Sprite winSprite, loseSprite, correctImageSprite, incorrectImageSprite, progressSprite;
    sf::Vector2f textPos {584.0f, 788.0f};
    sf::Vector2f leftPos {576.f, 456.f};               // Start position for left sprite
    sf::Vector2f rightPos {1088.f, 456.f};            // Start position for right sprite

    // For Game 2
    std::vector<m_Sortables> toSort;
    sf::Texture game2BackgroudTexture, recycleTexture, trashTexture;
    sf::Sprite game2BackgroundSprite, recycleSprite, trashSprite;
    sf::RectangleShape trash1, trash2, trash3, trash4, recycle1, recycle2, recycle3, recycle4;      // temp
    sf::Vector2i clickPos;
    bool clickHeld;
    int spriteMoving;

private:
    void eventHandler();
    void update();
    void draw();
    void loadGame1Assets();
    void textWrapper(std::string& s);                       // Helper function for loadGame1Assets()
    void updateProgressSprite();
    void loadGame2Assets();
    void setOptionsMenu_mainMenuButton();
    void setOptionsMenu_optionsMenuButton();

public:
    // Constructor
    Game()
    {
        window.create({ 1920, 1080 }, "Climate Stompers");
        state = m_GameState::Menu;
        loadGame1Assets();
        loadGame2Assets();
    }
    void run()
    {
        while(window.isOpen())
        {
            eventHandler();
            update();
            draw();
        }
    }
};
