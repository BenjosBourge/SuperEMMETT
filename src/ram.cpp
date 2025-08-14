
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ram.hpp>

Ram::Ram() {
    _memorySize = 256*2;
    _memory.resize(_memorySize, 0);
}

Ram::~Ram() {
    // Destructor logic if needed
}