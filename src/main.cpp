#include "GameState.h"
#include "MoveGen.h"
#include "Helpers.h"

int main() {
    GameState *gameState = new GameState;

    Helpers::printGameState(*gameState, Helpers::PRINT_LETTER_REP);

    std::vector moves = MoveGen::generatePawnPushes(*gameState);
    for (Move move : moves) {
        move.printMove();
    }
}
