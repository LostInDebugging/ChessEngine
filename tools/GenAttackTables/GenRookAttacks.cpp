#include "GenAttacks.h"
#include "MagicBB.h"
#include "Magic.h"

namespace AtkTableGen {
    std::array<uint64_t, Magic::MAX_ROOK_TABLE_SIZE> generateRookAttackTable(std::array<uint64_t, 64> rookMagics) {
        std::array<uint64_t, Magic::MAX_ROOK_TABLE_SIZE> rookAttackTable;
        for (int sq = 0; sq < 64; sq++) {
            uint64_t magic = rookMagics[sq];
            uint64_t mask = Magic::ROOK_BLOCKER_MASKS[sq];

            for (uint64_t blockers : Magic::bitSubsets(mask)) {
                int mi = Magic::magicIndex(sq, blockers, magic, Magic::ROOK);
                uint64_t moves = Magic::validSliderMoves(sq, blockers, Magic::ROOK.dirs, Magic::ROOK.dirCount);
                rookAttackTable[mi] = moves;
            }
        }

        return rookAttackTable;
    }
}