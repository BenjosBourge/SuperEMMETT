/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <code.hpp>

class Ram;

class Compiler {
public:
    Compiler();
    ~Compiler();

    std::shared_ptr<Ram> _ram;

    void compile(const std::vector<Line>& lines);
};