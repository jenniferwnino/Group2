#include "Game.h"
#include <iostream>

void Game::draw()
{
	window.clear();
	if (state == m_GameState::Menu)
	{
		mainTexture.loadFromFile("./graphics/climateStompersMainMenu.png");
		mainSprite.setTexture(mainTexture);
		window.draw(mainSprite);
	}
	else if (state == m_GameState::MainGame)
	{
		questions.emplace_back(m_Questions{ "Correct", "Incorrect", false, false, true });
		mainTexture.loadFromFile("./graphics/climateStompersInGame.png");
		mainSprite.setTexture(mainTexture);
		window.draw(mainSprite);

		mainFont.loadFromFile("./fonts/Square.ttf");

		sf::Text mainText("Choose the option that is best \nfor the environment!", mainFont, 36U);
		mainText.setPosition(600.0f, 185.0f);
		mainText.setFillColor(sf::Color::Black);

		sf::Text correctAnswer(questions[questionNum].correctText, mainFont, defaultFontSize);
		correctAnswer.setPosition(584.0f, 788.0f);
		correctAnswer.setFillColor(sf::Color::Black);
		sf::Text incorrectAnswer(questions[questionNum].incorrectText, mainFont, defaultFontSize);
		incorrectAnswer.setPosition(584.0f, 788.0f);
		incorrectAnswer.setFillColor(sf::Color::Black);

		if (questions[questionNum].answered && questions[questionNum].answeredCorrect)
		{
			window.draw(correctAnswer);
		}

		else if (questions[questionNum].answered && !questions[questionNum].answeredCorrect)
		{
			window.draw(incorrectAnswer);
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

	}
	else if (state == m_GameState::MainGame)
	{
		if (mousePosition.x >= 578 && mousePosition.x <= 832 && mousePosition.y >= 460 && mousePosition.y <= 712 && !questions[questionNum].answered)
		{
			questions[questionNum].answered = true;

			if (questions[questionNum].leftIsCorrect)
			{
				questions[questionNum].answeredCorrect = true;
				numCorrect++;
			}
			else
			{
				questions[questionNum].answeredCorrect = false;
			}
		}
		else if (mousePosition.x >= 1090 && mousePosition.x <= 1344 && mousePosition.y >= 460 && mousePosition.y <= 712 && !questions[questionNum].answered)
		{
			questions[questionNum].answered = true;

			if (!questions[questionNum].leftIsCorrect)
			{
				questions[questionNum].answeredCorrect = true;
				numCorrect++;
			}
			else
			{
				questions[questionNum].answeredCorrect = false;
			}
		}
		else if (mousePosition.x >= 1696 && mousePosition.x <= 1886 && mousePosition.y >= 978 && mousePosition.y <= 1052 && questions[questionNum].answered)
		{
			if (++questionNum >= 1)
			{
				state = m_GameState::Menu;
			}
		}
	}
	else if (state == m_GameState::Paused)
	{

	}
}

void Game::eventHandler()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			state = m_GameState::MainGame;
			mousePosition = sf::Mouse::getPosition(window);
			std::cout << "Clicked\n";
		}
	}
}
