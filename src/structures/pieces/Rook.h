#pragma once

#include "../base/Piece.h"
#include "../types/Position.h"
#include "../types/Color.h"
#include "../types/PieceType.h"

class Board;

class Rook : public Piece {
private:
	Board* board;

public:
	Rook(Color color, Board* board);

	PieceType getType() const override;
	bool isValidMove(Position& origin, Position& dest) const override;
};