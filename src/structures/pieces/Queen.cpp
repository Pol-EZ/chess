#include "Queen.h"

#include <iostream>

Queen::Queen(Color color, Board* board) : Piece(color), board(board) {}

PieceType Queen::getType() const {
	return QUEEN;
}

bool Queen::isValidMove(Position& origin, Position& dest) const {
	// Horizontal and vertical
	bool checkVertical = origin.x == dest.x;
	bool checkHorizontal = origin.y == dest.y;

	// Diagonal
	int deltaX = std::abs(dest.x - origin.x);
	int deltaY = std::abs(dest.y - origin.y);

	return deltaX == deltaY || checkHorizontal || checkVertical;
}