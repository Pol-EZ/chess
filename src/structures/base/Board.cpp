#include "Board.h"

#include <iostream>

#include "../PiecesImport.h"

Board::Board() {
    // Inicializa todas las posiciones del tablero con nullptr
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            squares[row][col] = nullptr;
        }
    }

    // Piezas negras
    squares[0][0] = new Rook(BLACK, this);
    squares[0][1] = new Knight(BLACK);
    squares[0][2] = new Bishop(BLACK, this);
    squares[0][3] = new King(BLACK);
    squares[0][4] = new Queen(BLACK, this);
    squares[0][5] = new Bishop(BLACK, this);
    squares[0][6] = new Knight(BLACK);
    squares[0][7] = new Rook(BLACK, this);

    // Peones negros
    for (int col = 0; col < 8; col++) {
        squares[1][col] = new Pawn(BLACK, this);
    }

    // Piezas blancas
    squares[7][0] = new Rook(WHITE, this);
    squares[7][1] = new Knight(WHITE);
    squares[7][2] = new Bishop(WHITE, this);
    squares[7][3] = new King(WHITE);
    squares[7][4] = new Queen(WHITE, this);
    squares[7][5] = new Bishop(WHITE, this);
    squares[7][6] = new Knight(WHITE);
    squares[7][7] = new Rook(WHITE, this);

    // Peones blancos
    for (int col = 0; col < 8; col++) {
        squares[6][col] = new Pawn(WHITE, this);
    }
}

void Board::print() const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = squares[row][col];

            if (piece == nullptr) {
                std::cout << ". ";
                continue;
            }

            switch (piece->getType()) {
                case PAWN:
                    std::cout << (piece->getColor() == WHITE ? "p " : "P ");
                    break;

                case ROOK:
                    std::cout << (piece->getColor() == WHITE ? "r " : "R ");
                    break;

                case KNIGHT:
                    std::cout << (piece->getColor() == WHITE ? "n " : "N ");
                    break;

                case BISHOP:
                    std::cout << (piece->getColor() == WHITE ? "b " : "B ");
                    break;

                case QUEEN:
                    std::cout << (piece->getColor() == WHITE ? "q " : "Q ");
                    break;

                case KING:
                    std::cout << (piece->getColor() == WHITE ? "k " : "K ");
                    break;
            }
        }
        std::cout << std::endl;
    }
}

Piece* Board::getPiece(Position& position) const {
	return squares[position.y][position.x];
}

void Board::setPiece(Piece* piece, Position& position) {
    squares[position.y][position.x] = piece;
}

Position Board::getKingPos(Color color) const {
    Position kingPosition = { -1, -1 }; // Valor predeterminado si no se encuentra el rey

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = squares[row][col];

            if (piece != nullptr && piece->getColor() == color && dynamic_cast<King*>(piece) != nullptr) {
                kingPosition.y = row;
                kingPosition.x = col;
                break; // Se encontró el rey, salir del bucle
            }
        }
    }

    return kingPosition;
}

