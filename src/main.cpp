#include "GameState.h"
#include "MoveGen.h"

class GameState;

int main() {
    GameState *gameState = new GameState;

    gameState->PrintGameState();

    std::vector moves = MoveGen::generatePawnPushes(*gameState);
    for (Move move : moves) {
        move.printMove();
    }
}
