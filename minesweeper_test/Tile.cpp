
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Toolbox.h"
#include "minesweeper.h"


Tile::Tile(sf::Vector2f position) {
    tilePosition = position;
    typeOfTile = 0;
    state = HIDDEN;
}

sf::Vector2f Tile::getLocation() {
    return tilePosition;
}

Tile::State Tile::getState() {
    return state;
}

std::array<Tile *, 8> &Tile::getNeighbors() {
    return neighbors;
}

void Tile::setState(Tile::State _state) {
    state = _state;
}

void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
    neighbors = _neighbors;
}

void Tile::onClickLeft() {
    Toolbox* tools = Toolbox::getInstance();
    if(tools->gameState->getPlayStatus() == GameState::PLAYING){
        if (getState() == HIDDEN){
            if (typeOfTile == -1){
                setState(EXPLODED);
                tools->gameState->setPlayStatus(GameState::LOSS);
            }
            else if (typeOfTile >= 0){
                setState(REVEALED);
                if (typeOfTile == 0){
                    revealNeighbors();
                }

                int hiddenTileCount = 0;
                for(int y = 0; y < tools->gameState->mapDimensions.y; y++) {
                    for (int x = 0; x < tools->gameState->mapDimensions.x; x++) {
                        if(tools->gameState->mapData[y][x]->getState() == HIDDEN){
                            hiddenTileCount++;
                        }
                    }
                }
                if (hiddenTileCount == tools->gameState->getMineCount()){
                    tools->gameState->setPlayStatus(GameState::WIN);
                    for(int y = 0; y < tools->gameState->mapDimensions.y; y++) {
                        for (int x = 0; x < tools->gameState->mapDimensions.x; x++) {
                            if(tools->gameState->mapData[y][x]->getState() == HIDDEN){
                                tools->gameState->mapData[y][x]->setState(FLAGGED);
                            }
                        }
                    }
                }


            }
        }
    }
}

void Tile::onClickRight() {
    Toolbox* tools = Toolbox::getInstance();
    if(tools->gameState->getPlayStatus() == GameState::PLAYING){
        if (getState() == FLAGGED){
            setState(HIDDEN);
            tools->gameState->numberOfFlags--;
        }
        else if (getState() == HIDDEN){
            setState(FLAGGED);
            tools->gameState->numberOfFlags++;
        }
    }
}

void Tile::draw() {
    Toolbox* tools = Toolbox::getInstance();

    if(getState() == HIDDEN){
        currentTileTexture.loadFromFile("images/tile_hidden.png");
        currentTileSprite.setTexture(currentTileTexture);
        currentTileSprite.setPosition(sf::Vector2f (getLocation().x * 32, getLocation().y * 32));
        tools->window.draw(currentTileSprite);
        if(getDebugMode() && typeOfTile == -1){
            currentTileTexture.loadFromFile("images/mine.png");
            currentTileSprite.setTexture(currentTileTexture);
            tools->window.draw(currentTileSprite);
        }
    }
    else if(getState() == REVEALED){
        currentTileTexture.loadFromFile("images/tile_revealed.png");
        currentTileSprite.setTexture(currentTileTexture);
        currentTileSprite.setPosition(getLocation().x * 32, getLocation().y * 32);
        tools->window.draw(currentTileSprite);
        switch (typeOfTile){
            case 0:
                break;
            case 1:
                currentTileTexture.loadFromFile("images/number_1.png");
                currentTileSprite.setTexture(currentTileTexture);
                tools->window.draw(currentTileSprite);
                break;
            case 2:
                currentTileTexture.loadFromFile("images/number_2.png");
                currentTileSprite.setTexture(currentTileTexture);
                tools->window.draw(currentTileSprite);
                break;
            case 3:
                currentTileTexture.loadFromFile("images/number_3.png");
                currentTileSprite.setTexture(currentTileTexture);
                tools->window.draw(currentTileSprite);
                break;
            case 4:
                currentTileTexture.loadFromFile("images/number_4.png");
                currentTileSprite.setTexture(currentTileTexture);
                tools->window.draw(currentTileSprite);
                break;
            case 5:
                currentTileTexture.loadFromFile("images/number_5.png");
                currentTileSprite.setTexture(currentTileTexture);
                tools->window.draw(currentTileSprite);
                break;
            case 6:
                currentTileTexture.loadFromFile("images/number_6.png");
                currentTileSprite.setTexture(currentTileTexture);
                tools->window.draw(currentTileSprite);
                break;
            case 7:
                currentTileTexture.loadFromFile("images/number_7.png");
                currentTileSprite.setTexture(currentTileTexture);
                tools->window.draw(currentTileSprite);
                break;
            case 8:
                currentTileTexture.loadFromFile("images/number_8.png");
                currentTileSprite.setTexture(currentTileTexture);
                tools->window.draw(currentTileSprite);
                break;
            default:
                break;
        };

    }
    else if(getState() == EXPLODED){
        currentTileTexture.loadFromFile("images/tile_revealed.png");
        currentTileSprite.setTexture(currentTileTexture);
        currentTileSprite.setPosition(getLocation().x * 32, getLocation().y * 32);
        tools->window.draw(currentTileSprite);
        currentTileTexture.loadFromFile("images/mine.png");
        currentTileSprite.setTexture(currentTileTexture);
        tools->window.draw(currentTileSprite);
    }
    else if(getState() == FLAGGED){
        currentTileTexture.loadFromFile("images/tile_hidden.png");
        currentTileSprite.setTexture(currentTileTexture);
        currentTileSprite.setPosition(getLocation().x * 32, getLocation().y * 32);
        tools->window.draw(currentTileSprite);
        currentTileTexture.loadFromFile("images/flag.png");
        currentTileSprite.setTexture(currentTileTexture);
        tools->window.draw(currentTileSprite);
    }
}

void Tile::revealNeighbors() {
    for(Tile* neighbor : neighbors){
        if(neighbor != nullptr){
            if(neighbor->typeOfTile != -1){
                /// DEBUG
                neighbor->onClickLeft();
            }
        }
    }
}
