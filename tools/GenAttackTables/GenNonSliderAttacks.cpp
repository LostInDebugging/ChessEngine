#include "GenAttacks.h"
#include "BoardConstants.h"

namespace AtkTableGen {
    std::array<uint64_t, 64> generateKnightAttackTable() {
        std::array<uint64_t, 64> knightAttacks {};

        for (int sq = 0; sq < 64; sq++) {
            uint64_t pos = 1ull << sq;

            knightAttacks[sq] = 
            ((pos << 17) & ~Rays::FILE_A) | // 2 up 1 right
            ((pos << 15) & ~Rays::FILE_H) | // 2 up 1 left
            ((pos << 10) & ~(Rays::FILE_A | Rays::FILE_B)) | // 1 up 2 right
            ((pos << 6) & ~(Rays::FILE_G | Rays::FILE_H)) | // 1 up 2 left
            ((pos >> 17) & ~Rays::FILE_H) | // 2 down 1 left
            ((pos >> 15) & ~Rays::FILE_A) | // 2 down 1 right
            ((pos >> 10) & ~(Rays::FILE_G | Rays::FILE_H)) | // 1 down 2 left
            ((pos >> 6) & ~(Rays::FILE_A | Rays::FILE_B));
        }

        return knightAttacks;
    }

    std::array<uint64_t, 64> generateKingAttackTable() {
        std::array<uint64_t, 64> kingAttacks {};
        
        struct Direction {
            int dr;
            int dc;
        };

        constexpr struct Direction DIRS[] = {
            {0, 1}, {1, 0}, {-1, 0}, {0, -1}, // plus dir
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // cross dir
        };

        for (int sq = 0; sq < 64; sq++) {
            int row = sq / 8;
            int col = sq % 8;

            for (Direction dir : DIRS) {
                int endrow = row + dir.dr;
                int endcol = col + dir.dc;

                if (endrow >= 0 && endrow < 8 && endcol >= 0 && endcol < 8) {
                    kingAttacks[sq] |= 1ull << ((8 * endrow) + endcol);
                }
            }
        }

        return kingAttacks;
    }
}