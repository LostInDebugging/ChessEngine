#include "GameState.h"
#include "MoveGen.h"
#include "Helpers.h"

int main() {
    GameState *gameState = new GameState("4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1");

    Helpers::printGameState(*gameState, Helpers::PRINT_LETTER_REP);

    std::vector moves = MoveGen::generatePawnPushes(*gameState);
    for (Move move : moves) {
        move.printMove();
    }
}
