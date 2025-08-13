
#include <iostream>
#include <SFML/Graphics.hpp>
#include <code.hpp>

Line::Line()
{
    std::cout << "Line object created." << std::endl;
}

Line::~Line()
{
    std::cout << "Line object destroyed." << std::endl;
}

Code::Code() {
    std::cout << "Code object created." << std::endl;
}

Code::~Code() {
    std::cout << "Code object destroyed." << std::endl;
}