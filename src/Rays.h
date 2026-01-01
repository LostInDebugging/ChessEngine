#include <cstdint>

namespace Rays {
    constexpr uint64_t make_rank_mask(int rank_index) {
        return 255ull << rank_index;
    }

    constexpr uint64_t make_file_mask(int file_index) {
        return 0b0000000100000001000000010000000100000001000000010000000100000001ull << file_index;
    }

    constexpr uint64_t RANKS[8] = {
        make_rank_mask(0),
        make_rank_mask(1),
        make_rank_mask(2),
        make_rank_mask(3),
        make_rank_mask(4),
        make_rank_mask(5),
        make_rank_mask(6),
        make_rank_mask(7)
    };

    constexpr uint64_t FILES[8] = {
        make_file_mask(0),
        make_file_mask(1),
        make_file_mask(2),
        make_file_mask(3),
        make_file_mask(4),
        make_file_mask(5),
        make_file_mask(6),
        make_file_mask(7)
    };
}
