
#include <opcode.hpp>

Opcode::Opcode()
{
    _name = "NOP";
    _opcode = 0x00;
}

Opcode::Opcode(std::string name, char opcode)
{
    _name = name;
    _opcode = opcode;
}



