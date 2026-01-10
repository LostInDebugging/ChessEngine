#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <iostream>
#include <vector>
#include <bit>
#include "Move.h"
#include "GameState.h"

class MoveGen {
public:
    // generates all single and double pawn pushes. Does not generate promotion moves
    static std::vector<Move> generatePawnPushes(GameState state);

private:
    static void extractMoves(std::vector<Move>& moves, uint64_t bb, int offset);
};

#endif
