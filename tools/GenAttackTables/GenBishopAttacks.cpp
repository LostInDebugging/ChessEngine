#include "GenAttacks.h"
#include "MagicBB.h"
#include "Magic.h"

namespace AtkTableGen {
    std::array<uint64_t, Magic::MAX_BISHOP_TABLE_SIZE> generateBishopAttackTable(std::array<uint64_t, 64> bishopMagics) {
        std::array<uint64_t, Magic::MAX_BISHOP_TABLE_SIZE> bishopAttackTable;
        for (int sq = 0; sq < 64; sq++) {
            uint64_t magic = bishopMagics[sq];
            uint64_t mask = Magic::BISHOP_BLOCKER_MASKS[sq];

            for (uint64_t blockers : Magic::bitSubsets(mask)) {
                int mi = Magic::magicIndex(sq, blockers, magic, Magic::BISHOP);
                uint64_t moves = Magic::validSliderMoves(sq, blockers, Magic::BISHOP.dirs, Magic::BISHOP.dirCount);
                bishopAttackTable[mi] = moves;
            }
        }

        return bishopAttackTable;
    }
}