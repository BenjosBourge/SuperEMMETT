/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#include <vector>
#include <memory>
#include <ram.hpp>
#include <cpu.hpp>
#include <compiler.hpp>
#include <code.hpp>
#include <mouse.hpp>

class Emmett {
public:
    Emmett();
    ~Emmett();

    Mouse _mouse;

    std::shared_ptr<Ram> _ram;
    std::shared_ptr<Cpu> _cpu;
    std::shared_ptr<Compiler> _compiler;
    std::shared_ptr<Code> _code;
};