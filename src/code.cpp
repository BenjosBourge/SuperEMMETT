
#include <iostream>
#include <SFML/Graphics.hpp>
#include <code.hpp>

Line::Line()
{

}

Line::~Line()
{

}

Code::Code() {

}

Code::~Code() {

}

void Code::addLine() {
    _lines.push_back(Line());
}

void Code::removeLine() {
    if (!_lines.empty()) {
        _lines.pop_back();
    }
}