/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#include <vector>
#include <memory>

class Ram;

class Cpu {
public:
    Cpu();
    ~Cpu();

    void reset();

    char _a;
    char _x;
    char _y;

    int _pc;
    std::vector<char> _registers;

    std::shared_ptr<Ram> _ram;

    void fetch();
};