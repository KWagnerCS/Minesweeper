
#include <SFML/Graphics.hpp>
#pragma once

class Tile {
public:
    enum State {REVEALED, HIDDEN, FLAGGED, EXPLODED};   // Visual state
    Tile(sf::Vector2f position);                        // Constructor
    sf::Vector2f getLocation();                         // Returns location
    State getState();                                   // Returns state
    std::array<Tile*, 8>& getNeighbors();               // Returns pointer to array of Tile pointers
    void setState(State _state);                        // Sets state and updates visuals
    void setNeighbors(std::array<Tile*, 8> _neighbors); // Sets neighbors
    void onClickLeft();
    void onClickRight();
    void draw();
protected:
    void revealNeighbors();

private:
    std::array<Tile*, 8> neighbors;
    State state;                 // Visual state of tile
    int typeOfTile;              // -1: Mine, 0-8: Number of surrounding mines
    sf::Vector2f tilePosition;   // Position as Vector2f
    sf::Sprite currentTileSprite;
    sf::Texture currentTileTexture;

    friend class GameState;
};
