#ifndef BOARDCONSTANTS_H
#define BOARDCONSTANTS_H

#include <cstdint>

enum class PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    EMPTY,
    INVALID
};

enum class PlayerColour {
    BLACK, 
    WHITE,
    INVALID
};

struct Piece {
    PieceType piece;
    PlayerColour colour;
};


namespace Rays {
    constexpr uint64_t make_rank_mask(int rank_index) {
        return 255ull << (rank_index * 8);
    }

    constexpr uint64_t make_file_mask(int file_index) {
        return 0b0000000100000001000000010000000100000001000000010000000100000001ull << file_index;
    }

    constexpr uint64_t RANK_1 = make_rank_mask(0);
    constexpr uint64_t RANK_2 = make_rank_mask(1);
    constexpr uint64_t RANK_3 = make_rank_mask(2);
    constexpr uint64_t RANK_4 = make_rank_mask(3);
    constexpr uint64_t RANK_5 = make_rank_mask(4);
    constexpr uint64_t RANK_6 = make_rank_mask(5);
    constexpr uint64_t RANK_7 = make_rank_mask(6);
    constexpr uint64_t RANK_8 = make_rank_mask(7);

    constexpr uint64_t FILE_A = make_file_mask(0);
    constexpr uint64_t FILE_B = make_file_mask(1);
    constexpr uint64_t FILE_C = make_file_mask(2);
    constexpr uint64_t FILE_D = make_file_mask(3);
    constexpr uint64_t FILE_E = make_file_mask(4);
    constexpr uint64_t FILE_F = make_file_mask(5);
    constexpr uint64_t FILE_G = make_file_mask(6);
    constexpr uint64_t FILE_H = make_file_mask(7);
}

#endif
