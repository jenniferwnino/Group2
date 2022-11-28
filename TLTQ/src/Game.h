#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

class Game {
private:
    // General Game Variables
    sf::RenderWindow window;
    enum class m_GameState
    {
        Menu = 0, GameSelection, Options, Options_Level, MainGame, Game2, Paused
    };
    m_GameState state;
    m_GameState returnTo{ m_GameState::Menu };
    const uint32_t defaultFontSize{ 24 };
    uint32_t UID{ 0 };
    uint32_t game1Score{ 0 };
    uint32_t game2Score{ 0 };
    sf::Vector2i mousePosition;
    sf::Event event;
    sf::Font mainFont;
    sf::Texture pauseTexture, tutorial1Texture, tutorial2Texture, tutorial3Texture;
    sf::Sprite pauseSprite, tutorial1Sprite, tutorial2Sprite, tutorial3Sprite;
    sf::RectangleShape returnToMain, nextButton;

    // For Main Menu
    sf::Texture mainTexture;
    sf::Sprite mainSprite;

    // For Level Selection
    sf::Texture gameSelectTexture;
    sf::Sprite gameSelectSprite;
    sf::RectangleShape game1Select, game2Select;

    // For Options Settings
    sf::RectangleShape optionsL1, optionsL2, optionsL3, returnToOptionsMenu, changeLevel;
    sf::Text mainReturnText, optionsReturnText;

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
    std::vector<m_Questions> questions;
    bool tutorial1aWatched { false };
    bool tutorial1bWatched { false };
    uint32_t numCorrect{ 0 };
    uint32_t questionNum{ 0 };
    uint32_t difficultyLevel{ 1 };                          // Default difficulty is level 1
    float winCondition{ 0.75f };                            // Default win condition for level 1
    uint32_t charsPerLine{ 56 };                            // Default for difficult level 1
    sf::Texture game1StaticTexture, game1FallingTexture, winTexture, loseTexture, correctImageTexture, incorrectImageTexture, progressTexture, dropBoxTexture;
    sf::Sprite game1StaticSprite, game1FallingSprite, winSprite, loseSprite, correctImageSprite, incorrectImageSprite, progressSprite, dropBoxSprite;
    sf::Text game1QuestionText;
    sf::RectangleShape winLoseMenuButton, winLosePlayAgainButton;
    sf::Vector2f answerPos {584.0f, 788.0f};        // Default for difficult level 1
    sf::Vector2f leftPos {576.f, 456.f};               // Start position for left sprite
    sf::Vector2f rightPos {1088.f, 456.f};            // Start position for right sprite

    // For Game 2
    struct m_Sortables
    {
        sf::Vector2f unsortPos {};
        sf::Vector2f sortPos {};
        bool recyclable { false };
        bool sorted { false };
        sf::RectangleShape tempShape;
    };
    std::vector<m_Sortables> toSort;
    bool tutorial2aWatched { false };
    bool tutorial2bWatched { false };
    bool clickHeld{ false };
    int spriteMoving{ 0 };
    sf::Texture game2BackgroundTexture, recycleTexture, trashTexture;
    sf::Sprite game2BackgroundSprite, recycleSprite, trashSprite;
    sf::RectangleShape trash1, trash2, trash3, trash4, recycle1, recycle2, recycle3, recycle4;      // temp
    sf::Vector2i clickPos;

    // Sounds
    bool winLoseSoundHasPlayed = false;
    bool answerSoundHasPlayed = false;
    sf::SoundBuffer clickSoundBuffer, correctSoundBuffer, wrongSoundBuffer, winSoundBuffer, loseSoundBuffer;
    sf::Sound clickSound, correctSound, wrongSound, winSound, loseSound;
    sf::Music music;

private:
    // General Game Functions
    void eventHandler();
    void update();
    void draw();
    void loadSave();
    void updateSave();

    // Menus, options, and general settings functions
    void setMenuAndNextButtons();
    void loadMenuAndOptionsAssets();
    void setOptionsMenu_optionsMenuButton();
    void setOptionsMenu_levelButtons();
    void loadSounds();

    // Game 1 loading and helper functions
    void loadGame1Assets();
    void textWrapper(std::string& s);
    void updateProgressSprite();

    // Game 2 loading functions
    void loadGame2Assets();

public:
    // Constructor
    Game()
    {
        loadSave();
        window.create({ 1920, 1080 }, "Climate Stompers");
        state = m_GameState::Menu;
        loadSounds();
        setMenuAndNextButtons();
        loadMenuAndOptionsAssets();
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
    ~Game()
    {
        updateSave();
    }
};