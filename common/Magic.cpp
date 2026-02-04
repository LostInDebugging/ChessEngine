#include <cstdint> 
#include "Magic.h"
#include "Attacks.h"

namespace Magic {
    int magicIndex(int sq, uint64_t blockers, uint64_t magic, Slider slider) {
        return (blockers * magic) >> (64 - slider.indexBits[sq]);
    }
}
