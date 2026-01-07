#include <iostream>
#include <vector>
#include <bit>
#include "Move.h"
#include "GameState.h"
#include "Rays.h"

class MoveGen {
public:
    static std::vector<Move> generateSinglePawnPushes(GameState state);

private:
    static void extractMoves(std::vector<Move>& moves, uint64_t bb, int offset);
};
