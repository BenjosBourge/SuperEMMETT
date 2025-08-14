
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cpu.hpp>

Cpu::Cpu()
{
    _pc = 0;
    _registers.resize(8, 0); // Initialize 8 registers to 0
    _a = 0;
    _x = 0;
    _y = 0;
}

void Cpu::reset()
{
    _pc = 0;
    _a = 0;
    _x = 0;
    _y = 0;

    for (auto &reg : _registers)
        reg = 0;
}

Cpu::~Cpu()
{

}

