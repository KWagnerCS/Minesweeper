
#include "Toolbox.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Toolbox::Toolbox() {
    window.create(sf::VideoMode(800,600), "P4 - Minesweeper, Kevin Wagner");
    gameState = new GameState();

    auto testButton1F = [&](){delete gameState; gameState = new GameState("boards/testboard1.brd");};
    testButton1 = new Button(sf::Vector2f(560,512), testButton1F);

    auto testButton2F = [&](){delete gameState; gameState = new GameState("boards/testboard2.brd");};
    testButton2 = new Button(sf::Vector2f(624,512), testButton2F);
}

Toolbox* Toolbox::instance = nullptr;

Toolbox* Toolbox::getInstance() {
    if (instance == nullptr){
        instance = new Toolbox();
    }
    return instance;
}