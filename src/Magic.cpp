#include <cstdint> 
#include "Magic.h"
#include "Attacks.h"

namespace Magic {
    uint64_t getBishopMoves(int sq, uint64_t all) {
        return Attacks::bishopAttacks[magicIndex(sq, all & BISHOP_BLOCKER_MASKS[sq], BISHOP_MAGICS[sq], BISHOP)];
    }

    uint64_t getRookMoves(int sq, uint64_t all) {
        return Attacks::rookAttacks[magicIndex(sq, all & ROOK_BLOCKER_MASKS[sq], ROOK_MAGICS[sq], ROOK)];
    }
}
