#include "Game1.h"
#include <iostream>

Game1Question::Game1Question(std::string correct, std::string incorrect, sf::Font font, int fontSize,
                             sf::Vector2f pos) {
    correctText.setString(correct);
    correctText.setFont(font);
    correctText.setCharacterSize(fontSize);
    correctText.setColor(sf::Color::Black);
    correctText.setPosition(pos.x, pos.y);

    incorrectText.setString(incorrect);
    incorrectText.setFont(font);
    incorrectText.setCharacterSize(fontSize);
    incorrectText.setColor(sf::Color::Black);
    incorrectText.setPosition(pos.x, pos.y);
}


// Constructor
Game1::Game1() {
    // Set default values
    questionNumber = 1;
    questionFontSize = 36;
    answerFontSize = 24;
    questionPos.x = 600.f;
    questionPos.y = 185.f;
    answerPos.x = 584.f;
    answerPos.y = 788.f;

    questionResponse = false;
    leftAnswer = false;

    game1Texture.loadFromFile("./graphics/climateStompersInGame.png");
    game1Sprite.setTexture(game1Texture);
    font.loadFromFile("./fonts/Square.ttf");

    // Set main questions assests
    question.setFont(font);
    question.setCharacterSize(questionFontSize);
    question.setColor(sf::Color::Black);
    question.setPosition(questionPos.x, questionPos.y);
    question.setString("Choose the option that is best \n"
                        "for the environment!");

    // Load question 1 assets
    correctTemp = "That's correct! \n"
                           "Choosing to recycle is the best option for the planet! \n"
                           "Lots of things, like cans and cardboard, can be recycled \n"
                           "and made into new things! It takes less energy and less \n"
                           "resources to make products from recycled materials.";
    incorrectTemp = "That is not correct. \n"
                             "Throwing a recyclable item in the trash is not the \n"
                             "best choice for the planet. Lots of things, like cans \n"
                             "and cardboard, can be recycled and made into new things! \n"
                             "It takes less energy and less resources to make products \n"
                             "from recycled materials.";
    questions.push_back(Game1Question(correctTemp, incorrectTemp, font, answerFontSize, answerPos));

    // Load question 2 assets
    correctTemp = "That's correct! \n"
                           "Choosing solar power, or another renewable energy source, \n"
                           "is the the best choice for the planet! Choosing solar power \n"
                           "means less greenhouse gasses, like carbon dioxide, and \n"
                           "other air pollutants.";
    incorrectTemp = "That is not correct. \n"
                             "Coal, or other fossil fuels, are not the best choice for \n"
                             "the planet. Choosing solar power means less greenhouse \n"
                             "gasses, like carbon dioxide, and other air pollutants.";
    questions.push_back(Game1Question(correctTemp, incorrectTemp, font, answerFontSize, answerPos));
/*
    correctText1.setFont(font);
    correctText1.setCharacterSize(answerFontSize);
    correctText1.setColor(sf::Color::Black);
    correctText1.setPosition(answerPos.x, answerPos.y);
    correctText1.setString("That's correct! \n"
                           "Choosing to recycle is the best option for the planet! \n"
                           "Lots of things, like cans and cardboard, can be recycled \n"
                           "and made into new things! It takes less energy and less \n"
                           "resources to make products from recycled materials.");

    incorrectText1.setFont(font);
    incorrectText1.setCharacterSize(answerFontSize);
    incorrectText1.setColor(sf::Color::Black);
    incorrectText1.setPosition(answerPos.x, answerPos.y);
    incorrectText1.setString("That is not correct. \n"
                             "Throwing a recyclable item in the trash is not the \n"
                             "best choice for the planet. Lots of things, like cans \n"
                             "and cardboard, can be recycled and made into new things! \n"
                             "It takes less energy and less resources to make products \n"
                             "from recycled materials.");


    // Load question 2 assets
    correctText2.setFont(font);
    correctText2.setCharacterSize(answerFontSize);
    correctText2.setColor(sf::Color::Black);
    correctText2.setPosition(answerPos.x, answerPos.y);
    correctText2.setString("That's correct! \n"
                           "Choosing solar power, or another renewable energy source, \n"
                           "is the the best choice for the planet! Choosing solar power \n"
                           "means less greenhouse gasses, like carbon dioxide, and \n"
                           "other air pollutants.");

    incorrectText2.setFont(font);
    incorrectText2.setCharacterSize(answerFontSize);
    incorrectText2.setColor(sf::Color::Black);
    incorrectText2.setPosition(answerPos.x, answerPos.y);
    incorrectText2.setString("That is not correct. \n"
                             "Coal, or other fossil fuels, are not the best choice for \n"
                             "the planet. Choosing solar power means less greenhouse \n"
                             "gasses, like carbon dioxide, and other air pollutants.");
*/
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
        window.draw(question);

        // Left is correct answer
        if (leftAnswer) {
            //window.draw(correctText1);
            //window.draw(questions[0].correctText);
        }

            // Right is incorrect answer
        else if (rightAnswer) {
            //window.draw(incorrectText1);
            //window.draw(questions[0].incorrectText);
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
        window.draw(question);

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
