/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once

class Line {
public:
    Line();
    ~Line();
};

class Code {
public:
    Code();
    ~Code();

    std::vector<Line> _lines;

    void addLine();
    void removeLine();
};