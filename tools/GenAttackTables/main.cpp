#include <array>
#include <iostream>
#include <fstream>

#include "MagicBB.h"
#include "GenAttacks.h"

int main () {
    std::ofstream bishopMagicsOut("../data/BishopMagics.cpp", std::ios::trunc);
    std::ofstream rookMagicsOut("../data/RookMagics.cpp", std::ios::trunc);
    std::ofstream bishopAttacksOut("../data/BishopAttacks.cpp", std::ios::trunc);
    std::ofstream rookAttacksOut("../data/RookAttacks.cpp", std::ios::trunc);

    if (!rookMagicsOut || !bishopMagicsOut || !rookAttacksOut || !bishopAttacksOut) {
        std::cerr << "Failed to open output files\n";
        return 1;   
    }

    std::array<uint64_t, 64> rookMagics = Magic::findRookMagics();
    std::array<uint64_t, 64> bishopMagics = Magic::findBishopMagics();
    std::array<uint64_t, Magic::MAX_BISHOP_TABLE_SIZE> bishopAttackTable = AtkTableGen::generateBishopAttackTable(bishopMagics);
    std::array<uint64_t, Magic::MAX_ROOK_TABLE_SIZE> rookAttackTable = AtkTableGen::generateRookAttackTable(rookMagics);

    rookMagicsOut << "#include <array>\n";
    rookMagicsOut << "#include <cstdint>\n\n";

    rookMagicsOut << "namespace Magic {\n";
    rookMagicsOut << "    std::array<uint64_t, 64> ROOK_MAGICS = {\n        ";
    for (int i = 0; i < 64; i++) {
        rookMagicsOut << "0x" << std::hex << rookMagics[i];
        if (i != 63) {
            rookMagicsOut << ", ";
        }
        if ((i + 1) % 4 == 0 && i != 63) {
            rookMagicsOut << "\n        ";
        }
    }
    rookMagicsOut << "\n    };\n}\n";


    bishopMagicsOut << "#include <array>\n";
    bishopMagicsOut << "#include <cstdint>\n\n";

    bishopMagicsOut << "namespace Magic {\n";
    bishopMagicsOut << "    std::array<uint64_t, 64> BISHOP_MAGICS = {\n        ";
    for (int i = 0; i < 64; i++) {
        bishopMagicsOut << "0x" << std::hex << bishopMagics[i];
        if (i != 63) {
            bishopMagicsOut << ", ";
        }
        if ((i + 1) % 4 == 0 && i != 63) {
            bishopMagicsOut << "\n        ";
        }
    }
    bishopMagicsOut << "\n    };\n}\n";


    rookAttacksOut << "#include <array>\n";
    rookAttacksOut << "#include <cstdint>\n";
    rookAttacksOut << "#include \"Magic.h\"\n\n";

    rookAttacksOut << "namespace Attacks {\n";
    rookAttacksOut << "    std::array<uint64_t, Magic::MAX_ROOK_TABLE_SIZE> rookAttacks = {\n        ";
    for (int i = 0; i < Magic::MAX_ROOK_TABLE_SIZE - 1; i++) {
        rookAttacksOut << "0x" << std::hex << rookAttackTable[i];
        if (i != Magic::MAX_ROOK_TABLE_SIZE - 1) {
            rookAttacksOut << ", ";
        }
        if ((i + 1) % 4 == 0 && i != Magic::MAX_ROOK_TABLE_SIZE - 1) {
            rookAttacksOut << "\n        ";
        }
    }
    rookAttacksOut << "\n    };\n}\n";

    bishopAttacksOut << "#include <array>\n";
    bishopAttacksOut << "#include <cstdint>\n";
    bishopAttacksOut << "#include \"Magic.h\"\n\n";

    bishopAttacksOut << "namespace Attacks {\n";
    bishopAttacksOut << "    std::array<uint64_t, Magic::MAX_BISHOP_TABLE_SIZE> bishopAttacks = {\n        ";
    for (int i = 0; i < Magic::MAX_BISHOP_TABLE_SIZE - 1; i++) {
        bishopAttacksOut << "0x" << std::hex << bishopAttackTable[i];
        if (i != Magic::MAX_BISHOP_TABLE_SIZE - 1) {
            bishopAttacksOut << ", ";
        }
        if ((i + 1) % 4 == 0 && i != Magic::MAX_BISHOP_TABLE_SIZE - 1) {
            bishopAttacksOut << "\n        ";
        }
    }
    bishopAttacksOut << "\n    };\n}\n";
}