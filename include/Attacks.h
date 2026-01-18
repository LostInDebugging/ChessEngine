#ifndef ATTACKS_H
#define ATTACKS_H

#include <array>
#include <cstdint>

namespace Attacks {
    extern const std::array<uint64_t, 64> knightAttacks;

    extern const std::array<uint64_t, 64> kingAttacks;
}

#endif