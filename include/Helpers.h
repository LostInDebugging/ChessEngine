#ifndef HELPERS_H
#define HELPERS_H

#include <cstdint>
#include "GameState.h"

namespace Helpers {
    enum PrintGameStateMode {
        PRINT_ALL_BITBOARDS,
        PRINT_LETTER_REP
    };

    // Print a bitboard in a nice 8x8 format of 0s and 1s.
    void printBB(uint64_t bb);

    // Print the GameState
    void printGameState(GameState g, PrintGameStateMode mode);

    // Given a piece, return the corresponding character.
    char getPieceChar(Piece Piece);
}

#endif
