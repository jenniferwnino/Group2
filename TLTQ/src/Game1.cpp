#include "Game1.h"
#include <iostream>

// Constructor
Game1::Game1() {
    questionNumber = 1;
    questionResponse = false;
    leftAnswer = false;

    game1Texture.loadFromFile("../TLTQ/graphics/climateStompersInGame-export.png");
    game1Sprite.setTexture(game1Texture);
    font.loadFromFile("../TLTQ/fonts/Square.ttf");

    // Load question 1 assets
    question1.setFont(font);
    question1.setCharacterSize(36);
    question1.setColor(sf::Color::Black);
    question1.setPosition(600.f, 185.f);
    question1.setString("Choose the option that is best \n"
                        "for the environment!");

    correctText1.setFont(font);
    correctText1.setCharacterSize(24);
    correctText1.setColor(sf::Color::Black);
    correctText1.setPosition(584.f, 788.f);
    correctText1.setString("That's correct! \n"
                           "Choosing to recycle is the best option for the planet! \n"
                           "Lots of things, like cans and cardboard, can be recycled \n"
                           "and made into new things! It takes less energy and less \n"
                           "resources to make products from recycled materials.");

    incorrectText1.setFont(font);
    incorrectText1.setCharacterSize(24);
    incorrectText1.setColor(sf::Color::Black);
    incorrectText1.setPosition(584.f, 788.f);
    incorrectText1.setString("That is not correct. \n"
                             "Throwing a recyclable item in the trash is not the \n"
                             "best choice for the planet. Lots of things, like cans \n"
                             "and cardboard, can be recycled and made into new things! \n"
                             "It takes less energy and less resources to make products \n"
                             "from recycled materials.");

    // Load question 2 assets
    correctText2.setFont(font);
    correctText2.setCharacterSize(24);
    correctText2.setColor(sf::Color::Black);
    correctText2.setPosition(584.f, 788.f);
    correctText2.setString("That's correct! \n"
                           "Choosing solar power, or another renewable energy source, \n"
                           "is the the best choice for the planet! Choosing solar power \n"
                           "means less greenhouse gasses, like carbon dioxide, and \n"
                           "other air pollutants.");

    incorrectText2.setFont(font);
    incorrectText2.setCharacterSize(24);
    incorrectText2.setColor(sf::Color::Black);
    incorrectText2.setPosition(584.f, 788.f);
    incorrectText2.setString("That is not correct. \n"
                             "Coal, or other fossil fuels, are not the best choice for \n"
                             "the planet. Choosing solar power means less greenhouse \n"
                             "gasses, like carbon dioxide, and other air pollutants.");
}


// Public Functions
void Game1::update(sf::RenderWindow &window, sf::Vector2i position) {
    //temp - to check that game logic progresses properly
    //std::cout << questionNumber << std::endl;

    m_position = position;

    // Click identified in left answer area
    if (position.x >= 578 && position.x <= 832 && position.y >= 460 && position.y <= 712) {
        leftAnswer = true;
        rightAnswer = false;
    }

        // Click identified in right answer area
    else if (position.x >= 1090 && position.x <= 1344 && position.y >= 460 && position.y <= 712) {
        rightAnswer = true;
        leftAnswer = false;
    }

        // Click identified on next button
    else if (position.x >= 1696 && position.x <= 1886 && position.y >= 978 && position.y <= 1052) {
        next = true;
    }

        // Click somewhere other than boxes
    else {
        // Reset click bools
        leftAnswer = false;
        rightAnswer = false;
        next = false;
    }

    //temp - for tracking mouse location to set button positions
    //std::cout << position.x << " " << position.y << std::endl;
}

void Game1::draw(sf::RenderWindow &window) {
    window.clear();

    if (questionNumber == 1) {
        window.draw(game1Sprite);
        window.draw(question1);

        // Left is correct answer
        if (leftAnswer) {
            window.draw(correctText1);
        }

            // Right is incorrect answer
        else if (rightAnswer) {
            window.draw(incorrectText1);
        }

        if (next) {
            questionNumber++;

            // Reset click bools
            leftAnswer = false;
            rightAnswer = false;
            next = false;
        }
    }

    else if (questionNumber == 2) {
        window.draw(game1Sprite);
        window.draw(question1);

        // Left is correct answer
        if (leftAnswer) {
            window.draw(correctText2);
        }

            // Right is incorrect answer
        else if (rightAnswer) {
            window.draw(incorrectText2);
        }

    }

    else {
        window.draw(game1Sprite);
    }

    window.display();
}
