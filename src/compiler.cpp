
#include <iostream>
#include <SFML/Graphics.hpp>
#include <compiler.hpp>
#include <ram.hpp>
#include <cpu.hpp>
#include <unordered_map>

Compiler::Compiler()
{

}

Compiler::~Compiler()
{

}

void LDA(std::shared_ptr<Ram> ram, Line line, int &pc)
{
    ram->_memory[pc] = 0x10; // Opcode for LDA
    ram->_memory[pc + 1] = pc + 1;
    pc += 2; // Move to the next instruction
}

std::unordered_map<LineType, void(*)(std::shared_ptr<Ram>, Line, int&)> opcodeHandlers = {
    {LINE_TYPE_LDA, LDA}
};

void Compiler::compile(const std::vector<Line>& lines)
{
    int pc = 0;
    for (int i = 0; i < _ram->_memorySize; ++i)
        _ram->_memory[i] = 0;

    for (auto &l : lines) {
        if (opcodeHandlers.find(l._type) != opcodeHandlers.end()) {
            opcodeHandlers[l._type](_ram, l, pc);
        } else {
            std::cerr << "Unknown instruction type: " << l._type << std::endl;
        }
    }
}

