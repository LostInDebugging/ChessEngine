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

    // Print the GameState
    void printGameState(GameState g, PrintGameStateMode mode) {
        if (mode == PRINT_ALL_BITBOARDS) {

        } else if (mode == PRINT_LETTER_REP) {
            std::cout << "---------------------------------\n";
            for (int i = 7; i >= 0; i--) {
                std::cout << "| ";
                for (int j = 0; j < 8; j++) {
                    Piece piece = g.getPieceAtSquare(i * 8 + j);
                    std::cout << getPieceChar(piece);
                    std::cout << " | ";
                }
                std::cout << "\n---------------------------------\n";
            }
        }
    }

    char getPieceChar(Piece Piece) {
        char pieceChar = 'x';
        switch(Piece.piece) {
            case PieceType::PAWN:
                pieceChar = 'p';
                break;
            case PieceType::KNIGHT:
                pieceChar = 'n';
                break;
            case PieceType::BISHOP:
                pieceChar = 'b';
                break;
            case PieceType::ROOK:
                pieceChar = 'r';
                break;
            case PieceType::QUEEN:
                pieceChar = 'q';
                break;
            case PieceType::KING:
                pieceChar = 'k';
                break;
            case PieceType::EMPTY:
                return ' ';
            default:
                // shouldn't reach here
                return 'x';
        }

        switch(Piece.colour) {
            case PlayerColour::WHITE:
                return toupper(pieceChar);
                break;
            case PlayerColour::BLACK:
                return pieceChar;
                break;
            default:
                // shouldn't reach here
                return 'x';
        }
    }

    int squareLetterMapToIndex(std::string square) {
        return (square[1] - '1') * 8 + (square[0] - 'a');
    }
}
