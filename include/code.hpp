/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once

enum LineType {
    LINE_TYPE_DEFAULT,
    LINE_TYPE_LDA
};

class Line {
public:
    Line();
    ~Line();

    LineType _type;
    std::string _text;
    int _content;
};

class Code {
public:
    Code();
    ~Code();

    std::vector<Line> _lines;

    void addLine();
    void removeLine();
};