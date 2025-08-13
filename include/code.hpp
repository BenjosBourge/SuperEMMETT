/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

class Line {
public:
    Line();
    ~Line();
};

class Code {
public:
    Code();
    ~Code();

    std::vector<Line> lines;
};