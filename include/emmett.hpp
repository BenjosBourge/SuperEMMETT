/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <ram.hpp>
#include <cpu.hpp>
#include <compiler.hpp>
#include <code.hpp>
#include <mouse.hpp>
#include <button.hpp>

class Emmett {
public:
    Emmett();
    ~Emmett();

    Mouse _mouse;

    std::shared_ptr<Ram> _ram;
    std::shared_ptr<Cpu> _cpu;
    std::shared_ptr<Compiler> _compiler;
    std::shared_ptr<Code> _code;

    void update(float deltaTime, std::shared_ptr<Emmett> emmett);
    void draw(sf::RenderWindow &window);
    void draw_ram(sf::RenderWindow &window);
    void draw_code(sf::RenderWindow &window);
    void draw_cpu(sf::RenderWindow &window);

    std::vector<Button> _buttons;

    sf::Font _font;

    bool _run;
    float _timer;
};