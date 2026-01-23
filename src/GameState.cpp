#include "GameState.h"
#include "Helpers.h"
#include "Attacks.h"
#include "Magic.h"

GameState::GameState(std::string FEN) {
    int posEndIndex = FEN.find(' ');
    std::string posSubstr = FEN.substr(0, posEndIndex);

    int actColIndex = FEN.find(' ', posEndIndex + 1);
    std::string actCol = FEN.substr(posEndIndex + 1, 1);

    int castlingRightsIndex = FEN.find(' ', actColIndex + 1);
    std::string castlingRights = FEN.substr(actColIndex + 1, castlingRightsIndex - actColIndex);

    int enPassantIndex = FEN.find(' ', castlingRightsIndex + 1);
    std::string enPassant = FEN.substr(castlingRightsIndex + 1, enPassantIndex - castlingRightsIndex);

    int halfMoveClockIndex = FEN.find(' ', enPassantIndex + 1);
    std::string halfMoveClock = FEN.substr(enPassantIndex + 1, halfMoveClockIndex - enPassantIndex);

    std::string fullMoveCount = FEN.substr(halfMoveClockIndex + 1);

    m_activeColour = actCol == "w" ? PlayerColour::WHITE : PlayerColour::BLACK;
    m_enPassant = enPassant == "-" ? -1 : Helpers::squareLetterMapToIndex(enPassant);

    int rank = 7;
    int file = 0;
    for (char c : posSubstr) {
        int index = rank * 8 + file;
        if (c == '/') {
            rank -= 1;
            file = 0;
        } else if (c >= '1' && c <= '8') {
            file += (c - '0');
        } else {
            file += 1;

            if (isupper(c)) {
                m_wpbb |= (1ull << index);
            } else {
                m_bpbb |= (1ull << index);
            }
            
            switch(tolower(c)) {
                case 'p':
                    m_pbb |= (1ull << index);
                    break;
                case 'n':
                    m_nbb |= (1ull << index);
                    break;
                case 'b':
                    m_bbb |= (1ull << index);
                    break;
                case 'r':
                    m_rbb |= (1ull << index);
                    break;
                case 'q':
                    m_qbb |= (1ull << index);
                    break;
                case 'k':
                    m_kbb |= (1ull << index);
                    break;
                default:
                    // should never enter here
                    return;
            }
        }
    }
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
    m_castlingRights = WHITE_KINGSIDE | WHITE_QUEENSIDE | BLACK_KINGSIDE | BLACK_QUEENSIDE;
    m_enPassant = NO_EN_PASSANT;
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
            pbb = ~pbb;
    }

    switch(piece.colour) {
        case PlayerColour::WHITE:
            cbb = m_wpbb;
            break;
        case PlayerColour::BLACK:
            cbb = m_bpbb;
            break;
        default:
            break;
    }

    return pbb & cbb;
}

int GameState::getEnPassant() {
    return m_enPassant;
}

int GameState::getCastlingRights() {
    return m_castlingRights;
}

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

// PRIVATE METHOD DEFINITIONS
// =============================================================================
// =============================================================================


bool GameState::isSquareAttacked(int sq, PlayerColour col) {
    uint64_t sqBB = 1ull << sq;
    uint64_t all = m_wpbb | m_bpbb;

    uint64_t pawns = pieceBB({PieceType::PAWN, col});
    uint64_t pawnAttacks = col == PlayerColour::WHITE ? 
        (((~Rays::FILE_A & pawns) << 7) | ((~Rays::FILE_H & pawns) << 9)) : ((~Rays::FILE_H & pawns) >> 7 | (~Rays::FILE_A & pawns) >> 9);

    if (sqBB & pawnAttacks) {
        return true;
    }

    // Check knight attacks
    uint64_t knights = pieceBB({PieceType::KNIGHT, col});
    if (Attacks::knightAttacks[sq] & knights) {
        return true;
    }

    // Check bishop, queen attacks
    uint64_t bishops = pieceBB({PieceType::BISHOP, col});
    uint64_t queens = pieceBB({PieceType::QUEEN, col});
    
    uint64_t crossAttacks = Magic::getBishopMoves(sq, all);
    if (crossAttacks & (bishops | queens)) {
        return true;
    }

    // Check rook, queen attacks
    uint64_t rooks = pieceBB({PieceType::ROOK, col});
    uint64_t plusAttacks = Magic::getRookMoves(sq, all);
    if (plusAttacks & (rooks | queens)) {
        return true;
    }

    // Check king attacks
    uint64_t king = pieceBB({PieceType::KING, col});
    if (Attacks::kingAttacks[sq] & king) {
        return true;
    }

    return false;
}
