#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Game::draw()
{
	window.clear();
	if (state == m_GameState::Menu)
	{
		window.draw(mainSprite);
	}
    else if (state == m_GameState::GameSelection)
    {
        // TEMP VERSION OF GAME SELECTIONS SCREEN - NEED FINAL BACKGROUND
        window.draw(gameSelectSprite);
        window.draw(returnToMainButton);
        window.draw(mainReturnText);
        window.draw(returnToOptionsButton);
        window.draw(optionsReturnText);
        window.draw(game1Select);
        window.draw(game2Select);
    }
	else if (state == m_GameState::Options)
    {
        // TEMP FOR OPTIONS - NEED A NICER SCREEN DESIGN
        // CODE WILL CHANGE WITH NEW SCREEN DESIGN
        window.draw(returnToMainButton);
        window.draw(mainReturnText);
        window.draw(changeLevel);

        // Temp text - will be written in final background (?)
        sf::Text selectLevelText ("Change difficulty level", mainFont, 48U);
        selectLevelText.setFillColor(sf::Color::White);
        selectLevelText.setPosition(680.f, 545.f);
        window.draw(selectLevelText);
    }
    else if (state == m_GameState::Options_Level)
    {
        // TEMP FOR SETTING LEVEL - NEED A NICER SCREEN DESIGN
        // CODE WILL CHANGE WITH NEW SCREEN DESIGN
        window.draw(returnToMainButton);
        window.draw(mainReturnText);
        window.draw(returnToOptionsButton);
        window.draw(optionsReturnText);

        // Selected difficulty level shows blue, other levels show orange
        if (difficultyLevel == 1)
        {
            optionsL1.setFillColor(sf::Color::Blue);
            optionsL2.setFillColor(sf::Color(255, 128, 0, 255));
            optionsL3.setFillColor(sf::Color(255, 128, 0, 255));
        }
        else if (difficultyLevel == 2)
        {
            optionsL1.setFillColor(sf::Color(255, 128, 0, 255));
            optionsL2.setFillColor(sf::Color::Blue);
            optionsL3.setFillColor(sf::Color(255, 128, 0, 255));
        }
        else if (difficultyLevel == 3)
        {
            optionsL1.setFillColor(sf::Color(255, 128, 0, 255));
            optionsL2.setFillColor(sf::Color(255, 128, 0, 255));
            optionsL3.setFillColor(sf::Color::Blue);
        }

        // Draw the three level rectangles
        window.draw(optionsL1);
        window.draw(optionsL2);
        window.draw(optionsL3);

        // Temp text - will be written in final background (?)
        sf::Text level1Text ("Level 1", mainFont, 48U);
        level1Text.setFillColor(sf::Color::White);
        level1Text.setPosition(420.f, 420.f);
        window.draw(level1Text);
        sf::Text level2Text ("Level 2", mainFont, 48U);
        level2Text.setFillColor(sf::Color::White);
        level2Text.setPosition(820.f, 420.f);
        window.draw(level2Text);
        sf::Text level3Text ("Level 3", mainFont, 48U);
        level3Text.setFillColor(sf::Color::White);
        level3Text.setPosition(1220.f, 420.f);
        window.draw(level3Text);
    }
    else if (state == m_GameState::MainGame)
	{
        // Show the tutorials if it has not been viewed yet
        if (!tutorial1aWatched)
        {
            window.draw(nextButton);                            // Draw first so hidden
            window.draw(tutorial1Sprite);
        }
        else if (!tutorial1bWatched)
        {
            window.draw(nextButton);                            // Draw first so hidden
            window.draw(tutorial2Sprite);
        }
        // Show the game if the tutorial has been viewed
        else
        {
            // If all questions haven't been answered, show the next question
            if (questionNum < questions.size())
            {
                // Set correct background depending on difficulty level
                if (difficultyLevel == 1)
                {
                    window.draw(game1StaticSprite);
                }
                else
                {
                    window.draw(game1FallingSprite);
                }

                // Load correct & incorrect answer text
                sf::Text correctAnswer(questions[questionNum].correctText, mainFont, defaultFontSize);
                correctAnswer.setPosition(answerPos);
                correctAnswer.setFillColor(sf::Color::White);
                sf::Text incorrectAnswer(questions[questionNum].incorrectText, mainFont, defaultFontSize);
                incorrectAnswer.setPosition(answerPos);
                incorrectAnswer.setFillColor(sf::Color::White);

                // Load correct & incorrect answer sprites
                correctImageTexture.loadFromFile(questions[questionNum].correctImage);
                correctImageSprite.setTexture(correctImageTexture);
                correctImageSprite.setScale(4.0f, 4.0f);
                incorrectImageTexture.loadFromFile(questions[questionNum].incorrectImage);
                incorrectImageSprite.setTexture(incorrectImageTexture);
                incorrectImageSprite.setScale(4.0f, 4.0f);

                // Set correct & incorrect answer sprite locations
                if (questions[questionNum].leftIsCorrect)
                {
                    correctImageSprite.setPosition(leftPos);
                    incorrectImageSprite.setPosition(rightPos);
                }
                else
                {
                    correctImageSprite.setPosition(rightPos);
                    incorrectImageSprite.setPosition(leftPos);
                }

                // Draw correct & incorrect answer sprites
                window.draw(correctImageSprite);
                window.draw(incorrectImageSprite);

                // For falling sprites, need layer for sprites to drop behind
                if (difficultyLevel != 1)
                {
                    window.draw(dropBoxSprite);
                }

                // Add question text on top of background layers
                window.draw(game1QuestionText);

                // For first question, start with sun sprite 4
                if (questionNum == 0 && numCorrect == 0)
                {
                    progressTexture.loadFromFile("./graphics/sunSprite4of7.png");
                    progressSprite.setTexture(progressTexture);
                    progressSprite.setPosition(1512.5f, 15.5f);
                    progressSprite.setScale(4.0f, 4.05f);
                    window.draw(progressSprite);
                }

                // Question answered correctly - Show correct answer text & update sun sprite
                if (questions[questionNum].answered && questions[questionNum].answeredCorrect)
                {
                    window.draw(correctAnswer);
                    updateProgressSprite();
                }

                // Question answered incorrectly - Show incorrect answer text & update sun sprite
                else if (questions[questionNum].answered && !questions[questionNum].answeredCorrect)
                {
                    window.draw(incorrectAnswer);
                    updateProgressSprite();
                }

                window.draw(progressSprite);

            }
            // If all questions answered - display win or lose screen based on score
            else
            {
                // Game won
                if (numCorrect >= (questions.size()  * winCondition))
                {
                    winTexture.loadFromFile("./graphics/winScreen.png");
                    winSprite.setTexture(winTexture);
                    winSprite.setScale(4.0f, 4.0f);
                    window.draw(winSprite);
                    if (!winLoseSoundHasPlayed)
                    {
                        winLoseSoundHasPlayed = true;
                        winSound.play();
                    }
                }
                // Game lost
                else
                {
                    loseTexture.loadFromFile("./graphics/loseScreen.png");
                    loseSprite.setTexture(loseTexture);
                    loseSprite.setScale(4.0f, 4.0f);
                    window.draw(loseSprite);
                    if (!winLoseSoundHasPlayed)
                    {
                        winLoseSoundHasPlayed = true;
                        loseSound.play();
                    }
                }
            }
        }
	}
    else if (state == m_GameState::Game2)
    {
        // Show the tutorials if it has not been viewed yet
        if (!tutorial2aWatched)
        {
            window.draw(tutorial3Sprite);
        }
        else if (!tutorial2bWatched)
        {
            window.draw(tutorial2Sprite);
        }
        // Show the game if tutorials have been watched
        else {
            window.draw(game2BackgroundSprite);
            window.draw(returnToMainButton);
            window.draw(mainReturnText);

            window.draw(recycleSprite);
            window.draw(trashSprite);

            // Draw the temp shapes to sort
            for (int i = 0; i < 8; i++) {
                window.draw(toSort[i].tempShape);
            }
        }
    }
	else if (state == m_GameState::Paused)
	{
        pauseTexture.loadFromFile("./graphics/pauseScreen.png");
        pauseSprite.setTexture(pauseTexture);
        pauseSprite.setScale(4.0f, 4.0f);
        window.draw(pauseSprite);
	}
	window.display();
}

void Game::loadSave()
{
    std::ifstream file;
    file.open("save.dat", std::ios_base::in);

    std::string temp;
    if (file.is_open())
    {
        std::getline(file, temp);
        UID = std::stoi(temp);
        std::getline(file, temp);
        game1Score = std::stoi(temp);
        std::getline(file, temp);
        game2Score = std::stoi(temp);
    }

    file.close();
}

void Game::updateSave()
{
    std::ofstream oStream;
    oStream.open("save.dat", std::ios_base::out | std::ios_base::trunc);
    oStream << UID << "\n"
            << game1Score << "\n"
            << game2Score;
    oStream.close();
}

void Game::update()
{
	if (state == m_GameState::Menu)
	{
        // New Game button is clicked
       if (mainNewGameButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
       {
           state = m_GameState::GameSelection;
       }
       // Load Game button is clicked
       if (mainLoadGameButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
       {
          // This will simply resume the previous game for now since we do not have multiple games
           state = m_GameState::MainGame;
       } 
       // Options button is clicked
       if (mainOptionsButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
       {
           state = m_GameState::Options;
       }
	}
    else if (state == m_GameState::GameSelection)
    {
        // Clicked menu
        if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Menu;
        }

        // Clicked options
        else if (returnToOptionsButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Options;
        }

        // Clicked game 1
        else if (game1Select.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            // Reset all game 1 settings and launch
            state = m_GameState::MainGame;
            questionNum = 0;
            numCorrect = 0;
            winLoseSoundHasPlayed = false;
            for (int i = 0; i < questions.size(); i++)
            {
                questions[i].answered = false;
                questions[i].answeredCorrect = false;
            }
        }

        // Clicked game 2
        else if (game2Select.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            // Reset all game 2 settings and launch
            state = m_GameState::Game2;
        }
    }
    else if (state == m_GameState::Options)
    {
        if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Menu;
        }
        else if (changeLevel.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Options_Level;
        }
    }
    else if (state == m_GameState::Options_Level)
    {
        if (optionsL1.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            difficultyLevel = 1;

            // CHANGES FOR GAME 1 SETTINGS
            charsPerLine = 56;
            winCondition = 0.75f;
            answerPos = sf::Vector2f (584.f, 788.f);
            leftPos.y = 456.f;
            rightPos.y = 456.f;
            // Reload game 1 assets to ensure text wrapping is correct
            questions.clear();
            loadGame1Assets();

            // CHANGES FOR GAME 2 SETTINGS
            // TO BE COMPLETED
        }
        else if (optionsL2.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            difficultyLevel = 2;

            // CHANGES FOR GAME 1 SETTINGS
            charsPerLine = 105;
            winCondition = 0.80f;
            answerPos = sf::Vector2f (307.f, 918.f);
            leftPos.y = 0.f;
            rightPos.y = 0.f;
            // Reload game 1 assets to ensure text wrapping is correct
            questions.clear();
            loadGame1Assets();

            // CHANGES FOR GAME 2 SETTINGS
            // TO BE COMPLETED
        }
        else if (optionsL3.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            difficultyLevel = 3;

            // CHANGES FOR GAME 1 SETTINGS
            charsPerLine = 105;
            winCondition = 0.85f;
            leftPos.y = 0.f;
            rightPos.y = 0.f;
            // Reload game 1 assets to ensure text wrapping is correct
            questions.clear();
            loadGame1Assets();

            // CHANGES FOR GAME 2 SETTINGS
            // TO BE COMPLETED
        }
        else if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Menu;
        }
        else if (returnToOptionsButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Options;
        }
    }
	else if (state == m_GameState::MainGame)
	{
        // On tutorial 1a screen
        if (!tutorial1aWatched)
        {
            // Menu button is clicked
            if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                state = m_GameState::Menu;
            }
            // Next button is clicked
            if (nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                tutorial1aWatched = true;
                mousePosition = sf::Vector2i (0, 0);
            }
        }

        // On tutorial 1b screen
        else if (!tutorial1bWatched)
        {
            // Menu button is clicked
            if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                state = m_GameState::Menu;
            }
            // Next button is clicked
            if (nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                tutorial1bWatched = true;
                mousePosition = sf::Vector2i (0, 0);
            }
        }

        // On Game screen
        else {
            // All questions haven't been answered - inGame or inGameFallingSprites is displayed
            if (questionNum < questions.size()) {
                // Correct sprite clicked and question not already answered
                if (correctImageSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && !questions[questionNum].answered)
                {
                    questions[questionNum].answered = true;
                    numCorrect++;
                    questions[questionNum].answeredCorrect = true;
                    if (!answerSoundHasPlayed)
                        correctSound.play();
                }
                // Incorrect sprite clicked and question not already answered
                else if (incorrectImageSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && !questions[questionNum].answered)
                {
                    questions[questionNum].answered = true;
                    questions[questionNum].answeredCorrect = false;
                    if (!answerSoundHasPlayed)
                        wrongSound.play();
                }
                // Menu button is clicked
                else if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                {
                    state = m_GameState::Menu;
                }
                // Next button clicked and question already answered
                else if (nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && questions[questionNum].answered)
                {
                    ++questionNum;
                    answerSoundHasPlayed = false;
                }

                // If difficultyLevel 2 or 3, move the sprites
                if (difficultyLevel == 2 || difficultyLevel == 3)
                {
                    // If question not answered, move the sprites
                    if (!questions[questionNum].answered)
                    {
                        // If sprite is still on the screen
                        if (leftPos.y < dropBoxSprite.getPosition().y)
                        {
                            if (difficultyLevel == 2)
                            {

                                leftPos.y += 0.25;
                                rightPos.y += 0.25;
                            }
                            if (difficultyLevel == 3)
                            {
                                leftPos.y += 0.75;
                                rightPos.y += 0.75;
                            }
                        }
                        // If sprite went off the screen, mark question as incorrect answer
                        else
                        {
                            questions[questionNum].answered = true;
                            questions[questionNum].answeredCorrect = false;
                        }
                    }
                    // Reset positions once question is answered
                    else
                    {
                        leftPos.y = 0.f;
                        rightPos.y = 0.f;
                    }
                }
            }

            // All questions have been answered - winScreen or loseScreen is displayed
            else
            {
                // Home button clicked
                if (winLoseMenuButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                {
                    state = m_GameState::Menu;
                }
                // Play again button clicked
                else if (winLosePlayAgainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                {
                    state = m_GameState::MainGame;
                    questionNum = 0;
                    numCorrect = 0;
                    winLoseSoundHasPlayed = false;
                    for (int i = 0; i < questions.size(); i++)
                    {
                        questions[i].answered = false;
                        questions[i].answeredCorrect = false;
                    }
                }
            }
        }
	}
    else if (state == m_GameState::Game2)
    {
        // On tutorial 2a screen
        if (!tutorial2aWatched)
        {
            if (nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                tutorial2aWatched = true;
                mousePosition = sf::Vector2i (0, 0);
            }
        }
        // On tutorial 2b screen
        else if (!tutorial2bWatched)
        {
            if (nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                tutorial2bWatched = true;
                mousePosition = sf::Vector2i (0, 0);
            }
        }

        // In Game
        else {
            if (clickHeld) {
                toSort[spriteMoving].tempShape.setPosition(mousePosition.x, mousePosition.y);
            }
                // Clicked menu
            else if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
                state = m_GameState::Menu;
            }
        }
    }
	else if (state == m_GameState::Paused)
	{
        // To be updated later if necessary
	}

    // Reset mouse position to avoid overlapping elements.
    // Don't do on Game2 as it messes up drag & drop
    if (state != m_GameState::Game2){
        mousePosition.x = 0;
        mousePosition.y = 0;
    }
}

void Game::eventHandler()
{
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
        // Game 2 specific for drag & drop selection
        else if (state == m_GameState::Game2 && !clickHeld && event.type == sf::Event::MouseButtonPressed)
        {
            clickHeld = true;
            clickPos = sf::Mouse::getPosition(window);

            // Mark the correct sprite as moving
            for (int i = 0; i < toSort.size(); i++)
            {
                if (toSort[i].tempShape.getGlobalBounds().contains(sf::Vector2f(clickPos)))
                {
                    spriteMoving = i;
                }
            }
        }
        // Record mouse position when click is released
        else if (event.type == sf::Event::MouseButtonReleased)
		{
			mousePosition = sf::Mouse::getPosition(window);
            clickSound.play();

            if (clickHeld)
            {
                clickHeld = false;
            }
		}
        // Game 2 specific for drag & drop selection
        else if (clickHeld)
        {
            mousePosition = sf::Mouse::getPosition(window);
        }
        // Keyboard commands
        else if (event.type == sf::Event::KeyPressed)
        {
            // Pressing space bar controls the pause screen - Only works in games
            if (event.key.code == sf::Keyboard::Space && (state == m_GameState::MainGame || state == m_GameState::Paused || state == m_GameState::Game2))
            {
                if (state != m_GameState::Paused) {
                    returnTo = state;
                    state = m_GameState::Paused;
                }
                else
                {
                    state = returnTo;
                    //state = m_GameState::MainGame;      // Will need to change how this works if more than 1 game
                }
            }
            // Pressing escape key closes window
            else if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }
	}
}

void Game::loadMenuAndOptionsAssets()
{
    // Set mainFont
    mainFont.loadFromFile("./fonts/Square.ttf");

    // Load main menu background
    mainTexture.loadFromFile("./graphics/mainMenu.png");
    mainSprite.setTexture(mainTexture);
    mainSprite.setScale(4.0f, 4.0f);

    // Set main menu buttons
    mainNewGameButton.setPosition(30, 25);
    mainNewGameButton.setSize(sf::Vector2f(395.f, 85.f));
    mainLoadGameButton.setPosition(30.f, 130.f);
    mainLoadGameButton.setSize(sf::Vector2f (395.f, 85.f));
    mainOptionsButton.setPosition(30.f, 250.f);
    mainOptionsButton.setSize(sf::Vector2f (395.f, 85.f));

    // Set game selection screen assets
    gameSelectTexture.loadFromFile("./graphics/gameSelection.png");
    gameSelectSprite.setTexture(gameSelectTexture);
    gameSelectSprite.setScale(4.0f, 4.0f);
    game1Select.setSize(sf::Vector2f(256.f, 256.f));
    game1Select.setPosition(400, 400);
    game1Select.setFillColor(sf::Color(255, 128, 0, 255));
    game2Select.setSize(sf::Vector2f(256.f, 256.f));
    game2Select.setPosition(1250, 400);
    game2Select.setFillColor(sf::Color(255, 128, 0, 255));

    // For options menu - change level button
    changeLevel.setSize(sf::Vector2f(800.f, 150.f));
    changeLevel.setFillColor(sf::Color(255, 128, 0, 255));
    changeLevel.setPosition(550.f, 500.f);

    // Create options menu level buttons
    optionsL1.setSize(sf::Vector2f(256.f, 256.f));
    optionsL1.setPosition(400, 400);
    optionsL2.setSize(sf::Vector2f(256.f, 256.f));
    optionsL2.setPosition(800, 400);
    optionsL3.setSize(sf::Vector2f(256.f, 256.f));
    optionsL3.setPosition(1200, 400);

    // Load tutorial sprites
    tutorial1Texture.loadFromFile("./graphics/tutorial1.png");
    tutorial1Sprite.setTexture(tutorial1Texture);
    tutorial1Sprite.setScale(4.f, 4.f);
    tutorial2Texture.loadFromFile("./graphics/tutorial2.png");
    tutorial2Sprite.setTexture(tutorial2Texture);
    tutorial2Sprite.setScale(4.f, 4.f);
    tutorial3Texture.loadFromFile("./graphics/tutorial3.png");
    tutorial3Sprite.setTexture(tutorial3Texture);
    tutorial3Sprite.setScale(4.f, 4.f);
}

void Game::loadGame1Assets() {
    // Load backgrounds
    game1StaticTexture.loadFromFile("./graphics/inGame.png");
    game1StaticSprite.setTexture(game1StaticTexture);
    game1StaticSprite.setScale(4.0f, 4.0f);
    game1FallingTexture.loadFromFile("./graphics/inGameFallingSprites.png");
    game1FallingSprite.setTexture(game1FallingTexture);
    game1FallingSprite.setScale(4.0f, 4.0f);

    // Load main question text
    mainFont.loadFromFile("./fonts/Square.ttf");
    if (difficultyLevel == 1)
    {
        game1QuestionText.setString("Choose the option that is best for the \nenvironment!");
        game1QuestionText.setPosition(600.0f, 185.0f);
    }
    else if (difficultyLevel == 2 || difficultyLevel == 3)
    {
        game1QuestionText.setString("Choose the option that is best for the environment!");
        game1QuestionText.setPosition(520.0f, 765.0f);
    }
    game1QuestionText.setFont(mainFont);
    game1QuestionText.setCharacterSize(36U);
    game1QuestionText.setFillColor(sf::Color::White);

    // Make dropBox rectangle for level 2 & 3 difficulty
    dropBoxTexture.loadFromFile("./graphics/dropBox.png");
    dropBoxSprite.setTexture(dropBoxTexture);
    dropBoxSprite.setScale(4.f, 4.f);
    dropBoxSprite.setPosition(sf::Vector2f(252, 680));

    // Create menu button seen on win/lose screen
    winLoseMenuButton.setPosition(757, 749);
    winLoseMenuButton.setSize(sf::Vector2f(405, 90));

    // Create play again button seen on win/lose screen
    winLosePlayAgainButton.setPosition(755, 580);
    winLosePlayAgainButton.setSize(sf::Vector2f(405, 145));

    // Read the .csv file
    std::ifstream infile("./csv_files/game1input.csv");
    if (infile.is_open())
    {
        // Create temp variables for reading .csv file
        std::string dataLine, correctTemp, incorrectTemp, temp, correctImage, incorrectImage;
        bool l = false;

        // Throw out the first line with the headers
        getline(infile, dataLine);

        // Get question values
        while (getline(infile, dataLine))
        {
            std::istringstream stream(dataLine);

            // Break up line
            getline(stream, correctTemp, ',');
            getline(stream, incorrectTemp, ',');
            getline(stream, temp, ',');
            if (stoi(temp) == 1)
            {
                l = true;
            }
            getline(stream, correctImage, ',');
            getline(stream, incorrectImage, '\r');

            // Wrap answer text
            textWrapper(correctTemp);
            textWrapper(incorrectTemp);

            // Create question
            questions.emplace_back(m_Questions{ correctTemp, incorrectTemp, correctImage, incorrectImage, false, false, l});
        }
    }
}

void Game::textWrapper(std::string& s){
    std::string nextWord, currentLine, wrappedString;
    for (int i = 0; i < s.length(); i++)
    {
        nextWord += (s.at(i));
        // If it is a space (ASCII space = 32)
        if (s.at(i) == 32)
        {
            // If the next word will fit on the current line...
            if ((currentLine.length() + nextWord.length())<= charsPerLine)
            {
                // Add nextWord to currentLine & reset next word
                currentLine += nextWord;
                nextWord = "";
            }
            // If next word won't fit on the current line...
            else
            {
                // End current line and add to wrappedString
                currentLine += "\n";
                wrappedString += currentLine;
                // reset currentLine to nextWord & reset nextWord
                currentLine = nextWord;
                nextWord = "";
            }
        }
    }
    // Add remaining currentLine to the wrappedString
    currentLine += nextWord;
    wrappedString += currentLine;
    // Update input string reference
    s = wrappedString;
}

void Game::loadGame2Assets() {
    // Background
    game2BackgroundTexture.loadFromFile("./graphics/game2Screen.png");
    game2BackgroundSprite.setTexture(game2BackgroundTexture);
    game2BackgroundSprite.setScale(4.0f, 4.0f);

    // Add sprites
    recycleTexture.loadFromFile("./graphics/recyclingBin.png");
    recycleSprite.setTexture(recycleTexture);
    recycleSprite.setScale(4.0f, 4.0f);
    recycleSprite.setPosition(175.f, 150.f);
    trashTexture.loadFromFile("./graphics/trashCan.png");
    trashSprite.setTexture(trashTexture);
    trashSprite.setScale(4.0f, 4.0f);
    trashSprite.setPosition(1475.f, 150.f);

    // This whole section is a bit of a hot mess for the temp setup
    for (int i = 0; i < 8; i++)
    {
        toSort.emplace_back(m_Sortables());
        toSort[i].tempShape.setSize(sf::Vector2f(128.f, 128.f));
    }
    for (int i = 0; i < 4; i++)
    {
        toSort[i].tempShape.setFillColor(sf::Color::Red);
    }
    for (int i = 4; i < 8; i++)
    {
        toSort[i].recyclable = true;
        toSort[i].tempShape.setFillColor(sf::Color::Green);
    }
    float tempX = 700;
    for (int i = 0; i < 3; i++) {
        toSort[i].unsortPos.x = tempX;
        toSort[i].unsortPos.y = 150.f;
        tempX += 200;
    }
    tempX = 700;
    for (int i = 3; i < 6; i++)
    {
        toSort[i].unsortPos.x = tempX;
        toSort[i].unsortPos.y = 350.f;
        tempX += 200;
    }
    tempX = 700;
    for (int i = 6; i < 8; i++)
    {
        toSort[i].unsortPos.x = tempX;
        toSort[i].unsortPos.y = 550.f;
        tempX += 200;
    }
    for (int i = 0; i < 8; i++)
    {
        toSort[i].tempShape.setPosition(toSort[i].unsortPos);
    }
}

void Game::updateProgressSprite()
{
    std::string texturePath{ "./graphics/" };
    float percentCorrect{ (static_cast<float>(numCorrect) / (questionNum + 1)) };

    if (percentCorrect < 0.15f)
    {
        texturePath.append("sunSprite1of7.png");
    }
    else if (0.15f <= percentCorrect < 0.30f)
    {
        texturePath.append("sunSprite2of7.png");
    }
    else if (0.30f <= percentCorrect < 0.45f)
    {
        texturePath.append("sunSprite3of7.png");
    }
    else if (0.45f <= percentCorrect < 0.60f)
    {
        texturePath.append("sunSprite4of7.png");
    }
    else if (0.60f <= percentCorrect < 0.75f)
    {
        texturePath.append("sunSprite5of7.png");
    }
    else if (0.75f <= percentCorrect < 0.90f)
    {
        texturePath.append("sunSprite6of7.png");
    }
    else
    {
        texturePath.append("sunSprite7of7.png");
    }

    progressTexture.loadFromFile(texturePath);
    progressSprite.setTexture(progressTexture);
    progressSprite.setPosition(1512.5f, 15.5f);
    progressSprite.setScale(4.0f, 4.05f);
    window.draw(progressSprite);
}

void Game::setGlobalButtons() {
    // Set up "Main" button rectangle
    returnToMainButton.setPosition(30, 25);
    returnToMainButton.setSize(sf::Vector2f(395.f, 85.f));
    returnToMainButton.setFillColor(sf::Color(255, 128, 0, 255));

    // TEMPORARY TEXT - REMOVE ONCE OPTIONS MENU BACKGROUND CREATED
    mainReturnText.setString("Menu");
    mainReturnText.setFont(mainFont);
    mainReturnText.setCharacterSize(48U);
    mainReturnText.setFillColor(sf::Color::White);
    mainReturnText.setPosition(150.f, 40.f);

    // Set up "Next" button
    nextButton.setSize(sf::Vector2f (190.f, 75.f));
    nextButton.setPosition(1696.f, 978.f);
    nextButton.setFillColor(sf::Color(255, 128, 0, 255));

    // Set up "Options" button
    returnToOptionsButton.setPosition(30.f, 130.f);
    returnToOptionsButton.setSize(sf::Vector2f(395.f, 85.f));
    returnToOptionsButton.setFillColor(sf::Color(255, 128, 0, 255));

    // TEMPORARY TEXT - REMOVE ONCE OPTIONS MENU BACKGROUND CREATED
    optionsReturnText.setString("Options");
    optionsReturnText.setFont(mainFont);
    optionsReturnText.setCharacterSize(48U);
    optionsReturnText.setFillColor(sf::Color::White);
    optionsReturnText.setPosition(150.f, 140.f);
}

void Game::loadSounds()
{
    correctSoundBuffer.loadFromFile("./sounds/correctAnswer.wav");
    clickSoundBuffer.loadFromFile("./sounds/clicking.wav");
    wrongSoundBuffer.loadFromFile("./sounds/wrongAnswer.wav");
    winSoundBuffer.loadFromFile("./sounds/winGame.wav");
    loseSoundBuffer.loadFromFile("./sounds/loseGame.wav");
    music.openFromFile("./sounds/backgroundMusic.wav");

    clickSound.setBuffer(clickSoundBuffer);
    correctSound.setBuffer(correctSoundBuffer);
    wrongSound.setBuffer(wrongSoundBuffer);
    winSound.setBuffer(winSoundBuffer);
    loseSound.setBuffer(loseSoundBuffer);

    music.setVolume(50.0f);
    music.play();
}