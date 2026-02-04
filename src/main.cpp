#include "GameState.h"
#include "MoveGen.h"
#include "Helpers.h"
#include "MagicBB.h"
#include "Attacks.h"

int main() {
    GameState *gameState = new GameState("b1B5/3K2k1/1Q1p4/1P3p2/7P/3PP3/q4np1/1R3R2 b Kqk a3 205 123");

    std::vector moves = MoveGen::generatePseudolegalMoves(*gameState);

    for (Move move : moves) {
        move.printMove();
    }
    /*
    MagicBB::findRookMagics();
    MagicBB::findBishopMagics();
    
    std::cout << "Bishop Magics:\n";
    for (uint64_t magic : MagicBB::findBishopMagics()) {
        std::cout << magic << '\n';
    }

    std::cout << "Rook Magics:\n";
    for (uint64_t magic : MagicBB::findRookMagics()) {
        std::cout << magic << '\n';
    }
    */
}
