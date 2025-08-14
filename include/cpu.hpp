/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once
#include <vector>
#include <memory>

class Ram;

class Cpu {
public:
    Cpu();
    ~Cpu();

    void reset();

    unsigned char _a;
    unsigned char _x;
    unsigned char _y;

    int _pc;
    std::vector<unsigned char> _registers;

    std::shared_ptr<Ram> _ram;

    void fetch();
};