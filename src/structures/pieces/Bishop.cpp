#include "Bishop.h"

#include <iostream>

#include "../base/Board.h"

Bishop::Bishop(Color color, Board* board) : Piece(color), board(board) {}

PieceType Bishop::getType() const {
	return BISHOP;
}

bool Bishop::isValidMove(Position& origin, Position& dest) const {
    int deltaX = dest.x - origin.x;
    int deltaY = dest.y - origin.y;

    // Verificar si el movimiento es diagonal
    if (std::abs(deltaX) != std::abs(deltaY)) {
        return false;
    }

    // Verificar si hay piezas en el camino
    int stepX = (deltaX > 0) ? 1 : -1;
    int stepY = (deltaY > 0) ? 1 : -1;

    int currentX = origin.x + stepX;
    int currentY = origin.y + stepY;

    while (currentX != dest.x && currentY != dest.y) {
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