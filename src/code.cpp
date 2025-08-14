
#include <iostream>
#include <SFML/Graphics.hpp>
#include <code.hpp>

Line::Line()
{
    _type = LINE_TYPE_LDA;
    _text = "LDA";
    _content = 0;
}

Line::~Line()
{

}

Code::Code()
{

}

Code::~Code()
{

}

void Code::addLine()
{
    _lines.push_back(Line());
}

void Code::removeLine()
{
    if (!_lines.empty()) {
        _lines.pop_back();
    }
}