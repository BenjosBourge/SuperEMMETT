
#include <iostream>
#include <SFML/Graphics.hpp>
#include <format>
#include <button.hpp>
#include <emmett.hpp>

void addLine(std::shared_ptr<Emmett> emmett)
{
    emmett->_code->addLine();
}

void removeLine(std::shared_ptr<Emmett> emmett)
{
    emmett->_code->removeLine();
}

void compileCode(std::shared_ptr<Emmett> emmett)
{
    int pc = 0;
    for (int i = 0; i < emmett->_ram->_memorySize; ++i)
        emmett->_ram->_memory[i] = 0;
    for (auto &l : emmett->_code->_lines) {
        emmett->_ram->_memory[pc] = 1; // Example operation: set memory at pc to 1
        pc++;
    }
}

int main()
{
    std::shared_ptr<Emmett> emmett = std::make_shared<Emmett>();

    sf::RenderWindow window(sf::VideoMode(1600, 900), "SuperEMMETT");
    sf::RectangleShape rectangle(sf::Vector2f(100, 20));
    rectangle.setFillColor({250, 250, 250});
    rectangle.setPosition(100, 100);

    Button addLine_button(1340, 800, 50, 30, "+");
    addLine_button._click = addLine;
    Button removeLine_button(1400, 800, 50, 30, "-");
    removeLine_button._click = removeLine;
    Button compile_button(1460, 800, 50, 30, "C");
    compile_button._click = compileCode;

    std::vector<Button> buttons;
    buttons.push_back(addLine_button);
    buttons.push_back(removeLine_button);
    buttons.push_back(compile_button);

    sf::Font font;
    if (!font.loadFromFile("assets/RifficFree-Bold.ttf"))
        return -1;

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

        emmett->_mouse.update(window);

        for (auto &button : buttons)
        {
            if (button.isPressed(emmett->_mouse._x, emmett->_mouse._y) && emmett->_mouse._clicked)
            {
                if (button._click) {
                    button._click(emmett);
                }
            }
        }

        window.clear();

        //draw the RAM
        rectangle.setFillColor({90, 90, 90});
        rectangle.setSize(sf::Vector2f(25, 25));

        int ram_number = emmett->_ram->_memorySize;
        int number_of_col = 32; // 10 rows
        for (int i = 0; i < ram_number; ++i)
        {
            int x = i % number_of_col; // 100 columns
            int y = i / number_of_col; // 10 rows
            rectangle.setPosition(100 + x * 30, 100 + y * 30);
            if (emmett->_ram->_memory[i] == 1) {
                rectangle.setFillColor({250, 250, 250});
            } else
                rectangle.setFillColor({90, 90, 90});
            window.draw(rectangle);

            if (emmett->_ram->_memory[i] != 0) {
                std::string hex = std::format("{:02X}", emmett->_ram->_memory[i]);
                sf::Text text(hex, font, 15);
                text.setFillColor(sf::Color::Black);
                text.setPosition(100 + x * 30 + 2, 100 + y * 30 + 5);
                window.draw(text);
            }
        }

        // draw the lines
        rectangle.setFillColor({250, 250, 250});
        rectangle.setSize(sf::Vector2f(100, 20));
        int offset = 0;
        for (auto &l : emmett->_code->_lines)
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