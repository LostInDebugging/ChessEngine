#ifndef GEN_KING_KNIGHT_ATTACKS_H
#define GEN_KING_KNIGHT_ATTACKS_H

#include <array>
#include <cstdint>

namespace AtkTableGen { 
    std::array<uint64_t, 64> generateKnightAttackTable();
    std::array<uint64_t, 64> generateKingAttackTable();
}

#endif