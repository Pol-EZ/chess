#pragma once

#include <iostream>
#include <vector>

#include "structures/BaseImport.h"
#include "structures/TypesImport.h"

class Game {
private:
	Board board;
	std::vector<Piece*> capturedPieces;
	Color turn = WHITE;
	Color check = NONE;
	char* error = nullptr;

public:
	void mainLoop();

private:
	void drawBoard() const;
	Position requestPosition(const char* message) const;
	bool isValidPos(Position position) const;
	Color inCheck(Board board, Color kingColor) const;
	bool canExitsCheck(Color kingColor) const;
	bool exitsCheck(Position origin, Position dest) const;
	bool hasLegalMove(Color color) const;
	bool movePiece(Position origin, Position dest);
	void endTurn();

	char getPieceIcon(Piece* piece) const;
};