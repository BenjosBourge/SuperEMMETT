/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once
#include <string>
#include <memory>

class Emmett;

class Button {
public:
    Button(int x, int y, int width, int height, std::string label);
    bool isPressed(int mouseX, int mouseY);

    int _x;
    int _y;
    int _width;
    int _height;
    std::string _label;

    void (*_click)(std::shared_ptr<Emmett> emmett) = nullptr; // Pointer to a function to call when the button is clicked
};