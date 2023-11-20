#include "Knight.h"

#include <iostream>

Knight::Knight(Color color) : Piece(color) {}

PieceType Knight::getType() const {
    return KNIGHT;
}

bool Knight::isValidMove(Position& origin, Position& dest) const {
    int deltaX = std::abs(dest.x - origin.x);
    int deltaY = std::abs(dest.y - origin.y);

    bool isLShapedMove = (deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1);

    return isLShapedMove;
}