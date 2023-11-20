#pragma once

#include "../types/Position.h"
#include "../types/Color.h"
#include "../types/PieceType.h"

class Piece {
private:
	Color color;

public:
	Piece(Color color);
	~Piece();

	Color getColor() const;
	virtual PieceType getType() const = 0;
	virtual bool isValidMove(Position& origin, Position& dest) const = 0;
};