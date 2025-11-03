#include "Bot.h"
#include <cstdlib>
#include <ctime>

Bot::Bot(char symbol) : symbol(symbol) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

std::pair<int, int> Bot::getMove(const std::vector<std::vector<char>>& pole) {
    std::vector<std::pair<int, int>> volne;
    for (int i = 0; i < (int)pole.size(); i++) {
        for (int j = 0; j < (int)pole[i].size(); j++) {
            if (pole[i][j] == '.') {
                volne.emplace_back(i, j);
            }
        }
    }

    if (volne.empty()) return {-1, -1};

    int idx = std::rand() % volne.size();
    return volne[idx];
}
