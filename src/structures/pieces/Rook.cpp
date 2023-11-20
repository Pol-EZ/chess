#include "Rook.h"

#include "../base/Board.h"

Rook::Rook(Color color, Board* board) : Piece(color), board(board) {}

PieceType Rook::getType() const {
	return ROOK;
}

bool Rook::isValidMove(Position& origin, Position& dest) const {
    int deltaX = dest.x - origin.x;
    int deltaY = dest.y - origin.y;

    // Verificar si el movimiento es vertical u horizontal
    if (deltaX != 0 && deltaY != 0) {
        return false;
    }

    // Verificar si hay piezas en el camino
    int stepX = (deltaX > 0) ? 1 : (deltaX < 0) ? -1 : 0;
    int stepY = (deltaY > 0) ? 1 : (deltaY < 0) ? -1 : 0;

    int currentX = origin.x + stepX;
    int currentY = origin.y + stepY;

    while (currentX != dest.x || currentY != dest.y) {
        Position pos = Position(currentX, currentY);
        if (board->getPiece(pos) != nullptr) {
            // Hay una pieza en el camino
            return false;
        }
        currentX += stepX;
        currentY += stepY;
    }

    // No hay obstáculos en el camino
    return true;
}