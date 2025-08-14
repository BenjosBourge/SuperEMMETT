
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cpu.hpp>
#include <unordered_map>
#include <ram.hpp>

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


void NOP(std::shared_ptr<Cpu> cpu)
{
    std::cout << "NOP executed at PC: " << cpu->_pc << std::endl;
}

void LDA(std::shared_ptr<Cpu> cpu)
{
    cpu->_a = cpu->_ram->getByte(cpu->_pc + 1);
    cpu->_pc++;
}



std::unordered_map<unsigned char, void(*)(std::shared_ptr<Cpu>)> opcodeMap = {
        {0x00, NOP},
        {0x10, LDA}
};

void Cpu::fetch()
{
    unsigned char opcode = _ram->getByte(_pc);
    if (opcodeMap.find(opcode) != opcodeMap.end()) {
        opcodeMap[opcode](_ram->_cpu);
    } else {
        std::cerr << "Unknown opcode: " << std::hex << static_cast<int>(opcode) << std::dec << " at PC: " << _pc << std::endl;
    }
    _pc++;
}

