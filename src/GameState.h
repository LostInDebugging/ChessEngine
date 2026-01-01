#include <iostream>
#include <string>
#include <limits>

constexpr int BB_COUNT = 15;

enum PlayerColour {
    BLACK, 
    WHITE
};

enum bbVal {
    BLACKPAWNS,
    BLACKKNIGHTS,
    BLACKBISHOPS,
    BLACKROOKS,
    BLACKQUEENS,
    BLACKKING,
    WHITEPAWNS,
    WHITEKNIGHTS,
    WHITEBISHOPS,
    WHITEROOKS,
    WHITEQUEENS,
    WHITEKING,
    BLACKPIECES,
    WHITEPIECES,
    EMPTY
};

class GameState {
/*============================================================================*/
// PRIVATE MEMBER VARIABLES
private:
    uint64_t m_bboards[BB_COUNT];
    PlayerColour m_activeColour;
    int m_castlingRights;
    int m_enPassant;
    int m_halfMoveClock;
    int m_fullMoveCount;

/*============================================================================*/
// PUBLIC CALLABLE METHODS  
public:
    GameState(std::string FEN) {

    }

    // Create a new Chess game with the starting position
    GameState() {
        m_bboards[BLACKPAWNS] = 0b11111111ull << 48;
        m_bboards[WHITEPAWNS] = 0b11111111ull << 8;
        m_bboards[BLACKKNIGHTS] = 0b01000010ull << 56;
        m_bboards[WHITEKNIGHTS] = 0b01000010ull;
        m_bboards[BLACKBISHOPS] = 0b00100100ull << 56;
        m_bboards[WHITEBISHOPS] = 0b00100100ull;
        m_bboards[BLACKROOKS] = 0b10000001ull << 56;
        m_bboards[WHITEROOKS] = 0b10000001ull;
        m_bboards[BLACKQUEENS] = 0b00001000ull << 56;
        m_bboards[WHITEQUEENS] = 0b00001000ull;
        m_bboards[BLACKKING] = 0b00010000ull << 56;
        m_bboards[WHITEKING] = 0b00010000ull;
        m_bboards[BLACKPIECES] = 0b1111111111111111ull << 48;
        m_bboards[WHITEPIECES] = 0b1111111111111111ull;
        m_bboards[EMPTY] = std::numeric_limits<unsigned long long>::max() ^ (m_bboards[BLACKPIECES] | m_bboards[WHITEPIECES]);

        m_activeColour = WHITE;
        m_castlingRights = -1; // TODO: castling rights
        m_halfMoveClock = 0;
        m_fullMoveCount = 0;
    }

    // Return the pawn bitboard for reading
    uint64_t getPawnBB(PlayerColour colour) {
        if (colour == BLACK) {
            return m_bboards[BLACKPAWNS];
        }
        return m_bboards[WHITEPAWNS];
    }

    // Return the currently active colour
    PlayerColour getActiveColour() {
        return m_activeColour;
    }

    // Print the GameState
    void PrintGameState() {
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
/*============================================================================*/
// PRIVATE HELPER METHODS
private: 
    char getPieceChar(bbVal Piece) {
        switch(Piece) {
            case BLACKPAWNS:
                return 'p';
            case BLACKKNIGHTS:
                return 'n';
            case BLACKBISHOPS:
                return 'b';
            case BLACKROOKS:
                return 'r';
            case BLACKQUEENS:
                return 'q';
            case BLACKKING:
                return 'k';
            case WHITEPAWNS:
                return 'P';
            case WHITEKNIGHTS:
                return 'N';
            case WHITEBISHOPS:
                return 'B';
            case WHITEROOKS:
                return 'R';
            case WHITEQUEENS:
                return 'Q';
            case WHITEKING:
                return 'K';
            case EMPTY:
                return ' ';
        }
    }

    bbVal getPieceAtSquare(int square) {
        unsigned long long bitMask = 1ull << square;
        
        if (bitMask & m_bboards[EMPTY]) {
            return EMPTY;
        } else if (bitMask & m_bboards[WHITEPIECES]) {
            // return correct white piece
            if (bitMask & m_bboards[WHITEPAWNS]) {
                return WHITEPAWNS;
            } else if (bitMask & m_bboards[WHITEKNIGHTS]) {
                return WHITEKNIGHTS;
            } else if (bitMask & m_bboards[WHITEBISHOPS]) {
                return WHITEBISHOPS;
            } else if (bitMask & m_bboards[WHITEROOKS]) {
                return WHITEROOKS;
            } else if (bitMask & m_bboards[WHITEQUEENS]) {
                return WHITEQUEENS;
            } else if (bitMask & m_bboards[WHITEKING]) {
                return WHITEKING;
            }
        } else {
            // return correct black piece
            if (bitMask & m_bboards[BLACKPAWNS]) {
                return BLACKPAWNS;
            } else if (bitMask & m_bboards[BLACKKNIGHTS]) {
                return BLACKKNIGHTS;
            } else if (bitMask & m_bboards[BLACKBISHOPS]) {
                return BLACKBISHOPS;
            } else if (bitMask & m_bboards[BLACKROOKS]) {
                return BLACKROOKS;
            } else if (bitMask & m_bboards[BLACKQUEENS]) {
                return BLACKQUEENS;
            } else if (bitMask & m_bboards[BLACKKING]) {
                return BLACKKING;
            }
        }
    }
};
