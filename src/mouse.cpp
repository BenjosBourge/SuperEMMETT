
#include <iostream>
#include <SFML/Graphics.hpp>
#include <mouse.hpp>

void Mouse::update(sf::RenderWindow &window) {
    sf::Vector2i position = sf::Mouse::getPosition(window);
    _x = position.x;
    _y = position.y;

    _clicked = false;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!_pressed) {
            _clicked = true;
        }
        _pressed = true;
    } else {
        _pressed = false;
    }
}