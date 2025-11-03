#include "Game.h"
#include "Bot.h"
#include <iostream>

using namespace std;

Game::Game(int velikost, bool protiBotovi)
    : n(velikost),
      pole(n, vector<char>(n, '.')),
      tahy(0),
      konec(false),
      hrac('X'),
      protiBotovi(protiBotovi),
      bot(nullptr),
      memory() // implicitně
{
    if (protiBotovi) {
        bot = new Bot('O'); // bot hraje za O
    }
}

Game::~Game() {
    delete bot;
}

void Game::vypisPole() const {
    cout << "   ";
    for (int i = 0; i < n; i++) cout << i << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << i << " |";
        for (int j = 0; j < n; j++) {
            cout << pole[i][j] << " ";
        }
        cout << "\n";
    }
}

bool Game::isValidMove(int x, int y) const {
    return (x >= 0 && x < n && y >= 0 && y < n && pole[x][y] == '.');
}

// checkWin nyní naplní outSeq pokud najde výherní sekvenci (>=5)
bool Game::checkWin(int x, int y, char hrac, Memory::Sequence& outSeq) const {
    int dx[4] = {1, 0, 1, 1};
    int dy[4] = {0, 1, 1, -1};

    for (int dir = 0; dir < 4; dir++) {
        std::vector<std::pair<int,int>> seq;
        seq.emplace_back(x, y);

        int i = x + dx[dir], j = y + dy[dir];
        while (i >= 0 && i < n && j >= 0 && j < n && pole[i][j] == hrac) {
            seq.emplace_back(i, j);
            i += dx[dir];
            j += dy[dir];
        }

        i = x - dx[dir]; j = y - dy[dir];
        // pro zachování pořadí od jedné strany ke druhé přední části vkládáme na začátek
        std::vector<std::pair<int,int>> back;
        while (i >= 0 && i < n && j >= 0 && j < n && pole[i][j] == hrac) {
            back.emplace_back(i, j);
            i -= dx[dir];
            j -= dy[dir];
        }
        // vložíme back v obráceném pořadí před seq, aby výsledné pořadí bylo korektní
        for (int k = static_cast<int>(back.size()) - 1; k >= 0; --k) {
            seq.insert(seq.begin(), back[k]);
        }

        if ((int)seq.size() >= 5) {
            // naplníme outSeq a vrátíme true
            outSeq = seq;
            return true;
        }
    }
    return false;
}

void Game::play() {
    srand(time(nullptr));

    bool botZacina = (rand() % 2 == 1);
    cout << (botZacina ? "Bot" : "Hrac") << " zacina pripravu hry!\n";

    auto udelejTriTahy = [&](char hlavni, char druhy) {
        int placedMain = 0, placedOther = 0;
        while (placedMain + placedOther < 3) {
            int x = rand() % n;
            int y = rand() % n;
            if (!isValidMove(x, y)) continue;

            if (placedMain < 2) {
                pole[x][y] = hlavni;
                placedMain++;
            } else {
                pole[x][y] = druhy;
                placedOther++;
            }
        }
    };

    if (botZacina) {
        udelejTriTahy('O', 'X');
    } else {
        udelejTriTahy('X', 'O');
    }
    while (!konec) {
        vypisPole();
        cout << "Hrac " << hrac << " je na tahu." << endl;

        int x, y;
        if (protiBotovi && hrac == 'O') {
            auto move = bot->getMove(pole);
            x = move.first;
            y = move.second;
            cout << "Bot hraje: " << x << " " << y << endl;
        } else {
            cout << "Zadej souradnice (radek sloupec): ";
            cin >> x >> y;
        }

        if (!isValidMove(x, y)) {
            cout << "Neplatny tah, zkus znovu!" << endl;
            continue;
        }

        pole[x][y] = hrac;
        tahy++;

        Memory::Sequence foundSeq;
        if (checkWin(x, y, hrac, foundSeq)) {
            // uložíme nalezenou postupku do paměti
            memory.addSequence(foundSeq, hrac);

            vypisPole();
            cout << "Vyhral hrac " << hrac << "!" << endl;
            konec = true;
            continue;
        }

        hrac = (hrac == 'X') ? 'O' : 'X';

        if (tahy == n * n) {
            vypisPole();
            cout << "Remiza!" << endl;
            konec = true;
        }
    }

    // příklad: po skončení hry můžeme vypsat uložené postupky (pokud existují)
    const auto& seqs = memory.getSequences();
    if (!seqs.empty()) {
        cout << "Ulozene postupky (owner: sequence coords):\n";
        for (const auto& p : seqs) {
            char owner = p.first;
            const auto& seq = p.second;
            cout << owner << ": ";
            for (const auto& c : seq) {
                cout << "(" << c.first << "," << c.second << ") ";
            }
            cout << "\n";
        }
    }
}

const std::vector<std::pair<char, Memory::Sequence>>& Game::getMemorySequences() const {
    return memory.getSequences();
}