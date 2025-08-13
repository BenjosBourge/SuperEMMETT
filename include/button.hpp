/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#include <string>

class Button {
public:
    Button(int x, int y, int width, int height, std::string label);
    bool isPressed(int mouseX, int mouseY);

    int _x;
    int _y;
    int _width;
    int _height;
    std::string _label;

    void (*_click)() = nullptr; // Pointer to a function to call when the button is clicked
};