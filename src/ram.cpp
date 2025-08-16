
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ram.hpp>

Ram::Ram()
{
    _memorySize = 512;
    _memory.resize(_memorySize, 0);
}

Ram::~Ram()
{

}

unsigned char Ram::getByte(int address)
{
    if (address < 0)
        address += _memorySize;
    if (address >= _memorySize)
        address -= _memorySize;
    return _memory[address];
}

void Ram::setByte(int address, unsigned char value)
{
    if (address < 0)
        address += _memorySize;
    if (address >= _memorySize)
        address -= _memorySize;
    _memory[address] = value;
}