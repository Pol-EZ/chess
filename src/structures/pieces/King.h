#pragma once

#include "../base/Piece.h"
#include "../types/Position.h"
#include "../types/Color.h"
#include "../types/PieceType.h"

class King : public Piece {
public:
	King(Color color);

	PieceType getType() const override;
	bool isValidMove(Position& origin, Position& dest) const override;
};