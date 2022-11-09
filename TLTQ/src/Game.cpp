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
	else if (state == m_GameState::MainGame)
	{
		mainTexture.loadFromFile("./graphics/inGame.png");
		mainSprite.setTexture(mainTexture);
        mainSprite.setScale(4.0f, 4.0f);
		window.draw(mainSprite);

		mainFont.loadFromFile("./fonts/Square.ttf");

		sf::Text mainText("Choose the option that is best \nfor the environment!", mainFont, 36U);
		mainText.setPosition(600.0f, 185.0f);
		mainText.setFillColor(sf::Color::White);
		window.draw(mainText);

        // All questions haven't been answered
        if (questionNum < questions.size())
        {
            // Load text
            sf::Text correctAnswer(questions[questionNum].correctText, mainFont, defaultFontSize);
            correctAnswer.setPosition(584.0f, 788.0f);
            correctAnswer.setFillColor(sf::Color::White);
            sf::Text incorrectAnswer(questions[questionNum].incorrectText, mainFont, defaultFontSize);
            incorrectAnswer.setPosition(584.0f, 788.0f);
            incorrectAnswer.setFillColor(sf::Color::White);

            // Load images
            correctImageTexture.loadFromFile(questions[questionNum].correctImage);
            correctImageSprite.setTexture(correctImageTexture);
            correctImageSprite.setPosition(576.f, 456.f);
            correctImageSprite.setScale(4.0f, 4.0f);
            window.draw(correctImageSprite);
            incorrectImageTexture.loadFromFile(questions[questionNum].incorrectImage);
            incorrectImageSprite.setTexture(incorrectImageTexture);
            incorrectImageSprite.setPosition(1088.f, 456.f);
            incorrectImageSprite.setScale(4.0f, 4.0f);
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
            }
            else
            {
                loseTexture.loadFromFile("./graphics/loseScreen.png");
                loseSprite.setTexture(loseTexture);
                loseSprite.setScale(4.0f, 4.0f);
                window.draw(loseSprite);
            }
        }
	}
	else if (state == m_GameState::Paused)
	{

	}
	window.display();
}

void Game::update()
{
	if (state == m_GameState::Menu)
	{
        // If they clicked on NEW GAME
       if (mousePosition.x >= 32 && mousePosition.x <= 426 && mousePosition.y >= 26 && mousePosition.y <= 104) {
           state = m_GameState::MainGame;
           questionNum = 0;
           numCorrect = 0;
           for (int i = 0; i < questions.size(); i++)
           {
               questions[i].answered = false;
               questions[i].answeredCorrect = false;
           }
       }
       // If they clicked on LOAD GAME
       if (mousePosition.x >= 32 && mousePosition.x <= 426 && mousePosition.y >= 139 && mousePosition.y <= 216) {
          // This will simply resume the previous game for now since we do not have multiple games
           state = m_GameState::MainGame;
       } 
       // If they clicked on OPTIONS
       if (mousePosition.x >= 32 && mousePosition.x <= 426 && mousePosition.y >= 251 && mousePosition.y <= 316) {
           //TODO: implement functionality for set of options available to user (perhaps music mute and difficulty bar?)
       }
       //TODO (not neccessary): Perhaps if the sun is clicked on, he twitches or moves suddenly as a small easter egg
	}
	else if (state == m_GameState::MainGame)
	{
        // All questions haven't been answered
        if (questionNum < questions.size()) {
            // If left answer selected and question not already answered
            if (mousePosition.x >= 578 && mousePosition.x <= 832 && mousePosition.y >= 460 && mousePosition.y <= 712 &&
                !questions[questionNum].answered) {
                questions[questionNum].answered = true;

                if (questions[questionNum].leftIsCorrect) {
                    questions[questionNum].answeredCorrect = true;
                    numCorrect++;
                } else {
                    questions[questionNum].answeredCorrect = false;
                }
            }
            // If right answer selected and question not already answered
            else if (mousePosition.x >= 1090 && mousePosition.x <= 1344 && mousePosition.y >= 460 &&
                     mousePosition.y <= 712 && !questions[questionNum].answered) {
                questions[questionNum].answered = true;

                if (!questions[questionNum].leftIsCorrect) {
                    questions[questionNum].answeredCorrect = true;
                    numCorrect++;
                } else {
                    questions[questionNum].answeredCorrect = false;
                }
            }
            // If next button clicked and question already answered
            else if (mousePosition.x >= 1696 && mousePosition.x <= 1886 && mousePosition.y >= 978 &&
                     mousePosition.y <= 1052 && questions[questionNum].answered) {
                ++questionNum;
            }
            // If menu is selected
            else if (mousePosition.x >= 20 && mousePosition.x <= 525 && mousePosition.y >= 20 &&
                mousePosition.y <= 100)
            {
                state = m_GameState::Menu;
            }
        }
        // All questions have been answered
        else
        {
            // Home button clicked
            if (mousePosition.x >= 762 && mousePosition.x <= 1156 && mousePosition.y >= 756 && mousePosition.y <= 834)
            {
                state = m_GameState::Menu;
            }
            // Play again button clicked
        }
	}
	else if (state == m_GameState::Paused)
	{

	}

    // Reset mouse position to avoid overlapping elements.
    mousePosition.x = 0;
    mousePosition.y = 0;
}

void Game::eventHandler()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			mousePosition = sf::Mouse::getPosition(window);
		}
	}
}

void Game::loadQuestions() {
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
    progressSprite.setScale(4.0f, 4.0f);
    window.draw(progressSprite);
}