//
// Created by liebi on 21.09.2025.
//

#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <utility>

class Memory {
public:
    using Coord = std::pair<int,int>;
    using Sequence = std::vector<Coord>;

    Memory() = default;

    // přidá postupku a uloží i vlastníka (hráče: 'X' nebo 'O')
    void addSequence(const Sequence& seq, char owner);

    // vrátí reference na uložené postupky (každá položka: pár <owner, sequence>)
    const std::vector<std::pair<char, Sequence>>& getSequences() const;

    void clear();

private:
    // každá položka: <kdo (char), souřadnice postupky>
    std::vector<std::pair<char, Sequence>> sequences;
};

#endif //MEMORY_H