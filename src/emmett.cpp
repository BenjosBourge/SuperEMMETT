
#include <iostream>
#include <SFML/Graphics.hpp>
#include <emmett.hpp>
#include <format>

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

Emmett::Emmett()
{
    _ram = std::make_shared<Ram>();
    _cpu = std::make_shared<Cpu>();
    _compiler = std::make_shared<Compiler>();
    _code = std::make_shared<Code>();

    if (!_font.loadFromFile("assets/RifficFree-Bold.ttf"))
        std::cerr << "Error loading font!" << std::endl;

    _ram->_cpu = _cpu;
    _compiler->_ram = _ram;
    _cpu->_ram = _ram;

    _run = false;
    _timer = 0.0f;

    // Initialize buttons
    Button addLine_button(1340, 800, 50, 30, "+");
    addLine_button._click = addLine;
    Button removeLine_button(1400, 800, 50, 30, "-");
    removeLine_button._click = removeLine;
    Button compile_button(1460, 800, 50, 30, "C");
    compile_button._click = compileCode;
    Button run_button(200, 800, 100, 40, "Run");
    run_button._click = runCode;

    _buttons.push_back(addLine_button);
    _buttons.push_back(removeLine_button);
    _buttons.push_back(compile_button);
    _buttons.push_back(run_button);
}

Emmett::~Emmett()
{

}

void Emmett::update(float deltaTime, std::shared_ptr<Emmett> emmett)
{
    for (auto &button : _buttons)
        if (button.isPressed(_mouse._x, _mouse._y) && _mouse._clicked)
            if (button._click)
                button._click(emmett);

    int offset = 0;
    int index = 0;
    for (auto &line : _code->_lines) {
        if (_mouse._x >= 1350 && _mouse._x <= 1510 &&
                _mouse._y >= 100 + offset && _mouse._y <= 140 + offset &&
            _mouse._clicked) {

            if (_mouse._x >= 1420 && _mouse._x <= 1460 &&
                _mouse._y >= 102 + offset && _mouse._y <= 138 + offset &&
                _mouse._clicked) {
                int new_index_mode = (line._indexModeIndex + 1) % line._indexModes.size();
                line._indexModeIndex = new_index_mode;
                line._indexModeType = line._indexModes[new_index_mode];
                break;
            }
            std::cout << "Clicked on line: " << line._text << " " << index << std::endl;
        }
        offset += 50;
        index += 1;
    }

    if (_run) {
        _timer -= deltaTime;
        if (_timer <= 0.0f) {
            _cpu->fetch();
            _timer = 0.5f;
        }
    }
}

void Emmett::draw(sf::RenderWindow &window)
{
    window.clear();

    draw_ram(window);
    draw_code(window);
    draw_cpu(window);

    // draw the buttons
    for (auto &button : _buttons)
    {
        sf::RectangleShape buttonShape(sf::Vector2f(button._width, button._height));
        buttonShape.setPosition(button._x, button._y);
        buttonShape.setFillColor(sf::Color(200, 200, 200));
        window.draw(buttonShape);

        // Draw the label
        sf::Text text(button._label, _font, 20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(button._x + 10, button._y + 5);
        window.draw(text);
    }
    window.display();
}

void Emmett::draw_ram(sf::RenderWindow &window)
{
    //draw the RAM
    sf::RectangleShape rectangle(sf::Vector2f(25, 25));
    rectangle.setPosition(100, 100);
    rectangle.setFillColor({90, 90, 90});

    int ram_number = _ram->_memorySize;
    int number_of_col = 32; // 10 rows
    for (int i = 0; i < ram_number; ++i)
    {
        int x = i % number_of_col; // 100 columns
        int y = i / number_of_col; // 10 rows
        rectangle.setPosition(100 + x * 30, 100 + y * 30);
        if (_ram->_memory[i] != 0) {
            rectangle.setFillColor({250, 250, 250});
        } else
            rectangle.setFillColor({90, 90, 90});
        window.draw(rectangle);

        if (_ram->_memory[i] != 0) {
            std::string hex = std::format("{:02X}", _ram->_memory[i]);
            sf::Text text(hex, _font, 15);
            text.setFillColor(sf::Color::Black);
            text.setPosition(100 + x * 30 + 2, 100 + y * 30 + 5);
            window.draw(text);
        }
    }
}

void Emmett::draw_code(sf::RenderWindow &window)
{
    // draw the lines
    sf::RectangleShape rectangle(sf::Vector2f(160, 40));
    rectangle.setPosition(100, 100);
    rectangle.setFillColor({250, 250, 250});
    int offset = 0;
    for (auto &l : _code->_lines)
    {
        rectangle.setFillColor({250, 250, 250});
        rectangle.setSize(sf::Vector2f(160, 40));
        rectangle.setPosition(1350, 100 + offset);
        window.draw(rectangle);
        sf::Text text(l._text, _font, 20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(1350 + 10, 100 + offset + 5);
        window.draw(text);

        //indexing mode
        rectangle.setPosition(1420, 102 + offset);
        rectangle.setSize(sf::Vector2f(40, 36));
        rectangle.setFillColor({140, 140, 140});
        window.draw(rectangle);
        sf::Text indexModeText(indexModeTexts.at(l._indexModeType), _font, 15);
        indexModeText.setFillColor(sf::Color::Black);
        indexModeText.setPosition(1420 + 5, 102 + offset + 5);
        window.draw(indexModeText);

        offset += 50; // Increment offset for each line
    }
}

void Emmett::draw_cpu(sf::RenderWindow &window)
{
    // draw Cpu
    sf::RectangleShape rectangle(sf::Vector2f(360, 160));
    rectangle.setFillColor({155, 89, 182});
    rectangle.setPosition(100, 600);
    window.draw(rectangle);

    // register
    rectangle.setFillColor({90, 90, 90});
    rectangle.setSize(sf::Vector2f(30, 30));
    for (int i = 0; i < _cpu->_registers.size(); i += 1)
    {
        rectangle.setPosition(380 + (i / 4) * 35, 610 + (i % 4) * 35 + 2);
        window.draw(rectangle);

        if (_cpu->_registers[i] != 0) {
            std::string hex = std::format("{:02X}", _cpu->_registers[i]);
            sf::Text text(hex, _font, 17);
            text.setFillColor(sf::Color::Black);
            text.setPosition(380 + (i / 4) * 35 + 2, 610 + (i % 4) * 35 + 7);
            window.draw(text);
        }
    }

    // X and Y
    rectangle.setSize(sf::Vector2f(60, 60));
    rectangle.setPosition(300, 615);
    if (_cpu->_x == 0)
        rectangle.setFillColor({90, 90, 90});
    else
        rectangle.setFillColor({155, 155, 155});
    window.draw(rectangle);
    if (_cpu->_x != 0) {
        std::string hex = std::format("{:02X}", _cpu->_x);
        sf::Text text(hex, _font, 32);
        text.setFillColor(sf::Color::Black);
        text.setPosition(300 + 5, 615 + 10);
        window.draw(text);
    }

    window.draw(rectangle);
    rectangle.setPosition(300, 685);
    if (_cpu->_y == 0)
        rectangle.setFillColor({90, 90, 90});
    else
        rectangle.setFillColor({155, 155, 155});
    window.draw(rectangle);
    if (_cpu->_y != 0) {
        std::string hex = std::format("{:02X}", _cpu->_y);
        sf::Text text(hex, _font, 32);
        text.setFillColor(sf::Color::Black);
        text.setPosition(300 + 5, 685 + 10);
        window.draw(text);
    }

    // Accumulator
    rectangle.setSize(sf::Vector2f(120, 120));
    rectangle.setPosition(170, 620);
    if (_cpu->_a == 0)
        rectangle.setFillColor({90, 90, 90});
    else
        rectangle.setFillColor({155, 155, 155});
    window.draw(rectangle);
    if (_cpu->_a != 0) {
        std::string hex = std::format("{:02X}", _cpu->_a);
        sf::Text text(hex, _font, 48);
        text.setFillColor(sf::Color::Black);
        text.setPosition(170 + 25, 620 + 30);
        window.draw(text);
    }

    // pc
    rectangle.setSize(sf::Vector2f(55, 30));
    rectangle.setPosition(108, 615);
    rectangle.setFillColor({155, 155, 155});
    window.draw(rectangle);
    std::string hex = std::format("{:04X}", _cpu->_pc);
    sf::Text text(hex, _font, 15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(110 + 2, 615 + 5);
    window.draw(text);

    rectangle.setSize(sf::Vector2f(45, 45));
    rectangle.setPosition(108, 650);
    rectangle.setFillColor({155, 155, 155});
    window.draw(rectangle);
    hex = std::format("{:02X}", _ram->_memory[_cpu->_pc]);
    text.setString(hex);
    text.setCharacterSize(21);
    text.setFillColor(sf::Color::Black);
    text.setPosition(110 + 5, 650 + 10);
    window.draw(text);
}
