#pragma once

#include "../types/Position.h"
#include "../base/Piece.h"
#include "../pieces/Pawn.h"

class Board {
private:
	Piece* squares[8][8];

public:
	Board();

	void print() const;
	Piece* getPiece(Position& position) const;
	void setPiece(Piece* piece, Position& position);
	Position getKingPos(Color color) const;
};