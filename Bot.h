#pragma once
#include <utility>
#include <vector>

class Bot {
public:
    Bot(char symbol);
    std::pair<int, int> getMove(const std::vector<std::vector<char>>& pole);

private:
    char symbol;
};
