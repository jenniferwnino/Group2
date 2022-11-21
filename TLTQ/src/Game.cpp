#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Game::draw()
{
	window.clear();
	if (state == m_GameState::Menu)
	{
	    mainTexture.loadFromFile("./graphics/mainMenu.png");
		mainSprite.setTexture(mainTexture);
		mainSprite.setScale(4.0f, 4.0f);
		window.draw(mainSprite);
	}
	else if (state == m_GameState::Options)
    {
        // TEMP FOR OPTIONS - NEED A NICER SCREEN DESIGN
        // CODE WILL CHANGE WITH NEW SCREEN DESIGN
        mainFont.loadFromFile("./fonts/Square.ttf");

        setOptionsMenu_mainMenuButton();
        window.draw(returnToMain);
        window.draw(mainReturnText);

        changeLevel.setSize(sf::Vector2f(800.f, 150.f));
        changeLevel.setFillColor(sf::Color(255, 128, 0, 255));
        changeLevel.setPosition(550.f, 500.f);
        sf::Text selectLevelText ("Change difficulty level", mainFont, 48U);
        selectLevelText.setFillColor(sf::Color::White);
        selectLevelText.setPosition(680.f, 545.f);
        window.draw(changeLevel);
        window.draw(selectLevelText);
    }
    else if (state == m_GameState::Options_Level)
    {
        // TEMP FOR SETTING LEVEL - NEED A NICER SCREEN DESIGN
        // CODE WILL CHANGE WITH NEW SCREEN DESIGN
        mainFont.loadFromFile("./fonts/Square.ttf");

        setOptionsMenu_mainMenuButton();
        window.draw(returnToMain);
        window.draw(mainReturnText);

        setOptionsMenu_optionsMenuButton();
        window.draw(returnToOptionsMenu);
        window.draw(optionsReturnText);

        optionsL1.setSize(sf::Vector2f(256.f, 256.f));
        optionsL1.setPosition(400, 400);
        if (difficultyLevel == 1)
        {
            optionsL1.setFillColor(sf::Color::Blue);
        }
        else
        {
            optionsL1.setFillColor(sf::Color(255, 128, 0, 255));
        }
        sf::Text level1Text ("Level 1", mainFont, 48U);
        level1Text.setFillColor(sf::Color::White);
        level1Text.setPosition(420.f, 420.f);
        window.draw(optionsL1);
        window.draw(level1Text);

        optionsL2.setSize(sf::Vector2f(256.f, 256.f));
        optionsL2.setPosition(800, 400);
        if (difficultyLevel == 2) {
            optionsL2.setFillColor(sf::Color::Blue);
        }
        else
        {
            optionsL2.setFillColor(sf::Color(255, 128, 0, 255));
        }
        sf::Text level2Text ("Level 2", mainFont, 48U);
        level2Text.setFillColor(sf::Color::White);
        level2Text.setPosition(820.f, 420.f);
        window.draw(optionsL2);
        window.draw(level2Text);

        optionsL3.setSize(sf::Vector2f(256.f, 256.f));
        optionsL3.setPosition(1200, 400);
        if (difficultyLevel == 3)
        {
            optionsL3.setFillColor(sf::Color::Blue);
        }
        else
        {
            optionsL3.setFillColor(sf::Color(255, 128, 0, 255));
        }
        sf::Text level3Text ("Level 3", mainFont, 48U);
        level3Text.setFillColor(sf::Color::White);
        level3Text.setPosition(1220.f, 420.f);
        window.draw(optionsL3);
        window.draw(level3Text);
    }
    else if (state == m_GameState::MainGame)
	{
		// Load and draw background
        mainTexture.loadFromFile("./graphics/inGame.png");
		mainSprite.setTexture(mainTexture);
        mainSprite.setScale(4.0f, 4.0f);
		window.draw(mainSprite);

        // Load and draw main question text
		mainFont.loadFromFile("./fonts/Square.ttf");
		sf::Text mainText("Choose the option that is best \nfor the environment!", mainFont, 36U);
		mainText.setPosition(600.0f, 185.0f);
		mainText.setFillColor(sf::Color::White);
		window.draw(mainText);

        // All questions haven't been answered
        if (questionNum < questions.size())
        {
            // Load correct & incorrect answer text
            sf::Text correctAnswer(questions[questionNum].correctText, mainFont, defaultFontSize);
            correctAnswer.setPosition(textPos);
            correctAnswer.setFillColor(sf::Color::White);
            sf::Text incorrectAnswer(questions[questionNum].incorrectText, mainFont, defaultFontSize);
            incorrectAnswer.setPosition(textPos);
            incorrectAnswer.setFillColor(sf::Color::White);

            // Load correct & incorrect images
            correctImageTexture.loadFromFile(questions[questionNum].correctImage);
            correctImageSprite.setTexture(correctImageTexture);
            correctImageSprite.setScale(4.0f, 4.0f);
            incorrectImageTexture.loadFromFile(questions[questionNum].incorrectImage);
            incorrectImageSprite.setTexture(incorrectImageTexture);
            incorrectImageSprite.setScale(4.0f, 4.0f);

            // Set answer sprite locations
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

            // Draw answer sprites
            window.draw(correctImageSprite);
            window.draw(incorrectImageSprite);

            if (questionNum == 0 && numCorrect == 0)
            {
                progressTexture.loadFromFile("./graphics/sunSprite4of7.png");
                progressSprite.setTexture(progressTexture);
                progressSprite.setPosition(1512.5f, 15.5f);
                progressSprite.setScale(4.0f, 4.0f);
                window.draw(progressSprite);
            }

            if (questions[questionNum].answered && questions[questionNum].answeredCorrect)
            {
                window.draw(correctAnswer);
                updateProgressSprite();
            }

            else if (questions[questionNum].answered && !questions[questionNum].answeredCorrect)
            {
                window.draw(incorrectAnswer);
                updateProgressSprite();
            }

            window.draw(progressSprite);
        }
        // All questions answered - display win or lose
        else
        {
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
    else if (state == m_GameState::Game2)
    {
        window.draw(game2BackgroundSprite);
        window.draw(recycleSprite);
        window.draw(trashSprite);

        // Draw the temp shapes to sort
        for (int i = 0; i < 8; i++)
        {
            window.draw(toSort[i].tempShape);
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

void Game::update()
{
	if (state == m_GameState::Menu)
	{
        // If they clicked on NEW GAME
       if (mousePosition.x >= 32 && mousePosition.x <= 426 && mousePosition.y >= 26 && mousePosition.y <= 104)
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
       // If they clicked on LOAD GAME
       if (mousePosition.x >= 32 && mousePosition.x <= 426 && mousePosition.y >= 139 && mousePosition.y <= 216)
       {
          // This will simply resume the previous game for now since we do not have multiple games
           state = m_GameState::MainGame;
       } 
       // If they clicked on OPTIONS
       if (mousePosition.x >= 32 && mousePosition.x <= 426 && mousePosition.y >= 251 && mousePosition.y <= 316)
       {
           state = m_GameState::Options;
       }
       //TODO (not neccessary): Perhaps if the sun is clicked on, he twitches or moves suddenly as a small easter egg
	}
    else if (state == m_GameState::Options)
    {
        if (returnToMain.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
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
            winCondition = 0.75f;
            leftPos.y = 456.f;
            rightPos.y = 456.f;
        }
        else if (optionsL2.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            difficultyLevel = 2;
            winCondition = 0.80f;
            leftPos.y = 0.f;
            rightPos.y = 0.f;
        }
        else if (optionsL3.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            difficultyLevel = 3;
            winCondition = 0.85f;
            leftPos.y = 0.f;
            rightPos.y = 0.f;
        }
        else if (returnToMain.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Menu;
        }
        else if (returnToOptionsMenu.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Options;
        }
    }
	else if (state == m_GameState::MainGame)
	{
        // All questions haven't been answered
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
            // If next button clicked and question already answered
            else if (mousePosition.x >= 1696 && mousePosition.x <= 1886 && mousePosition.y >= 978 && mousePosition.y <= 1052 && questions[questionNum].answered)
            {
                ++questionNum;
                answerSoundHasPlayed = false;
            }
            // If menu is selected
            else if (mousePosition.x >= 20 && mousePosition.x <= 525 && mousePosition.y >= 20 && mousePosition.y <= 100)
            {
                state = m_GameState::Menu;
            }

            // If difficultyLevel 2 or 3, move the sprites
            if (difficultyLevel == 2 || difficultyLevel == 3)
            {
                // If question not answered, move the sprites
                if (!questions[questionNum].answered)
                {
                    // If sprite is still on the screen
                    if (leftPos.y < window.getSize().y)
                    {
                        if (difficultyLevel == 2)
                        {
                            leftPos.y += 1;
                            rightPos.y += 1;
                        }
                        if (difficultyLevel == 3)
                        {
                            leftPos.y += 1.5;
                            rightPos.y += 1.5;
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
        // All questions have been answered (winScreen or loseScreen is displayed)
        else
        {
            // Home button clicked
            if (mousePosition.x >= 762 && mousePosition.x <= 1156 && mousePosition.y >= 756 && mousePosition.y <= 834)
            {
                state = m_GameState::Menu;
            }
            // Play again button clicked
            else if (mousePosition.x >= 762 && mousePosition.x <= 1156 && mousePosition.y >= 586 && mousePosition.y <= 720)
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
    else if (state == m_GameState::Game2)
    {
        if (clickHeld)
        {
            toSort[spriteMoving].tempShape.setPosition(mousePosition.x, mousePosition.y);
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
        else if (event.type == sf::Event::MouseButtonReleased)
		{
			mousePosition = sf::Mouse::getPosition(window);
            clickSound.play();

            if (clickHeld) {clickHeld = false;}
            std::cout << "released" << std::endl;
		}
        else if (clickHeld)
        {
            mousePosition = sf::Mouse::getPosition(window);
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            // Pressing space bar controls the pause screen - Only works in game
            if (event.key.code == sf::Keyboard::Space && (state == m_GameState::MainGame || state == m_GameState::Paused))
            {
                if (state != m_GameState::Paused) {
                    state = m_GameState::Paused;
                }
                else
                {
                    state = m_GameState::MainGame;      // Will need to change how this works if more than 1 game
                }
            }
            // Pressing escape key closes window
            else if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            // TEMP OPTION TO ENTER GAME 2
            else if (event.key.code == sf::Keyboard::Num2)
            {
                state = m_GameState::Game2;
            }
        }
	}
}

void Game::loadGame1Assets() {
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
    game2BackgroudTexture.loadFromFile("./graphics/game2Screen.png");
    game2BackgroundSprite.setTexture(game2BackgroudTexture);
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
    progressSprite.setScale(4.0f, 4.0f);
    window.draw(progressSprite);
}

void Game::setOptionsMenu_mainMenuButton() {
    returnToMain.setSize(sf::Vector2f(400.f, 75.f));
    returnToMain.setFillColor(sf::Color(255, 128, 0, 255));
    returnToMain.setPosition(25, 30);
    mainReturnText.setString("Menu");
    mainReturnText.setFont(mainFont);
    mainReturnText.setCharacterSize(48U);
    mainReturnText.setFillColor(sf::Color::White);
    mainReturnText.setPosition(150.f, 40.f);
}

void Game::setOptionsMenu_optionsMenuButton()
{
    returnToOptionsMenu.setSize(sf::Vector2f(400.f, 75.f));
    returnToOptionsMenu.setFillColor(sf::Color(255, 128, 0, 255));
    returnToOptionsMenu.setPosition(25, 130);
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