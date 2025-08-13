
#include <iostream>
#include <SFML/Graphics.hpp>
#include <code.hpp>
#include <button.hpp>
#include <ram.hpp>

Code code;
Ram ram;

class Mouse {
public:
    Mouse()
    {
        _pressed = false;
        _clicked = false;
    }

    ~Mouse() = default;

    int x = 0;
    int y = 0;

    void update(sf::RenderWindow &window) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        x = position.x;
        y = position.y;

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

    bool _pressed;
    bool _clicked;
};

void addLine()
{
    code.addLine();
}

void removeLine()
{
    code.removeLine();
}

void compileCode()
{
    int pc = 0;
    for (int i = 0; i < ram._memorySize; ++i)
        ram._memory[i] = 0;
    for (auto &l : code._lines) {
        ram._memory[pc] = 1; // Example operation: set memory at pc to 1
        pc++;
    }
}

int main()
{
    std::cout << "SuperEMMETT started." << std::endl;

    sf::RenderWindow window(sf::VideoMode(1600, 900), "SuperEMMETT");
    sf::RectangleShape rectangle(sf::Vector2f(100, 20));
    rectangle.setFillColor({250, 250, 250});
    rectangle.setPosition(100, 100);

    Button addLine_button(1400, 800, 50, 30, "+");
    addLine_button._click = addLine;
    Button removeLine_button(1460, 800, 50, 30, "-");
    removeLine_button._click = removeLine;
    Button compile_button(1520, 800, 80, 30, "C");
    compile_button._click = compileCode;

    std::vector<Button> buttons;
    buttons.push_back(addLine_button);
    buttons.push_back(removeLine_button);
    buttons.push_back(compile_button);

    sf::Font font;
    if (!font.loadFromFile("assets/RifficFree-Bold.ttf"))
        return -1;

    Mouse mouse;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        mouse.update(window);

        for (auto &button : buttons)
        {
            if (button.isPressed(mouse.x, mouse.y) && mouse._clicked)
            {
                if (button._click) {
                    button._click(); // Call the function associated with the button
                }
            }
        }

        window.clear();

        //draw the RAM
        rectangle.setFillColor({90, 90, 90});
        rectangle.setSize(sf::Vector2f(10, 10));

        int ram_number = 1000;
        int number_of_col = 50; // 10 rows
        for (int i = 0; i < ram_number; ++i)
        {
            int x = i % number_of_col; // 100 columns
            int y = i / number_of_col; // 10 rows
            rectangle.setPosition(100 + x * 15, 100 + y * 15);
            if (ram._memory[i] == 1)
                rectangle.setFillColor({250, 250, 250});
            else
                rectangle.setFillColor({90, 90, 90});
            window.draw(rectangle);
        }

        // draw the lines
        rectangle.setFillColor({250, 250, 250});
        rectangle.setSize(sf::Vector2f(100, 20));
        int offset = 0;
        for (auto &l : code._lines)
        {
            rectangle.setPosition(1400, 100 + offset);
            window.draw(rectangle);
            offset += 30; // Increment offset for each line
        }

        // draw the buttons
        for (auto &button : buttons)
        {
            sf::RectangleShape buttonShape(sf::Vector2f(button._width, button._height));
            buttonShape.setPosition(button._x, button._y);
            buttonShape.setFillColor(sf::Color(200, 200, 200));
            window.draw(buttonShape);

            // Draw the label
            sf::Text text(button._label, font, 20);
            text.setFillColor(sf::Color::Black);
            text.setPosition(button._x + 10, button._y + 5);
            window.draw(text);
        }


        window.display();
    }
}