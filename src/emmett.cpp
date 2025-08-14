
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
}

Emmett::~Emmett()
{

}
