#pragma once

#include "../base/Piece.h"
#include "../types/Position.h"
#include "../types/Color.h"
#include "../types/PieceType.h"

class Knight : public Piece {
public:
	Knight(Color color);

	PieceType getType() const override;
	bool isValidMove(Position& origin, Position& dest) const override;
};