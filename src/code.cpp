
#include <iostream>
#include <SFML/Graphics.hpp>
#include <code.hpp>

Line::Line()
{
    _type = LINE_TYPE_LDA;
    _text = "LDA";
    _content = 0;

    _indexModes.push_back(INDEX_MODE_TYPE_IMMEDIATE);
    _indexModes.push_back(INDEX_MODE_TYPE_ABSOLUTE);
    _indexModes.push_back(INDEX_MODE_TYPE_INDIRECT);
    _indexModeType = INDEX_MODE_TYPE_IMMEDIATE;
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