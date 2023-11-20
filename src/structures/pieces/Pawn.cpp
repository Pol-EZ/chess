#include "Pawn.h"

#include <iostream>

#include "../base/Board.h"

Pawn::Pawn(Color color, Board* board) : Piece(color), board(board) {}

PieceType Pawn::getType() const {
    return PAWN;
}

bool Pawn::isValidMove(Position& origin, Position& dest) const {
    int deltaX = dest.x - origin.x;
    int deltaY = dest.y - origin.y;

    int direction = getColor() == BLACK ? -1 : 1;
    // Verifica si el movimiento es hacia adelante
    bool checkFront = origin.x == dest.x && origin.y == (dest.y + 1 * direction);

    // Verifica si es el primer movimiento y puede avanzar dos casillas
    bool checkInitial = origin.x == dest.x && (getColor() == BLACK ? origin.y == 1 && dest.y == 3 : origin.y == 6 && dest.y == 4);

    // Obtiene la pieza en la posición de destino
    Piece* piece = board->getPiece(dest);

    // Verifica si hay una pieza enemiga en la casilla diagonal para realizar la captura
    bool isEnemyPiece = piece != nullptr && piece->getColor() != getColor();
    bool checkCapture = std::abs(deltaX) == 1 && deltaY == direction * -1 && isEnemyPiece;

    // Verifica si no hay piezas en el camino
    bool noPieceInPath = true;
    if (deltaY < 0) {
        // Movimiento hacia adelante
        for (int i = origin.y - 1; i > dest.y; --i) {
            Position pos = Position(origin.x, i );
            if (board->getPiece(pos) != nullptr) {
                noPieceInPath = false;
                break;
            }
        }
    }

    // Combina todas las condiciones
    return (checkFront || checkInitial || checkCapture) && noPieceInPath;
}