
#include <button.hpp>

Button::Button(int x, int y, int width, int height, std::string label)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _label = label;
}

bool Button::isPressed(int mouseX, int mouseY)
{
    return (mouseX >= _x && mouseX <= _x + _width &&
            mouseY >= _y && mouseY <= _y + _height);
}