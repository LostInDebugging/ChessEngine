#include <cstdint> 
#include "Magic.h"
#include "Attacks.h"

namespace Magic {
    int magicIndex(int sq, uint64_t blockers, uint64_t magic, Slider slider) {
        return (blockers * magic) >> (64 - slider.indexBits[sq]);
    }

    uint64_t getBishopMoves(int sq, uint64_t all) {
        return Attacks::bishopAttacks[magicIndex(sq, all & BISHOP_BLOCKER_MASKS[sq], BISHOP_MAGICS[sq], BISHOP)];
    }

    uint64_t getRookMoves(int sq, uint64_t all) {
        return Attacks::rookAttacks[magicIndex(sq, all & ROOK_BLOCKER_MASKS[sq], ROOK_MAGICS[sq], ROOK)];
    }
}
