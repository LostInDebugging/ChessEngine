#include <iostream>
#include <vector>
#include "Move.h"
#include "GameState.h"

class MoveGen {
public:
    static std::vector<Move> generateSinglePawnPushes(GameState state) {
        uint64_t pawnBB = state.getPawnBB(state.getActiveColour());

        
    }
};
