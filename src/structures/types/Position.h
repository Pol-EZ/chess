#pragma once

class Position {
public:
	Position();
	Position(int x, int y);

	int x;
	int y;

	Position operator=(int other);
	Position operator=(Position other);
};