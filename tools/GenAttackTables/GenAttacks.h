#ifndef GEN_ATTACKS_H
#define GEN_ATTACKS_H

#include <array>
#include <cstdint>

#include "MagicBB.h"

namespace AtkTableGen { 
    std::array<uint64_t, 64> generateKnightAttackTable();
    std::array<uint64_t, 64> generateKingAttackTable();
    std::array<uint64_t, Magic::MAX_BISHOP_TABLE_SIZE> generateBishopAttackTable(std::array<uint64_t, 64> bishopMagics);
    std::array<uint64_t, Magic::MAX_ROOK_TABLE_SIZE> generateRookAttackTable(std::array<uint64_t, 64> rookMagics);
}

#endif