/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once
#include <vector>
#include <memory>

class Cpu;

class Ram {
public:
    Ram();
    ~Ram();

    unsigned char getByte(int address);
    void setByte(int address, unsigned char value);

    int _memorySize;
    std::vector<unsigned char> _memory;

    std::shared_ptr<Cpu> _cpu;
};