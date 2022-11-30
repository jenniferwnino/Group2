#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>

// General Game Functions
void Game::draw()
{
	window.clear();
	if (state == m_GameState::Menu)
	{
		window.draw(mainSprite);
	}
    else if (state == m_GameState::GameSelection)
    {
        window.draw(gameSelectSprite);
    }
	else if (state == m_GameState::OptionsMenu)
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
    else if (state == m_GameState::DifficultySelect)
    {
        window.draw(difficultyChoiceSprite);

        // Selected difficulty level shows blue, other levels show orange
        if (difficultyLevel == 1)
        {
            window.draw(difficulty1SelectedSprite);
            window.draw(difficulty2NotSelectedSprite);
            window.draw(difficulty3NotSelectedSprite);
        }
        else if (difficultyLevel == 2)
        {
            window.draw(difficulty1NotSelectedSprite);
            window.draw(difficulty2SelectedSprite);
            window.draw(difficulty3NotSelectedSprite);
        }
        else if (difficultyLevel == 3)
        {
            window.draw(difficulty1NotSelectedSprite);
            window.draw(difficulty2NotSelectedSprite);
            window.draw(difficulty3SelectedSprite);
        }
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
                    // If they got two or more wrong in a row && if its not the last question
                    if (numWrong >= 2 && questionNum != 3)
                        displayHint();
                }

                window.draw(progressSprite);

            }
            // If all questions answered - display win or lose screen based on score
            else
            {
                // Game won
                if (numCorrect >= (questions.size()  * winCondition))
                {
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

        // Display game background until all questions are sorted
        else if (!game2Finished) {
            window.draw(game2BackgroundSprite);

            // Display prompt based on attempt number
            if (game2AttemptNum != 1)
            {
                game2Prompt.setString("You did not sort all of the items correctly. Try again! \n"
                                      "Once sorted, the item will not be movable again. \n"
                                      "After you have sorted all the items, click the next button");
            }
            window.draw(game2Prompt);

            // Draw the 8 image sprites
            for (int i = 0; i < 8; i++)
            {
                window.draw(toSort[i].sortableSprite);
            }

            // Display sun sprite depending on attempt number
            if (game2AttemptNum == 1)
            {
                window.draw(game2Sun1Sprite);
            }
            else if (game2AttemptNum == 2)
            {
                window.draw(game2Sun2Sprite);
            }
            else
            {
                window.draw(game2Sun3Sprite);
            }
        }

        // If game finished and all questions were sorted correctly - show win screen
        else if (game2Finished && game2Score == 8)
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

        // If game finished and all questions were NOT sorted correctly - show lose screen
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
           state = returnTo;
       } 
       // Options button is clicked
       if (mainOptionsButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
       {
           state = m_GameState::OptionsMenu;
       }
	}
    else if (state == m_GameState::GameSelection)
    {
        // Clicked menu
        if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Menu;
        }

        // Clicked game 1
        else if (game1Select.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            // Reset all game 1 settings and launch
            state = m_GameState::MainGame;
            questionNum = 0;
            numCorrect = 0;
            winLoseSoundHasPlayed = false;
            numWrong = 0;
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
            resetGame2Hard();
            state = m_GameState::Game2;
        }
    }
    else if (state == m_GameState::OptionsMenu)
    {
        if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Menu;
        }
        else if (changeLevel.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::DifficultySelect;
        }
    }
    else if (state == m_GameState::DifficultySelect)
    {
        // Difficulty level 1 clicked (not already selected)
        if (difficulty1SelectedSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && difficultyLevel != 1)
        {
            // Set difficulty level
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
            game2MaxAttempts = 3;
        }

        // Difficulty level 2 clicked (not already selected)
        else if (difficulty2SelectedSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && difficultyLevel != 2)
        {
            // Set difficulty level
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
            game2MaxAttempts = 3;
        }

        // Difficulty level 3 clicked (not already selected)
        else if (difficulty3SelectedSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && difficultyLevel != 3)
        {
            // Set difficult level
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
            game2MaxAttempts = 2;
        }
        else if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::Menu;
        }
        else if (returnToOptionsButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
        {
            state = m_GameState::OptionsMenu;
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
                returnTo = m_GameState::MainGame;
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
                returnTo = m_GameState::MainGame;
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
                    numWrong = 0;
                    if (!answerSoundHasPlayed)
                        correctSound.play();
                }
                // Incorrect sprite clicked and question not already answered
                else if (incorrectImageSprite.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && !questions[questionNum].answered)
                {
                    questions[questionNum].answered = true;
                    questions[questionNum].answeredCorrect = false;
                    numWrong++;
                    if (!answerSoundHasPlayed)
                        wrongSound.play();
                }
                // Menu button is clicked
                else if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                {
                    returnTo = m_GameState::MainGame;
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
                            numWrong++;
                            // If they got two or more wrong in a row && if its not the last question
                            if (numWrong >= 2 && questionNum != 3)
                                displayHint();
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
                    returnTo = m_GameState::MainGame;
                    state = m_GameState::Menu;
                }
                // Play again button clicked
                else if (winLosePlayAgainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                {
                    state = m_GameState::MainGame;
                    questionNum = 0;
                    numCorrect = 0;
                    winLoseSoundHasPlayed = false;
                    numWrong = 0;
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
        // On tutorial screens
        if (!tutorial2aWatched)
        {
            // Menu button is clicked
            if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                returnTo = m_GameState::Game2;
                state = m_GameState::Menu;
                mousePosition = sf::Vector2i(0, 0);
            }
            // Next button is clicked
            if (nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && !clickHeld)
            {
                tutorial2aWatched = true;
                mousePosition = sf::Vector2i(0, 0);
            }
        }
        else if (!tutorial2bWatched)
        {
            // Menu button is clicked
            if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                returnTo = m_GameState::Game2;
                state = m_GameState::Menu;
                mousePosition = sf::Vector2i(0, 0);
            }
            // Next button is clicked
            if (nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && !clickHeld)
            {
                tutorial2bWatched = true;
                mousePosition = sf::Vector2i(0, 0);
            }
        }

        // On Game screen
        else if (!game2Finished) {
            // Update position if object is being dragged & not already marked as sorted
            if (clickHeld && !toSort[spriteMoving].sorted)
            {
                toSort[spriteMoving].sortableSprite.setPosition(mousePosition.x, mousePosition.y);
            }

            // Mouse released and sprite dragged to recycling square 1 && position not already occupied
            else if (game2RecycleDragArea1.getGlobalBounds().contains(toSort[spriteMoving].sortableSprite.getPosition()) && !game2RecycleSq1Occupied)
            {
                // Snap into place & mark as sorted
                toSort[spriteMoving].sortableSprite.setPosition(game2RecycleSq1.getPosition());
                toSort[spriteMoving].sorted = true;
                // Mark position as occupied
                game2RecycleSq1Occupied = true;
                // If recyclable item, store as sorted correctly
                if (toSort[spriteMoving].recyclable)
                {
                    toSort[spriteMoving].sortedCorrectly = true;
                }
            }

            // Mouse released and sprite dragged to recycling square 2 && position not already occupied
            else if (game2RecycleDragArea2.getGlobalBounds().contains(toSort[spriteMoving].sortableSprite.getPosition()) && !game2RecycleSq2Occupied)
            {
                // Snap into place & mark as sorted
                toSort[spriteMoving].sortableSprite.setPosition(game2RecycleSq2.getPosition());
                toSort[spriteMoving].sorted = true;
                // Mark position as occupied
                game2RecycleSq2Occupied = true;
                // If recyclable item, store as sorted correctly
                if (toSort[spriteMoving].recyclable)
                {
                    toSort[spriteMoving].sortedCorrectly = true;
                }
            }

            // Mouse released and sprite dragged to recycling square 3 && position not already occupied
            else if (game2RecycleDragArea3.getGlobalBounds().contains(toSort[spriteMoving].sortableSprite.getPosition()) && !game2RecycleSq3Occupied)
            {
                // Snap into place & mark as sorted
                toSort[spriteMoving].sortableSprite.setPosition(game2RecycleSq3.getPosition());
                toSort[spriteMoving].sorted = true;
                // Mark position as occupied
                game2RecycleSq3Occupied = true;
                // If recyclable item, store as sorted correctly
                if (toSort[spriteMoving].recyclable)
                {
                    toSort[spriteMoving].sortedCorrectly = true;
                }
            }

            // Mouse released and sprite dragged to recycling square 4 && position not already occupied
            else if (game2RecycleDragArea4.getGlobalBounds().contains(toSort[spriteMoving].sortableSprite.getPosition()) && !game2RecycleSq4Occupied)
            {
                // Snap into place & mark as sorted
                toSort[spriteMoving].sortableSprite.setPosition(game2RecycleSq4.getPosition());
                toSort[spriteMoving].sorted = true;
                // Mark position as occupied
                game2RecycleSq4Occupied = true;
                // If recyclable item, store as sorted correctly
                if (toSort[spriteMoving].recyclable)
                {
                    toSort[spriteMoving].sortedCorrectly = true;
                }
            }

            // Mouse released and sprite dragged to trash square 1 && position not already occupied
            else if (game2TrashDragArea1.getGlobalBounds().contains(toSort[spriteMoving].sortableSprite.getPosition()) && !game2TrashSq1Occupied)
            {
                // Snap into place & mark as sorted
                toSort[spriteMoving].sortableSprite.setPosition(game2TrashSq1.getPosition());
                toSort[spriteMoving].sorted = true;
                // Mark position as occupied
                game2TrashSq1Occupied = true;
                // If trash item, store as sorted correctly
                if (!toSort[spriteMoving].recyclable)
                {
                    toSort[spriteMoving].sortedCorrectly = true;
                }
            }

            // Mouse released and sprite dragged to trash square 2 && position not already occupied
            else if (game2TrashDragArea2.getGlobalBounds().contains(toSort[spriteMoving].sortableSprite.getPosition()) && !game2TrashSq2Occupied)
            {
                // Snap into place & mark as sorted
                toSort[spriteMoving].sortableSprite.setPosition(game2TrashSq2.getPosition());
                toSort[spriteMoving].sorted = true;
                // Mark position as occupied
                game2TrashSq2Occupied = true;
                // If trash item, store as sorted correctly
                if (!toSort[spriteMoving].recyclable)
                {
                    toSort[spriteMoving].sortedCorrectly = true;
                }
            }

            // Mouse released and sprite dragged to trash square 3 && position not already occupied
            else if (game2TrashDragArea3.getGlobalBounds().contains(toSort[spriteMoving].sortableSprite.getPosition()) && !game2TrashSq3Occupied)
            {
                // Snap into place & mark as sorted
                toSort[spriteMoving].sortableSprite.setPosition(game2TrashSq3.getPosition());
                toSort[spriteMoving].sorted = true;
                // Mark position as occupied
                game2TrashSq3Occupied = true;
                // If trash item, store as sorted correctly
                if (!toSort[spriteMoving].recyclable)
                {
                    toSort[spriteMoving].sortedCorrectly = true;
                }
            }

            // Mouse released and sprite dragged to trash square 4 && position not already occupied
            else if (game2TrashDragArea4.getGlobalBounds().contains(toSort[spriteMoving].sortableSprite.getPosition()) && !game2TrashSq4Occupied)
            {
                // Snap into place & mark as sorted
                toSort[spriteMoving].sortableSprite.setPosition(game2TrashSq4.getPosition());
                toSort[spriteMoving].sorted = true;
                // Mark position as occupied
                game2TrashSq4Occupied = true;
                // If trash item, store as sorted correctly
                if (!toSort[spriteMoving].recyclable)
                {
                    toSort[spriteMoving].sortedCorrectly = true;
                }
            }

            // Reset numSorted to recount
            numSorted = 0;
            // Check if all items have been sorted
            for (int i = 0; i < 8; i++)
            {
                if (toSort[i].sorted)
                {
                    numSorted++;
                }
            }

            // If all sorted & clicked next button
            if (numSorted == 8 && nextButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                // Reset mousePosition to avoid running up counters
                mousePosition = sf::Vector2i(0, 0);

                // Reset game2Score to recount
                game2Score = 0;
                // Count up number of objects sorted correctly
                for (int i = 0; i < toSort.size(); i++)
                {
                    if (toSort[i].sortedCorrectly)
                    {
                        game2Score++;
                    }
                }

                // Update the high score if current score is higher
                if (game2Score > game2HighScore)
                {
                    game2HighScore = game2Score;
                }

                // Add one to the number of attempts
                game2AttemptNum++;

                // If all objects are sorted correctly or if over maxAttempts
                if (game2Score == 8 || game2AttemptNum > game2MaxAttempts)
                {
                    // Mark the game as finished to display win/lose screen
                    game2Finished = true;
                }

                // If not all sorted correctly and maxAttemps not reached
                else
                {
                    resetGame2Soft();
                }
            }

            // Clicked menu button
            if (returnToMainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)) && !clickHeld)
            {
                mousePosition = sf::Vector2i(0, 0);
                returnTo = m_GameState::Game2;
                state = m_GameState::Menu;
            }
        }

        // Game finished - Displaying win/lose screen
        else
        {
            // Home button clicked
            if (winLoseMenuButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                mousePosition = sf::Vector2i(0, 0);
                returnTo = m_GameState::Game2;
                state = m_GameState::Menu;
            }

            // Play again button clicked
            else if (winLosePlayAgainButton.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
            {
                mousePosition = sf::Vector2i(0, 0);
                state = m_GameState::Game2;
                winLoseSoundHasPlayed = false;
                game2Finished = false;
                resetGame2Hard();
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
                if (toSort[i].sortableSprite.getGlobalBounds().contains(sf::Vector2f(clickPos)))
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
            std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
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

// Menus, options, and general settings
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

void Game::loadGlobalAssets() {
    // Set mainFont
    mainFont.loadFromFile("./fonts/Square.ttf");

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
}

void Game::loadMainMenuAssets()
{
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
}

void Game::loadGameSelectionAssets()
{
    // Add background
    gameSelectTexture.loadFromFile("./graphics/gameSelect.png");
    gameSelectSprite.setTexture(gameSelectTexture);
    gameSelectSprite.setScale(4.0f, 4.0f);

    // Create hidden button rectangles
    game1Select.setPosition(607, 263);
    game1Select.setSize(sf::Vector2f(708.f, 348.f));
    game2Select.setPosition(607, 650);
    game2Select.setSize(sf::Vector2f(708.f, 348.f));
}

void Game::loadDifficultySelectionAssets()
{
    // Add background
    difficultyChoiceTexture.loadFromFile("./graphics/difficultyChoice.png");
    difficultyChoiceSprite.setTexture(difficultyChoiceTexture);
    difficultyChoiceSprite.setScale(4.f, 4.f);

    // Create level 1 button sprites
    difficulty1SelectedTexture.loadFromFile("./graphics/difficulty1Selected.png");
    difficulty1SelectedSprite.setTexture(difficulty1SelectedTexture);
    difficulty1SelectedSprite.setScale(4.f, 4.f);
    difficulty1SelectedSprite.setPosition(600.f, 308.f);
    difficulty1NotSelectedTexture.loadFromFile("./graphics/difficulty1NotSelected.png");
    difficulty1NotSelectedSprite.setTexture(difficulty1NotSelectedTexture);
    difficulty1NotSelectedSprite.setScale(4.f, 4.f);
    difficulty1NotSelectedSprite.setPosition(600.f, 308.f);

    // Create level 2 button sprites
    difficulty2SelectedTexture.loadFromFile("./graphics/difficulty2Selected.png");
    difficulty2SelectedSprite.setTexture(difficulty2SelectedTexture);
    difficulty2SelectedSprite.setScale(4.f, 4.f);
    difficulty2SelectedSprite.setPosition(600.f, 532.f);
    difficulty2NotSelectedTexture.loadFromFile("./graphics/difficulty2NotSelected.png");
    difficulty2NotSelectedSprite.setTexture(difficulty2NotSelectedTexture);
    difficulty2NotSelectedSprite.setScale(4.f, 4.f);
    difficulty2NotSelectedSprite.setPosition(600.f, 532.f);

    // Create level 3 button sprites
    difficulty3SelectedTexture.loadFromFile("./graphics/difficulty3Selected.png");
    difficulty3SelectedSprite.setTexture(difficulty3SelectedTexture);
    difficulty3SelectedSprite.setScale(4.f, 4.f);
    difficulty3SelectedSprite.setPosition(600.f, 756.f);
    difficulty3NotSelectedTexture.loadFromFile("./graphics/difficulty3NotSelected.png");
    difficulty3NotSelectedSprite.setTexture(difficulty3NotSelectedTexture);
    difficulty3NotSelectedSprite.setScale(4.f, 4.f);
    difficulty3NotSelectedSprite.setPosition(600.f, 756.f);



    // For options menu - change level button
    changeLevel.setSize(sf::Vector2f(800.f, 150.f));
    changeLevel.setFillColor(sf::Color(255, 128, 0, 255));
    changeLevel.setPosition(550.f, 500.f);
}

void Game::loadWinLoseScreenAssets()
{
    // Load win screen
    winTexture.loadFromFile("./graphics/winScreen.png");
    winSprite.setTexture(winTexture);
    winSprite.setScale(4.0f, 4.0f);

    // Load lose screen
    loseTexture.loadFromFile("./graphics/loseScreen.png");
    loseSprite.setTexture(loseTexture);
    loseSprite.setScale(4.0f, 4.0f);

    // Create menu button seen on win/lose screen
    winLoseMenuButton.setPosition(757, 749);
    winLoseMenuButton.setSize(sf::Vector2f(405, 90));

    // Create play again button seen on win/lose screen
    winLosePlayAgainButton.setPosition(755, 580);
    winLosePlayAgainButton.setSize(sf::Vector2f(405, 145));
}

void Game::loadTutorialAssets()
{
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

// Game 1 loading and helper functions
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

    // Setting the hint message
    bubble.setRadius(120.0);
    bubble.setPosition(1400.f, 450.f);
    bubble.setFillColor(sf::Color::White);
    bubble.setOutlineThickness(5);
    bubble.setOutlineColor(sf::Color::Black);
    bubble.setScale(2, 1);
    triangle.setPointCount(3);
    triangle.setRadius(120.0);
    triangle.setPosition(1600.f, 400.f);
    triangle.setFillColor(sf::Color::White);
    triangle.setOutlineThickness(5);
    triangle.setOutlineColor(sf::Color::Black);
    hint.setFont(mainFont);
    hint.setPosition(1450.f, 500.f);
    hint.setCharacterSize(24);
    hint.setFillColor(sf::Color::Black);

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

void Game::displayHint()
{
    window.draw(triangle);
    window.draw(bubble);
    if (questionNum == 1)
        hint.setString("Want a hint for the next one?\nRemember that plastic is one of\nour planet's worst enemies!");
    if (questionNum == 2)
        hint.setString("Want a hint for the next one?\nRemember that oil does not get\nalong well with the fishies!");
    window.draw(hint);
}

// Game 2 loading and helper functions
void Game::loadGame2Assets() {
    // Load background
    game2BackgroundTexture.loadFromFile("./graphics/inGameSortingSprites.png");
    game2BackgroundSprite.setTexture(game2BackgroundTexture);
    game2BackgroundSprite.setScale(4.0f, 4.0f);

    // Create prompt text
    game2Prompt.setString("Sort each of the items as either recylable or as trash. \n"
                          "Once sorted, the item will not be movable again. \n"
                          "After you have sorted all the items, click the next button");
    game2Prompt.setFont(mainFont);
    game2Prompt.setPosition(428.f, 900.f);
    game2Prompt.setCharacterSize(36U);
    game2Prompt.setFillColor(sf::Color::White);

    // Create sun sprites
    game2Sun1Texture.loadFromFile("./graphics/sunSprite4of7.png");
    game2Sun1Sprite.setTexture(game2Sun1Texture);
    game2Sun1Sprite.setPosition(1512.5f, 15.5f);
    game2Sun1Sprite.setScale(4.0f, 4.05f);
    game2Sun2Texture.loadFromFile("./graphics/sunSprite3of7.png");
    game2Sun2Sprite.setTexture(game2Sun2Texture);
    game2Sun2Sprite.setPosition(1512.5f, 15.5f);
    game2Sun2Sprite.setScale(4.0f, 4.05f);
    game2Sun3Texture.loadFromFile("./graphics/sunSprite2of7.png");
    game2Sun3Sprite.setTexture(game2Sun3Texture);
    game2Sun3Sprite.setPosition(1512.5f, 15.5f);
    game2Sun3Sprite.setScale(4.0f, 4.05f);

    // Set square positions of initial grid
    game2StartSq1.setPosition(828.f, 268.f);
    game2StartSq1.setSize(sf::Vector2f(128.f, 128.f));
    game2StartSq2.setPosition(964.f, 268.f);
    game2StartSq2.setSize(sf::Vector2f(128.f, 128.f));
    game2StartSq3.setPosition(828.f, 404.f);
    game2StartSq3.setSize(sf::Vector2f(128.f, 128.f));
    game2StartSq4.setPosition(964.f, 404.f);
    game2StartSq4.setSize(sf::Vector2f(128.f, 128.f));
    game2StartSq5.setPosition(828.f, 540.f);
    game2StartSq5.setSize(sf::Vector2f(128.f, 128.f));
    game2StartSq6.setPosition(964.f, 540.f);
    game2StartSq6.setSize(sf::Vector2f(128.f, 128.f));
    game2StartSq7.setPosition(828.f, 676.f);
    game2StartSq7.setSize(sf::Vector2f(128.f, 128.f));
    game2StartSq8.setPosition(964.f, 676.f);
    game2StartSq8.setSize(sf::Vector2f(128.f, 128.f));

    // Set square positions for recycle sorted squares
    game2RecycleSq1.setPosition(47.f, 499.f);
    game2RecycleSq1.setSize(sf::Vector2f(128.f, 128.f));
    game2RecycleSq2.setPosition(229.f, 499.f);
    game2RecycleSq2.setSize(sf::Vector2f(128.f, 128.f));
    game2RecycleSq3.setPosition(47.f, 679.f);
    game2RecycleSq3.setSize(sf::Vector2f(128.f, 128.f));
    game2RecycleSq4.setPosition(229.f, 679.f);
    game2RecycleSq4.setSize(sf::Vector2f(128.f, 128.f));

    // Set drag areas for recycle squares
    game2RecycleDragArea1.setPosition(28.f, 480.f);
    game2RecycleDragArea1.setSize(sf::Vector2f(168.f, 168.f));
    game2RecycleDragArea2.setPosition(214.f, 480.f);
    game2RecycleDragArea2.setSize(sf::Vector2f(168.f, 168.f));
    game2RecycleDragArea3.setPosition(28.f, 660.f);
    game2RecycleDragArea3.setSize(sf::Vector2f(168.f, 168.f));
    game2RecycleDragArea4.setPosition(214.f, 660.f);
    game2RecycleDragArea4.setSize(sf::Vector2f(168.f, 168.f));

    // Set square positions for trash sorted squares
    game2TrashSq1.setPosition(1564.f, 499.f);
    game2TrashSq1.setSize(sf::Vector2f(128.f, 128.f));
    game2TrashSq2.setPosition(1744.f, 499.f);
    game2TrashSq2.setSize(sf::Vector2f(128.f, 128.f));
    game2TrashSq3.setPosition(1564.f, 679.f);
    game2TrashSq3.setSize(sf::Vector2f(128.f, 128.f));
    game2TrashSq4.setPosition(1744.f, 679.f);
    game2TrashSq4.setSize(sf::Vector2f(128.f, 128.f));

    // Set drag areas for trash squares
    game2TrashDragArea1.setPosition(1548.f, 480.f);
    game2TrashDragArea1.setSize(sf::Vector2f(168.f, 168.f));
    game2TrashDragArea2.setPosition(1728.f, 480.f);
    game2TrashDragArea2.setSize(sf::Vector2f(168.f, 168.f));
    game2TrashDragArea3.setPosition(1548.f, 660.f);
    game2TrashDragArea3.setSize(sf::Vector2f(168.f, 168.f));
    game2TrashDragArea4.setPosition(1728.f, 660.f);
    game2TrashDragArea4.setSize(sf::Vector2f(168.f, 168.f));

    // CREATING MANUALLY - Potentially add through .csv in future
    // Add initial items to array
    for (int i = 0; i < 8; i++)
    {
        toSort.emplace_back(m_Sortables());
    }
    // Load bag (trash) and put in square 1
    toSort[0].sortableTexture.loadFromFile("./graphics/game2BagTrash.png");
    toSort[0].sortableSprite.setTexture(toSort[0].sortableTexture);
    toSort[0].sortableSprite.setScale(sf::Vector2f(4.f, 4.f));
    toSort[0].unsortPos = game2StartSq1.getPosition();
    toSort[0].sortableSprite.setPosition(toSort[0].unsortPos);
    toSort[0].recyclable = false;
    // Load battery (recycling) and put in square 2
    toSort[1].sortableTexture.loadFromFile("./graphics/game2BatteryRecycling.png");
    toSort[1].sortableSprite.setTexture(toSort[1].sortableTexture);
    toSort[1].sortableSprite.setScale(sf::Vector2f(4.f, 4.f));
    toSort[1].unsortPos = game2StartSq2.getPosition();
    toSort[1].sortableSprite.setPosition(toSort[1].unsortPos);
    toSort[1].recyclable = true;
    // Load banana (trash) and put in square 3
    toSort[2].sortableTexture.loadFromFile("./graphics/game2BananaTrash.png");
    toSort[2].sortableSprite.setTexture(toSort[2].sortableTexture);
    toSort[2].sortableSprite.setScale(sf::Vector2f(4.f, 4.f));
    toSort[2].unsortPos = game2StartSq3.getPosition();
    toSort[2].sortableSprite.setPosition(toSort[2].unsortPos);
    toSort[2].recyclable = false;
    // Load hanger (trash) and put in square 4
    toSort[3].sortableTexture.loadFromFile("./graphics/game2HangerTrash.png");
    toSort[3].sortableSprite.setTexture(toSort[3].sortableTexture);
    toSort[3].sortableSprite.setScale(sf::Vector2f(4.f, 4.f));
    toSort[3].unsortPos = game2StartSq4.getPosition();
    toSort[3].sortableSprite.setPosition(toSort[3].unsortPos);
    toSort[3].recyclable = false;
    // Load can (recycling) and put in square 5
    toSort[4].sortableTexture.loadFromFile("./graphics/game2CanRecycling.png");
    toSort[4].sortableSprite.setTexture(toSort[4].sortableTexture);
    toSort[4].sortableSprite.setScale(sf::Vector2f(4.f, 4.f));
    toSort[4].unsortPos = game2StartSq5.getPosition();
    toSort[4].sortableSprite.setPosition(toSort[4].unsortPos);
    toSort[4].recyclable = true;
    // Load mirror (trash) and put in square 6
    toSort[5].sortableTexture.loadFromFile("./graphics/game2MirrorTrash.png");
    toSort[5].sortableSprite.setTexture(toSort[5].sortableTexture);
    toSort[5].sortableSprite.setScale(sf::Vector2f(4.f, 4.f));
    toSort[5].unsortPos = game2StartSq6.getPosition();
    toSort[5].sortableSprite.setPosition(toSort[5].unsortPos);
    toSort[5].recyclable = false;
    // Load glass bottle (recycling) and put in square 7
    toSort[6].sortableTexture.loadFromFile("./graphics/game2GlassBottleRecycling.png");
    toSort[6].sortableSprite.setTexture(toSort[6].sortableTexture);
    toSort[6].sortableSprite.setScale(sf::Vector2f(4.f, 4.f));
    toSort[6].unsortPos = game2StartSq7.getPosition();
    toSort[6].sortableSprite.setPosition(toSort[6].unsortPos);
    toSort[6].recyclable = true;
    // Load plastic bottle (recycling) and put in square 8
    toSort[7].sortableTexture.loadFromFile("./graphics/game2PlasticBottleRecycling.png");
    toSort[7].sortableSprite.setTexture(toSort[7].sortableTexture);
    toSort[7].sortableSprite.setScale(sf::Vector2f(4.f, 4.f));
    toSort[7].unsortPos = game2StartSq8.getPosition();
    toSort[7].sortableSprite.setPosition(toSort[7].unsortPos);
    toSort[7].recyclable = true;
}

void Game::resetGame2Soft()
{
    // Reset according to difficulty level
    if (difficultyLevel == 1)
    {
        // Move only the items sorted incorrectly back to their original position
        for (int i = 0; i < 8; i++)
        {
            if (!toSort[i].sortedCorrectly)
            {
                // Mark the position it was in as unoccupied
                if (game2RecycleDragArea1.getGlobalBounds().contains(toSort[i].sortableSprite.getPosition()))
                {
                    game2RecycleSq1Occupied = false;
                }
                else if (game2RecycleDragArea2.getGlobalBounds().contains(toSort[i].sortableSprite.getPosition()))
                {
                    game2RecycleSq2Occupied = false;
                }
                else if (game2RecycleDragArea3.getGlobalBounds().contains(toSort[i].sortableSprite.getPosition()))
                {
                    game2RecycleSq3Occupied = false;
                }
                else if (game2RecycleDragArea4.getGlobalBounds().contains(toSort[i].sortableSprite.getPosition()))
                {
                    game2RecycleSq4Occupied = false;
                }
                else if (game2TrashDragArea1.getGlobalBounds().contains(toSort[i].sortableSprite.getPosition()))
                {
                    game2TrashSq1Occupied = false;
                }
                else if (game2TrashDragArea2.getGlobalBounds().contains(toSort[i].sortableSprite.getPosition()))
                {
                    game2TrashSq2Occupied = false;
                }
                else if (game2TrashDragArea3.getGlobalBounds().contains(toSort[i].sortableSprite.getPosition()))
                {
                    game2TrashSq3Occupied = false;
                }
                else if (game2TrashDragArea4.getGlobalBounds().contains(toSort[i].sortableSprite.getPosition()))
                {
                    game2TrashSq4Occupied = false;
                }

                // Return to original position
                toSort[i].sortableSprite.setPosition(toSort[i].unsortPos);
                toSort[i].sorted = false;
            }
        }
    }
    else
    {
        // Move all items back to their original position
        for (int i = 0; i < 8; i++)
        {
            toSort[i].sortableSprite.setPosition(toSort[i].unsortPos);
            toSort[i].sorted = false;
        }
        // Mark all positions as unoccupied
        game2RecycleSq1Occupied = false;
        game2RecycleSq2Occupied = false;
        game2RecycleSq3Occupied = false;
        game2RecycleSq4Occupied = false;
        game2TrashSq1Occupied = false;
        game2TrashSq2Occupied = false;
        game2TrashSq3Occupied = false;
        game2TrashSq4Occupied = false;
    }
}

void Game::resetGame2Hard() {
    // Move all items back to their original position
    for (int i = 0; i < 8; i++)
    {
        toSort[i].sortableSprite.setPosition(toSort[i].unsortPos);
        toSort[i].sorted = false;
    }

    // Mark all positions as unoccupied
    game2RecycleSq1Occupied = false;
    game2RecycleSq2Occupied = false;
    game2RecycleSq3Occupied = false;
    game2RecycleSq4Occupied = false;
    game2TrashSq1Occupied = false;
    game2TrashSq2Occupied = false;
    game2TrashSq3Occupied = false;
    game2TrashSq4Occupied = false;

    // Reset attempt number
    game2AttemptNum = 1;
}
