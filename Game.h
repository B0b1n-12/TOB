#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>

class Bot;  // dopředná deklarace

// forward deklarace Memory
#include "Memory.h"

class Game {
private:
    int n;
    std::vector<std::vector<char>> pole;
    int tahy;
    bool konec;
    char hrac;
    bool protiBotovi;
    Bot* bot;


    // instance Memory pro ukládání postupků
    Memory memory;

public:
    Game(int velikost, bool protiBotovi = false);
    ~Game();

    void vypisPole() const;
    bool isValidMove(int x, int y) const;

    // změněná signatura: při úspěchu naplní outSeq souřadnicemi výherní postupky
    bool checkWin(int x, int y, char hrac, Memory::Sequence& outSeq) const;
    void play();

    // možnost získat uložené postupky z venku
    const std::vector<std::pair<char, Memory::Sequence>>& getMemorySequences() const;
};