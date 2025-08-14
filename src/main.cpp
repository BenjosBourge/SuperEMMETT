
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
    emmett->_compiler->compile(emmett->_code->_lines);
}

void runCode(std::shared_ptr<Emmett> emmett)
{
    emmett->_run = !emmett->_run;

    if (emmett->_run) {
        emmett->_cpu->reset();
        emmett->_timer = 0.5f;
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
    Button run_button(200, 800, 100, 40, "Run");
    run_button._click = runCode;


    std::vector<Button> buttons;
    buttons.push_back(addLine_button);
    buttons.push_back(removeLine_button);
    buttons.push_back(compile_button);
    buttons.push_back(run_button);

    sf::Font font;
    if (!font.loadFromFile("assets/RifficFree-Bold.ttf"))
        return -1;

    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        emmett->_mouse.update(window);
        emmett->update(deltaTime);

        for (auto &button : buttons)
            if (button.isPressed(emmett->_mouse._x, emmett->_mouse._y) && emmett->_mouse._clicked)
                if (button._click)
                    button._click(emmett);

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
            if (emmett->_ram->_memory[i] != 0) {
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
        rectangle.setSize(sf::Vector2f(160, 40));
        int offset = 0;
        for (auto &l : emmett->_code->_lines)
        {
            rectangle.setPosition(1350, 100 + offset);
            window.draw(rectangle);
            sf::Text text(l._text, font, 20);
            text.setFillColor(sf::Color::Black);
            text.setPosition(1350 + 10, 100 + offset + 5);
            window.draw(text);
            offset += 50; // Increment offset for each line
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

        // draw Cpu
        rectangle.setFillColor({155, 89, 182});
        rectangle.setSize(sf::Vector2f(360, 160));
        rectangle.setPosition(100, 600);
        window.draw(rectangle);

        // register
        rectangle.setFillColor({90, 90, 90});
        rectangle.setSize(sf::Vector2f(30, 30));
        for (int i = 0; i < emmett->_cpu->_registers.size(); i += 1)
        {
            rectangle.setPosition(380 + (i / 4) * 35, 610 + (i % 4) * 35 + 2);
            window.draw(rectangle);

            if (emmett->_cpu->_registers[i] != 0) {
                std::string hex = std::format("{:02X}", emmett->_cpu->_registers[i]);
                sf::Text text(hex, font, 17);
                text.setFillColor(sf::Color::Black);
                text.setPosition(380 + (i / 4) * 35 + 2, 610 + (i % 4) * 35 + 7);
                window.draw(text);
            }
        }

        // X and Y
        rectangle.setSize(sf::Vector2f(60, 60));
        rectangle.setPosition(300, 615);
        if (emmett->_cpu->_x == 0)
            rectangle.setFillColor({90, 90, 90});
        else
            rectangle.setFillColor({155, 155, 155});
        window.draw(rectangle);
        if (emmett->_cpu->_x != 0) {
            std::string hex = std::format("{:02X}", emmett->_cpu->_x);
            sf::Text text(hex, font, 32);
            text.setFillColor(sf::Color::Black);
            text.setPosition(300 + 5, 615 + 10);
            window.draw(text);
        }

        window.draw(rectangle);
        rectangle.setPosition(300, 685);
        if (emmett->_cpu->_y == 0)
            rectangle.setFillColor({90, 90, 90});
        else
            rectangle.setFillColor({155, 155, 155});
        window.draw(rectangle);
        if (emmett->_cpu->_y != 0) {
            std::string hex = std::format("{:02X}", emmett->_cpu->_y);
            sf::Text text(hex, font, 32);
            text.setFillColor(sf::Color::Black);
            text.setPosition(300 + 5, 685 + 10);
            window.draw(text);
        }

        // Accumulator
        rectangle.setSize(sf::Vector2f(120, 120));
        rectangle.setPosition(170, 620);
        if (emmett->_cpu->_a == 0)
            rectangle.setFillColor({90, 90, 90});
        else
            rectangle.setFillColor({155, 155, 155});
        window.draw(rectangle);
        if (emmett->_cpu->_a != 0) {
            std::string hex = std::format("{:02X}", emmett->_cpu->_a);
            sf::Text text(hex, font, 48);
            text.setFillColor(sf::Color::Black);
            text.setPosition(170 + 25, 620 + 30);
            window.draw(text);
        }

        // pc
        rectangle.setSize(sf::Vector2f(55, 30));
        rectangle.setPosition(108, 615);
        rectangle.setFillColor({155, 155, 155});
        window.draw(rectangle);
        std::string hex = std::format("{:04X}", emmett->_cpu->_pc);
        sf::Text text(hex, font, 15);
        text.setFillColor(sf::Color::Black);
        text.setPosition(110 + 2, 615 + 5);
        window.draw(text);

        rectangle.setSize(sf::Vector2f(45, 45));
        rectangle.setPosition(108, 650);
        rectangle.setFillColor({155, 155, 155});
        window.draw(rectangle);
        hex = std::format("{:02X}", emmett->_ram->_memory[emmett->_cpu->_pc]);
        text.setString(hex);
        text.setCharacterSize(21);
        text.setFillColor(sf::Color::Black);
        text.setPosition(110 + 5, 650 + 10);
        window.draw(text);

        window.display();
    }
}