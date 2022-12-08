
#include <SFML/Graphics.hpp>
#include <functional>
#pragma once

class Button {
public:
    Button(sf::Vector2f _position, std::function<void(void)> onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
private:
    std::function<void(void)> onClickFunction;
    sf::Vector2f position;
    sf::Sprite* sprite;
};
