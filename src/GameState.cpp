#include "GameState.h"

GameState::GameState(std::string FEN) {

}

// Create a new Chess game with the starting position
GameState::GameState() {
    m_pbb = (0b11111111ull << 48) | (0b11111111ull << 8);
    m_nbb = (0b01000010ull << 56) | 0b01000010ull;
    m_bbb = (0b00100100ull << 56) | 0b00100100ull;
    m_rbb = (0b10000001ull << 56) | 0b10000001ull;
    m_qbb = (0b00001000ull << 56) | 0b00001000ull;
    m_kbb = (0b00010000ull << 56) | 0b00010000ull;
    m_bpbb = 0b1111111111111111ull << 48;
    m_wpbb = 0b1111111111111111ull;

    m_activeColour = PlayerColour::WHITE;
    m_castlingRights = -1; // TODO: castling rights
    m_halfMoveClock = 0;
    m_fullMoveCount = 0;
}

// Return the currently active colour
PlayerColour GameState::getActiveColour() {
    return m_activeColour;
}

uint64_t GameState::getEmptyBB() {
    return ~(m_bpbb | m_wpbb);
}

// Return the piece bitboard of the specified colour
uint64_t GameState::pieceBB(Piece piece) {
    uint64_t pbb = 0;
    uint64_t cbb = 0;

    switch(piece.piece) {
        case PieceType::PAWN:
            pbb = m_pbb;
            break;
        case PieceType::KNIGHT:
            pbb = m_nbb;
            break;
        case PieceType::BISHOP:
            pbb = m_bbb;
            break;
        case PieceType::ROOK:
            pbb = m_rbb;
            break;
        case PieceType::QUEEN:
            pbb = m_qbb;
            break;
        case PieceType::KING:
            pbb = m_kbb;
            break;
        default:
            return 0;
    }

    switch(piece.colour) {
        case PlayerColour::WHITE:
            cbb = m_wpbb;
            break;
        case PlayerColour::BLACK:
            cbb = m_bpbb;
            break;
        default:
            return 0;
    }

    return pbb & cbb;
}

// PRIVATE METHOD DEFINITIONS
// =============================================================================
// =============================================================================


Piece GameState::getPieceAtSquare(int square) {
    unsigned long long bitMask = 1ull << square;
    Piece piece;

    if (bitMask & m_pbb) {
        piece.piece = PieceType::PAWN;
    } else if (bitMask & m_nbb) {
        piece.piece = PieceType::KNIGHT;
    } else if (bitMask & m_bbb) {
        piece.piece = PieceType::BISHOP;
    } else if (bitMask & m_rbb) {
        piece.piece = PieceType::ROOK;
    } else if (bitMask & m_qbb) {
        piece.piece = PieceType::QUEEN;
    } else if (bitMask & m_kbb) {
        piece.piece = PieceType::KING;
    } else {
        piece.piece = PieceType::INVALID;
    }

    if (bitMask & getEmptyBB()) {
        piece.piece = PieceType::EMPTY;
        piece.colour = PlayerColour::INVALID;
    } else if (bitMask & m_wpbb) {
        piece.colour = PlayerColour::WHITE;
    } else {
        piece.colour = PlayerColour::BLACK;
    }
    return piece;
}
