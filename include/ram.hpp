/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#include <vector>

class Ram {
public:
    Ram();
    ~Ram();

    int _memorySize;
    std::vector<char> _memory;
};