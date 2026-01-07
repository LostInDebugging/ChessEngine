#include "GameState.h"
#include "MoveGen.h"

class GameState;

int main() {
    GameState *gameState = new GameState;

    gameState->PrintGameState();

    std::vector moves = MoveGen::generateSinglePawnPushes(*gameState);
    for (Move move : moves) {
        move.printMove();
    }
}
