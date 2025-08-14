/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#include <vector>
#include <memory>

class Ram;

class Compiler {
public:
    Compiler();
    ~Compiler();

    std::shared_ptr<Ram> _ram;
};