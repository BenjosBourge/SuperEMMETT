
#include <iostream>
#include <SFML/Graphics.hpp>
#include <emmett.hpp>

Emmett::Emmett()
{
    _ram = std::make_shared<Ram>();
    _cpu = std::make_shared<Cpu>();
    _compiler = std::make_shared<Compiler>();
    _code = std::make_shared<Code>();

    _ram->_cpu = _cpu;
    _compiler->_ram = _ram;
    _cpu->_ram = _ram;

    _run = false;
    _timer = 0.0f;
}

Emmett::~Emmett()
{

}

void Emmett::update(float deltaTime)
{
    if (_run) {
        _timer -= deltaTime;
        if (_timer <= 0.0f) {
            _cpu->fetch();
            _timer = 0.5f;
        }
    }
}
