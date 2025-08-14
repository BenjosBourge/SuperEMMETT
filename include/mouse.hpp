/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Mouse {
public:
    Mouse()
    {
        _pressed = false;
        _clicked = false;
    }

    ~Mouse() = default;

    int _x = 0;
    int _y = 0;

    void update(sf::RenderWindow &window);

    bool _pressed;
    bool _clicked;
};
