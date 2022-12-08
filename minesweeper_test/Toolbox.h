#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"
#pragma once

class Toolbox {
    Toolbox();
    static Toolbox *instance;

    // define copy assigner
    Toolbox(Toolbox &another) = delete; // non copy-able
    void operator= (const Toolbox&) = delete; // non assignable

public:
    static Toolbox *getInstance();

    sf::RenderWindow window; // SFML application window
    GameState* gameState;    // Primary game state representation
    Button* debugButton;     // Reveals mines in debug mode
    Button* newGameButton;   // Resets / starts new game
    Button* testButton1;     // Loads test board #1
    Button* testButton2;     // Loads test board #2
};

