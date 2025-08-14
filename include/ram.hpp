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

    int _memorySize;
    std::vector<char> _memory;

    std::shared_ptr<Cpu> _cpu;
};