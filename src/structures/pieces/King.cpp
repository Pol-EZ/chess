#include "King.h"

#include <iostream>

King::King(Color color) : Piece(color) {}

PieceType King::getType() const {
    return KING;
}

bool King::isValidMove(Position& origin, Position& dest) const {
    int deltaX = std::abs(dest.x - origin.x);
    int deltaY = std::abs(dest.y - origin.y);

    // One square horizontally, vertically or diagonally.
    return (deltaX <= 1 && deltaY <= 1);
}