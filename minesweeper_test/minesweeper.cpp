
#include <SFML/Graphics.hpp>
#include "minesweeper.h"
#include "Toolbox.h"
#include <iostream>

bool debugMode;

int launch(){
    Toolbox* tools = Toolbox::getInstance();
    debugMode = false;
    tools->debugButton = new Button(sf::Vector2f(496,512), toggleDebugMode);
    tools->newGameButton = new Button(sf::Vector2f(368,512), restart);
    gameLoop();

    return 0;
}

int gameLoop(){
    Toolbox* tools = Toolbox::getInstance();

    render();
    tools->window.display();
    while(tools->window.isOpen()) {
        tools->window.clear();
        sf::Event event{};
        while (tools->window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                tools->window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mouseX = (float)event.mouseButton.x;
                auto mouseY = (float)event.mouseButton.y;

                if (mouseX >= 0 && mouseX < (float)tools->gameState->getMapDimensions().x * 32 &&
                    mouseY >= 0 && mouseY < (float)tools->gameState->getMapDimensions().y * 32) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        tools->gameState->getTile((int)mouseX / 32, (int)mouseY / 32)->onClickLeft();
                    }

                    if (event.mouseButton.button == sf::Mouse::Right) {
                        tools->gameState->getTile((int)mouseX / 32, (int)mouseY / 32)->onClickRight();
                    }
                }

                if (mouseX >= tools->newGameButton->getPosition().x && mouseX < tools->newGameButton->getPosition().x + 64 &&
                    mouseY >= tools->newGameButton->getPosition().y && mouseY < tools->newGameButton->getPosition().y + 64) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        tools->newGameButton->onClick();

                        /// DEBUG
                        std::cout << "Reset game" << std::endl;
                    }
                }

                if (mouseX >= tools->debugButton->getPosition().x && mouseX < tools->debugButton->getPosition().x + 64 &&
                    mouseY >= tools->debugButton->getPosition().y && mouseY < tools->debugButton->getPosition().y + 64) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        tools->debugButton->onClick();

                        /// DEBUG
                        std::cout << "Loaded test 1" << std::endl;
                    }
                }

                if (mouseX >= tools->testButton1->getPosition().x && mouseX < tools->testButton1->getPosition().x + 64 &&
                    mouseY >= tools->testButton1->getPosition().y && mouseY < tools->testButton1->getPosition().y + 64) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        tools->testButton1->onClick();

                        /// DEBUG
                        std::cout << "Loaded test 1" << std::endl;
                    }
                }

                if (mouseX >= tools->testButton2->getPosition().x && mouseX < tools->testButton2->getPosition().x + 64 &&
                    mouseY >= tools->testButton2->getPosition().y && mouseY < tools->testButton2->getPosition().y + 64) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        tools->testButton2->onClick();

                        /// DEBUG
                        std::cout << "Loaded test 2" << std::endl;
                    }
                }



                /// ON LOSS
                if(tools->gameState->getPlayStatus() == GameState::LOSS){
                    std::cout << "YOU LOST";
                }

                /// CURRENTLY RENDERS AND DISPLAYS ON MOUSE EVENT
                render();
                tools->window.display();
            }


        }
    }
    return 0;
}

void render(){
    Toolbox* tools = Toolbox::getInstance();
    for(int y = 0; y < tools->gameState->getMapDimensions().y; y++){
        for(int x = 0; x < tools->gameState->getMapDimensions().x; x++){
            tools->gameState->getTile(x,y)->draw();
        }
    }

    auto *buttonTexture = new sf::Texture;
    auto *buttonSprite = new sf::Sprite;

    if(tools->gameState->getPlayStatus() == GameState::PLAYING){
        buttonTexture->loadFromFile("images/face_happy.png");
    }
    else if(tools->gameState->getPlayStatus() == GameState::LOSS){
        buttonTexture->loadFromFile("images/face_lose.png");
    }
    else if(tools->gameState->getPlayStatus() == GameState::WIN){
        buttonTexture->loadFromFile("images/face_happy.png");
    }
    buttonSprite->setTexture(*buttonTexture);
    tools->newGameButton->setSprite(buttonSprite);
    tools->newGameButton->getSprite()->setPosition(tools->newGameButton->getPosition());
    tools->window.draw(*tools->newGameButton->getSprite());

    buttonTexture->loadFromFile("images/debug.png");
    buttonSprite->setTexture(*buttonTexture);
    tools->debugButton->setSprite(buttonSprite);
    tools->debugButton->getSprite()->setPosition(tools->debugButton->getPosition());
    tools->window.draw(*tools->debugButton->getSprite());

    buttonTexture->loadFromFile("images/test_1.png");
    buttonSprite->setTexture(*buttonTexture);
    tools->testButton1->setSprite(buttonSprite);
    tools->testButton1->getSprite()->setPosition(tools->testButton1->getPosition());
    tools->window.draw(*tools->testButton1->getSprite());

    buttonTexture->loadFromFile("images/test_2.png");
    buttonSprite->setTexture(*buttonTexture);
    tools->testButton2->setSprite(buttonSprite);
    tools->testButton2->getSprite()->setPosition(tools->testButton2->getPosition());
    tools->window.draw(*tools->testButton2->getSprite());


    /// MINE COUNT DIGITS DISPLAY
    sf::Texture digitTexture;
    digitTexture.loadFromFile("images/digits.png");
    sf::Sprite digitSpriteArray[11];
    for(int i = 0; i < 11; i++){
        digitSpriteArray[i].setTexture(digitTexture);
        digitSpriteArray[i].setTextureRect(sf::IntRect(i*21,0,21,32));
    }

    int digitArray[3];
    digitArray[0] = abs(((tools->gameState->getMineCount() - tools->gameState->getFlagCount()) / 100) % 10);
    digitArray[1] = abs(((tools->gameState->getMineCount() - tools->gameState->getFlagCount()) / 10) % 10);
    digitArray[2] = abs((tools->gameState->getMineCount() - tools->gameState->getFlagCount()) % 10);

    if((tools->gameState->getMineCount() - tools->gameState->getFlagCount()) < 0){
        digitSpriteArray[10].setPosition(sf::Vector2f(0,512));
        tools->window.draw(digitSpriteArray[10]);
        digitSpriteArray[digitArray[1]].setPosition(sf::Vector2f(21,512));
        tools->window.draw(digitSpriteArray[digitArray[1]]);
        digitSpriteArray[digitArray[2]].setPosition(sf::Vector2f(42,512));
        tools->window.draw(digitSpriteArray[digitArray[2]]);
    }
    else {
        digitSpriteArray[digitArray[0]].setPosition(sf::Vector2f(0,512));
        tools->window.draw(digitSpriteArray[digitArray[0]]);
        digitSpriteArray[digitArray[1]].setPosition(sf::Vector2f(21,512));
        tools->window.draw(digitSpriteArray[digitArray[1]]);
        digitSpriteArray[digitArray[2]].setPosition(sf::Vector2f(42,512));
        tools->window.draw(digitSpriteArray[digitArray[2]]);
    }

    /// DEALLOCATE
    delete buttonTexture;
    delete buttonSprite;
}

void restart(){
    Toolbox* tools = Toolbox::getInstance();
    debugMode = false;
    delete tools->gameState;
    tools->gameState = new GameState();
}

void toggleDebugMode(){
    debugMode = !debugMode;
}

bool getDebugMode(){
    return debugMode;
}

int main() {return launch();} // Invokes launch