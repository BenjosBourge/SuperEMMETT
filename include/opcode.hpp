/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

class Opcode {
public:
    Opcode();
    Opcode(std::string, char opcode);
    ~Opcode();

    std::string _name;
    unsigned char _opcode;
};

static const std::unordered_map<uint8_t, Opcode> opcodes = {
        {0x00, Opcode("NOP", 0x00)},
        {0x10, Opcode("LDA_abs", 0x10)},
};

