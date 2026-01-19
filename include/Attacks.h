#ifndef ATTACKS_H
#define ATTACKS_H

#include <array>
#include <cstdint>

#include "Magic.h"

namespace Attacks {
    extern const std::array<uint64_t, 64> knightAttacks;
    extern const std::array<uint64_t, 64> kingAttacks;
    extern const std::array<uint64_t, Magic::MAX_BISHOP_TABLE_SIZE> bishopAttacks;
    extern const std::array<uint64_t, Magic::MAX_ROOK_TABLE_SIZE> rookAttacks;
}

#endif