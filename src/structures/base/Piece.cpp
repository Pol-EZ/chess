#include "Piece.h"

#include "../PiecesImport.h"

Piece::Piece(Color color) : color(color) {}

Piece::~Piece() {}

Color Piece::getColor() const {
    return color;
}
