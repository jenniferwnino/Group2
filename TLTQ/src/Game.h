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
        Menu = 0, Options, Options_Level, MainGame, Paused
    };

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

    m_GameState state;
    const uint32_t defaultFontSize{ 24 };
    const uint32_t charsPerLine{ 56 };                      // Set number of characters per line for text wrapping answers
    uint32_t numCorrect{ 0 };
    uint32_t questionNum{ 0 };
    uint32_t difficultyLevel{ 1 };                          // Default difficulty is level 1
    float winCondition{ 0.75f };                            // Default win condition for level 1
    std::vector<m_Questions> questions;

    sf::Texture mainTexture;
    sf::Sprite mainSprite;
    sf::Texture winTexture;
    sf::Sprite winSprite;
    sf::Texture loseTexture;
    sf::Sprite loseSprite;
    sf::Texture pauseTexture;
    sf::Sprite pauseSprite;
    sf::Texture correctImageTexture;
    sf::Sprite  correctImageSprite;
    sf::Texture incorrectImageTexture;
    sf::Sprite  incorrectImageSprite;
    sf::Texture progressTexture;
    sf::Sprite progressSprite;

    // For Options Settings
    sf::RectangleShape optionsL1, optionsL2, optionsL3, returnToMain, returnToOptionsMenu, changeLevel;
    sf::Text mainReturnText, optionsReturnText;


    sf::Event event;
    sf::Font mainFont;
    sf::Vector2i mousePosition;
    sf::Vector2f textPos {584.0f, 788.0f};
    sf::Vector2f leftPos {576.f, 456.f};               // Start position for left sprite
    sf::Vector2f rightPos {1088.f, 456.f};            // Start position for right sprite

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

private:
    void eventHandler();
    void update();
    void draw();
    void loadQuestions();
    void textWrapper(std::string& s);
    void updateProgressSprite();
    void setOptionsMenu_mainMenuButton();
    void setOptionsMenu_optionsMenuButton();
    void loadSounds();

public:
    // Constructor
    Game()
    {
        window.create({ 1920, 1080 }, "Climate Stompers");
        state = m_GameState::Menu;
        loadQuestions();
        loadSounds();
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
