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
    uint32_t game2HighScore{ 0 };
    sf::Vector2i mousePosition;
    sf::Event event;
    sf::Font mainFont;
    sf::Texture pauseTexture, tutorial1Texture, tutorial2Texture, tutorial3Texture;
    sf::Sprite pauseSprite, tutorial1Sprite, tutorial2Sprite, tutorial3Sprite;
    sf::RectangleShape returnToMainButton, returnToOptionsButton, nextButton;

    // For Main Menu
    sf::Texture mainTexture;
    sf::Sprite mainSprite;
    sf::RectangleShape mainNewGameButton, mainLoadGameButton, mainOptionsButton;

    // For Level Selection
    sf::Texture gameSelectTexture;
    sf::Sprite gameSelectSprite;
    sf::RectangleShape game1Select, game2Select;

    // For Options Settings
    sf::RectangleShape optionsL1, optionsL2, optionsL3, changeLevel;
    sf::Text mainReturnText, optionsReturnText;                     // TEMP - REMOVE ONCE FINAL BACKGROUND ADDED

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
        bool recyclable { false };
        bool sorted { false };
        bool sortedCorrectly { false };
        sf::Texture sortableTexture;
        sf::Sprite sortableSprite;
    };
    std::vector<m_Sortables> toSort;
    bool tutorial2aWatched { false };
    bool tutorial2bWatched { false };
    bool clickHeld{ false };
    bool game2Finished { false };
    uint32_t game2AttemptNum { 1 };
    uint32_t game2MaxAttempts { 3 };
    uint32_t numSorted { 0 };
    uint32_t spriteMoving{ 0 };
    sf::Texture game2BackgroundTexture;
    sf::Sprite game2BackgroundSprite;
    sf::Text game2Prompt;
    sf::Vector2i clickPos;
    // Sun sprites
    sf::Texture game2Sun1Texture, game2Sun2Texture, game2Sun3Texture;
    sf::Sprite game2Sun1Sprite, game2Sun2Sprite, game2Sun3Sprite;
    // For setting locations for item boxes
    sf::RectangleShape game2StartSq1, game2StartSq2, game2StartSq3, game2StartSq4, game2StartSq5, game2StartSq6, game2StartSq7, game2StartSq8;
    sf::RectangleShape game2RecycleSq1, game2RecycleSq2, game2RecycleSq3, game2RecycleSq4;
    sf::RectangleShape game2TrashSq1, game2TrashSq2, game2TrashSq3, game2TrashSq4;
    // For setting locations of drag-and-drop areas to snap ino place
    sf::RectangleShape game2RecycleDragArea1, game2RecycleDragArea2, game2RecycleDragArea3, game2RecycleDragArea4;
    sf::RectangleShape game2TrashDragArea1, game2TrashDragArea2, game2TrashDragArea3, game2TrashDragArea4;
    // For marking which squares already have an object
    bool game2RecycleSq1Occupied { false };
    bool game2RecycleSq2Occupied { false };
    bool game2RecycleSq3Occupied { false };
    bool game2RecycleSq4Occupied { false };
    bool game2TrashSq1Occupied { false };
    bool game2TrashSq2Occupied { false };
    bool game2TrashSq3Occupied { false };
    bool game2TrashSq4Occupied { false };

    // Sounds
    bool winLoseSoundHasPlayed = false;
    bool answerSoundHasPlayed = false;
    sf::SoundBuffer clickSoundBuffer, correctSoundBuffer, wrongSoundBuffer, winSoundBuffer, loseSoundBuffer;
    sf::Sound clickSound, correctSound, wrongSound, winSound, loseSound;
    sf::Music music;

    // Hints
    uint32_t numWrong{ 0 }; // number of questions wrong (in a row)
    sf::CircleShape bubble;
    sf::CircleShape triangle;
    sf::Text hint;

private:
    // General Game Functions
    void eventHandler();
    void update();
    void draw();
    void loadSave();
    void updateSave();
    
    // Menus, options, and general settings
    void setGlobalButtons();
    void loadSounds();
    void loadMenuAndOptionsAssets();
    void setOptionsMenu_mainMenuButton();
    void setOptionsMenu_optionsMenuButton();
    void setOptionsMenu_levelButtons();
    void setWinLoseScreens();
    void displayHint();

    // Game 1 loading and helper functions
    void loadGame1Assets();
    void textWrapper(std::string& s);
    void updateProgressSprite();

    // Game 2 loading and helper functions
    void loadGame2Assets();
    void resetGame2Soft();
    void resetGame2Hard();

public:
    // Constructor
    Game()
    {
        loadSave();
        window.create({ 1920, 1080 }, "Climate Stompers");
        state = m_GameState::Menu;
        loadSounds();
        setGlobalButtons();
        loadMenuAndOptionsAssets();
        setWinLoseScreens();
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