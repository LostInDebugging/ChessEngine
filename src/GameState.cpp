#include "GameState.h"

GameState::GameState(std::string FEN) {

}

// Create a new Chess game with the starting position
GameState::GameState() {
    m_bboards[bbIndex(bbVal::BLACKPAWNS)] = 0b11111111ull << 48;
    m_bboards[bbIndex(bbVal::BLACKKNIGHTS)] = 0b01000010ull << 56;
    m_bboards[bbIndex(bbVal::WHITEPAWNS)] = 0b11111111ull << 8;
    m_bboards[bbIndex(bbVal::WHITEKNIGHTS)] = 0b01000010ull;
    m_bboards[bbIndex(bbVal::BLACKBISHOPS)] = 0b00100100ull << 56;
    m_bboards[bbIndex(bbVal::WHITEBISHOPS)] = 0b00100100ull;
    m_bboards[bbIndex(bbVal::BLACKROOKS)] = 0b10000001ull << 56;
    m_bboards[bbIndex(bbVal::WHITEROOKS)] = 0b10000001ull;
    m_bboards[bbIndex(bbVal::BLACKQUEENS)] = 0b00001000ull << 56;
    m_bboards[bbIndex(bbVal::WHITEQUEENS)] = 0b00001000ull;
    m_bboards[bbIndex(bbVal::BLACKKING)] = 0b00010000ull << 56;
    m_bboards[bbIndex(bbVal::WHITEKING)] = 0b00010000ull;
    m_bboards[bbIndex(bbVal::BLACKPIECES)] = 0b1111111111111111ull << 48;
    m_bboards[bbIndex(bbVal::WHITEPIECES)] = 0b1111111111111111ull;
    m_bboards[bbIndex(bbVal::EMPTY)] = std::numeric_limits<unsigned long long>::max() ^ (m_bboards[bbIndex(bbVal::BLACKPIECES)] | m_bboards[bbIndex(bbVal::WHITEPIECES)]);

    m_activeColour = PlayerColour::WHITE;
    m_castlingRights = -1; // TODO: castling rights
    m_halfMoveClock = 0;
    m_fullMoveCount = 0;
}

// return the bitboards for reading only
const uint64_t* GameState::getPosBB() {
    return m_bboards;
}

// Return the pawn bitboard for reading
uint64_t GameState::getPawnBB(PlayerColour colour) {
    if (colour == PlayerColour::BLACK) {
        return m_bboards[bbIndex(bbVal::BLACKPAWNS)];
    }
    return m_bboards[bbIndex(bbVal::WHITEPAWNS)];
}

// Return the currently active colour
PlayerColour GameState::getActiveColour() {
    return m_activeColour;
}

// Print the GameState
void GameState::PrintGameState() {
    std::cout << "---------------------------------\n";
    for (int i = 7; i >= 0; i--) {
        std::cout << "| ";
        for (int j = 7; j >= 0; j--) {
            bbVal piece = getPieceAtSquare(i * 8 + j);
            std::cout << getPieceChar(piece);
            std::cout << " | ";
        }
        std::cout << "\n---------------------------------\n";
    }
}

// PRIVATE METHOD DEFINITIONS
// =============================================================================
// =============================================================================
char GameState::getPieceChar(bbVal Piece) {
    switch(Piece) {
        case bbVal::BLACKPAWNS:
            return 'p';
        case bbVal::BLACKKNIGHTS:
            return 'n';
        case bbVal::BLACKBISHOPS:
            return 'b';
        case bbVal::BLACKROOKS:
            return 'r';
        case bbVal::BLACKQUEENS:
            return 'q';
        case bbVal::BLACKKING:
            return 'k';
        case bbVal::WHITEPAWNS:
            return 'P';
        case bbVal::WHITEKNIGHTS:
            return 'N';
        case bbVal::WHITEBISHOPS:
            return 'B';
        case bbVal::WHITEROOKS:
            return 'R';
        case bbVal::WHITEQUEENS:
            return 'Q';
        case bbVal::WHITEKING:
            return 'K';
        case bbVal::EMPTY:
            return ' ';
        default:
            // Should never reach here
            return '-';
    }
}

bbVal GameState::getPieceAtSquare(int square) {
    unsigned long long bitMask = 1ull << square;
    
    if (bitMask & m_bboards[bbIndex(bbVal::EMPTY)]) {
        return bbVal::EMPTY;
    } else if (bitMask & m_bboards[bbIndex(bbVal::WHITEPIECES)]) {
        // return correct white piece
        if (bitMask & m_bboards[bbIndex(bbVal::WHITEPAWNS)]) {
            return bbVal::WHITEPAWNS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::WHITEKNIGHTS)]) {
            return bbVal::WHITEKNIGHTS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::WHITEBISHOPS)]) {
            return bbVal::WHITEBISHOPS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::WHITEROOKS)]) {
            return bbVal::WHITEROOKS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::WHITEQUEENS)]) {
            return bbVal::WHITEQUEENS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::WHITEKING)]) {
            return bbVal::WHITEKING;
        } else {
            // Should never reach here
            return bbVal::EMPTY;
        }
    } else {
        // return correct black piece
        if (bitMask & m_bboards[bbIndex(bbVal::BLACKPAWNS)]) {
            return bbVal::BLACKPAWNS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::BLACKKNIGHTS)]) {
            return bbVal::BLACKKNIGHTS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::BLACKBISHOPS)]) {
            return bbVal::BLACKBISHOPS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::BLACKROOKS)]) {
            return bbVal::BLACKROOKS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::BLACKQUEENS)]) {
            return bbVal::BLACKQUEENS;
        } else if (bitMask & m_bboards[bbIndex(bbVal::BLACKKING)]) {
            return bbVal::BLACKKING;
        } else {
            // should never reach here
            return bbVal::EMPTY;
        }
    }
}
