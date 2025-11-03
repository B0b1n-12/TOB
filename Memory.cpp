//
// Created by liebi on 21.09.2025.
//

#include "Memory.h"

void Memory::addSequence(const Sequence& seq, char owner) {
    if (!seq.empty()) {
        sequences.emplace_back(owner, seq);
    }
}

const std::vector<std::pair<char, Memory::Sequence>>& Memory::getSequences() const {
    return sequences;
}

void Memory::clear() {
    sequences.clear();
}