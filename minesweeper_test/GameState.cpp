
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <fstream>
#include <iostream>
#include <experimental/random>
#include <string>

GameState::GameState(sf::Vector2i dimensions, int _numberOfMines) {
    mapDimensions = dimensions;
    numberOfMines = 0;
    numberOfFlags = 0;
    status = PLAYING;
    for(int y = 0; y < dimensions.y; y++){
        std::vector<Tile*> temp(dimensions.x);
        mapData.push_back(temp);
        for(int x = 0; x < dimensions.x; x++){
            mapData[y][x] = new Tile(sf::Vector2f(x,y));
        }
    }
    while(numberOfMines < _numberOfMines){
        int randomX = std::experimental::randint(0, dimensions.x - 1);
        int randomY = std::experimental::randint(0, dimensions.y - 1);
        if(mapData[randomY][randomX]->typeOfTile != -1){
            mapData[randomY][randomX]->typeOfTile = -1;
            numberOfMines++;
        }
    }

    /// set the numbers
}

GameState::GameState(const char *filePath) {
    mapDimensions = sf::Vector2i(25, 16);
    char tempRead;
    int tempType;
    numberOfMines = 0;
    numberOfFlags = 0;
    status = PLAYING;
    std::ifstream file;
    file.open(filePath, std::ios::in);
    for(int y = 0; y < 16; y++){
        std::vector<Tile*> temp(25);
        mapData.push_back(temp);
        for(int x = 0; x < 25; x++){
            file >> tempRead;
            if ((int)tempRead - 48 == 1){
                tempType = -1;
            }
            else{
                tempType = 0;
            }
            mapData[y][x] = new Tile(sf::Vector2f(x,y));
            mapData[y][x]->typeOfTile = tempType;
            if(mapData[y][x]->typeOfTile == -1){
                numberOfMines++;
            }
        }
    }
    file.close();

    /// set the numbers()
}

int GameState::getFlagCount() {
    return numberOfFlags;
}

int GameState::getMineCount() {
    return numberOfMines;
}

sf::Vector2i GameState::getMapDimensions() {
    return mapDimensions;
}

Tile *GameState::getTile(int x, int y) {
    return mapData[y][x];
}

GameState::PlayStatus GameState::getPlayStatus() {
    return status;
}

void GameState::setPlayStatus(GameState::PlayStatus _status) {
    status = _status;
}

GameState::~GameState() {
    for(int y = 0; y < mapDimensions.y; y++){
        for(int x = 0; x < mapDimensions.x; x++){
            delete mapData[y][x];
        }
    }
}