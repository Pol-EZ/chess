#include "Position.h"

Position::Position() {
	x = 0;
	y = 0;
}

Position::Position(int x, int y) : x(x), y(y) {}

Position Position::operator=(int other) {
	x = other;
	y = other;

	return *this;
}

Position Position::operator=(Position other) {
	x = other.x;
	y = other.y;

	return *this;
}