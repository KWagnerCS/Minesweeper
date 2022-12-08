
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
#pragma once

class GameState {
public:
    enum PlayStatus{WIN, LOSS, PLAYING};
    GameState(sf::Vector2i dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filePath);
    int getFlagCount();
    int getMineCount();
    sf::Vector2i getMapDimensions();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
    ~GameState();
private:
    sf::Vector2i mapDimensions;
    PlayStatus status;
    int numberOfMines;
    int numberOfFlags;
    std::vector<std::vector<Tile*>> mapData;

    friend class Tile;
};