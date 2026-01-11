#include "GameState.h"
#include "MoveGen.h"
#include "Helpers.h"

int main() {
    GameState *gameState = new GameState("b1B5/3K2k1/1Q1p4/1P3p2/7P/3PP3/q4np1/1R3R2 b - - 0 1");

    Helpers::printGameState(*gameState, Helpers::PRINT_LETTER_REP);

    std::vector moves = MoveGen::generatePawnPushes(*gameState);
    std::vector moves1 = MoveGen::generatePawnPromotions(*gameState);
    std::vector moves2 = MoveGen::generatePawnCaptures(*gameState);

    for (Move move : moves) {
        move.printMove();
    }

    for (Move move : moves1) {
        move.printMove();
    }
    for (Move move : moves2) {
        move.printMove();
    }
}
