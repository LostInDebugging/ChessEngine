#include "Helpers.h"
#include <iostream>
#include "BoardConstants.h"

namespace Helpers {
    // Print a bitboard in a nice 8x8 format of 0s and 1s.
    // Little-Endian Rank_File mapping
    void printBB(uint64_t bb) {
        std::cout << "---------------------------------\n";
        for (int i = 7; i >= 0; i--) {
            std::cout << "| ";
            for (int j = 0; j < 8; j++) {
                uint64_t bitInPlace = ((1ull << ((i * 8) + j)) & bb);
                char bit = bitInPlace == 0 ? '0' : '1';
                std::cout << bit;
                std::cout << " | ";
            }
            std::cout << "\n---------------------------------\n";
        }
    }
}
