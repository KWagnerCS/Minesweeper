
#include "Button.h"
#include <SFML/Graphics.hpp>

Button::Button(sf::Vector2f _position, std::function<void()> onClick) {
    position = _position;
    onClickFunction = onClick;
}

sf::Vector2f Button::getPosition() {
    return position;
}

sf::Sprite *Button::getSprite() {
    return sprite;
}

void Button::setSprite(sf::Sprite *_sprite) {
    sprite = _sprite;
}

void Button::onClick() {
    onClickFunction();
}