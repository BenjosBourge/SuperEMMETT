/* ----------------------------\
|         Super EMMETT         |
\-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

enum LineType {
    LINE_TYPE_DEFAULT,
    LINE_TYPE_LDA
};

enum IndexModeType {
    INDEX_MODE_TYPE_NONE,
    INDEX_MODE_TYPE_IMMEDIATE,
    INDEX_MODE_TYPE_ABSOLUTE,
    INDEX_MODE_TYPE_INDIRECT
};

static const std::unordered_map<IndexModeType, std::string> indexModeTexts = {
        { INDEX_MODE_TYPE_NONE, "None" },
        { INDEX_MODE_TYPE_IMMEDIATE, "Imm" },
        { INDEX_MODE_TYPE_ABSOLUTE, "Abs" },
        { INDEX_MODE_TYPE_INDIRECT, "Ind" }
};

class Line {
public:
    Line();
    ~Line();

    LineType _type;
    std::string _text;
    int _content;

    std::vector<IndexModeType> _indexModes;
    int _indexModeIndex = 0;
    IndexModeType _indexModeType = INDEX_MODE_TYPE_NONE;
};

class Code {
public:
    Code();
    ~Code();

    std::vector<Line> _lines;

    void addLine();
    void removeLine();
};