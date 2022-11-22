#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

class Game {
private:
    sf::RenderWindow window;
    enum class m_GameState
    {
        Menu = 0, GameSelection, Options, Options_Level, MainGame, Game2, Paused
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

    // For Level Selection
    sf::Texture gameSelectTexture;
    sf::Sprite gameSelectSprite;
    sf::RectangleShape game1Select, game2Select;

    // For Options Settings
    sf::RectangleShape optionsL1, optionsL2, optionsL3, returnToMain, returnToOptionsMenu, changeLevel;
    sf::Text mainReturnText, optionsReturnText;

    // For Game 1
    uint32_t numCorrect{ 0 };
    uint32_t questionNum{ 0 };
    uint32_t difficultyLevel{ 1 };                          // Default difficulty is level 1
    float winCondition{ 0.75f };                            // Default win condition for level 1
    std::vector<m_Questions> questions;
    uint32_t charsPerLine{ 56 };                            // Default for difficult level 1
    sf::Texture game1StaticTexture, game1FallingTexture, winTexture, loseTexture, correctImageTexture, incorrectImageTexture, progressTexture, dropBoxTexture;
    sf::Sprite game1StaticSprite, game1FallingSprite, winSprite, loseSprite, correctImageSprite, incorrectImageSprite, progressSprite, dropBoxSprite;
    sf::Text game1QuestionText;
    sf::Vector2f answerPos {584.0f, 788.0f};        // Default for difficult level 1
    sf::Vector2f leftPos {576.f, 456.f};            // Start position for left sprite
    sf::Vector2f rightPos {1088.f, 456.f};          // Start position for right sprite



    // Sounds
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound;
    sf::SoundBuffer correctSoundBuffer;
    sf::Sound correctSound;
    sf::SoundBuffer wrongSoundBuffer;
    sf::Sound wrongSound;
    sf::SoundBuffer winSoundBuffer;
    sf::Sound winSound;
    sf::SoundBuffer loseSoundBuffer;
    sf::Sound loseSound;
    sf::Music music;
    bool winLoseSoundHasPlayed = false;
    bool answerSoundHasPlayed = false;

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

    // Game 1 loading and helper functions
    void loadGame1Assets();
    void textWrapper(std::string& s);
    void updateProgressSprite();

    // Game 2 loading
    void loadGame2Assets();

    // Menus, options, and general settings
    void loadMenuAndOptionsAssets();
    void setOptionsMenu_mainMenuButton();
    void setOptionsMenu_optionsMenuButton();
    void setOptionsMenu_levelButtons();
    void loadSounds();

public:
    // Constructor
    Game()
    {
        window.create({ 1920, 1080 }, "Climate Stompers");
        state = m_GameState::Menu;
        loadSounds();
        loadGame1Assets();
        loadGame2Assets();
        loadMenuAndOptionsAssets();
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
