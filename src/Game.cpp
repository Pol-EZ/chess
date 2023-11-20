#include "Game.h"

#include <iostream>
#include <vector>

void Game::mainLoop() {
	Position originPos;
	Position destPos;

	bool inGame = true;
	while (inGame) {
		// Limpieza de la consola
		system("cls");
		
		// Comprobación de jaque
		check = inCheck(board, turn);

		// Escritura de datos y dibujado de la tabla
		std::cout << "Turno de las piezas " << (turn == WHITE ? "blancas" : "negras") << '.' << std::endl;
		if (error != nullptr) std::cout << error << std::endl;
		if (check != NONE) std::cout << "Estás en jaque!" << std::endl;
		drawBoard();

		error = nullptr;

		// Ingreso de las posiciones
		originPos = requestPosition("Ingrese la posición de origen (ej: 4h): ");
		destPos = requestPosition("Ingrese la posición de destino (ej: 3h): ");

		// Comprobación de las posiciones
		if (!isValidPos(originPos) || !isValidPos(destPos)) {
			error = (char*)"La posición ingresada, de destino u origen, no es válida.";
			continue;
		};

		// Comprobación de jaque mate, salida de jaque y rey ahogado
		if (check != NONE) {
			if (!canExitsCheck(turn)) {
				std::cout << "Jaque mate! Las piezas " << (turn == WHITE ? "negras" : "blancas") << " ganan!" << std::endl;
				inGame = false;
				continue;
			}
			if (!exitsCheck(originPos, destPos)) {
				error = (char*)"El movimiento seleccionado no te saca de jaque.";
				continue;
			}
		} else {
			if (!hasLegalMove(turn)) {
				std::cout << "Rey ahogado! Las piezas " << (turn == WHITE ? "negras" : "blancas") << " ganan!" << std::endl;
				inGame = false;
				continue;
			}
		}

		// Movimiento de la pieza
		bool pieceMoved = movePiece(originPos, destPos);
		// Comprobación de que la pieza se haya movido
		if (!pieceMoved) continue;

		// Cambio de turno y reinicio de la variable "error".
		endTurn();
	}

	return;
}

void Game::drawBoard() const {
	std::cout << std::endl;
	std::cout << "    a b c d e f g h" << std::endl;
	std::cout << "   ----------------" << std::endl;
	for (int row = 0; row < 8; row++) {
		std::cout << row + 1 << " | ";
		for (int col = 0; col < 8; col++) {
			Position position = Position(col, row);
			Piece* piece = board.getPiece(position);

			std::cout << getPieceIcon(piece) << ' ';
		}
		std::cout << std::endl;
	}

	if (!capturedPieces.empty()) {
		std::cout << "Piezas capturadas: ";
		for (int index = 0; index < capturedPieces.size(); index++) {
			std::cout << getPieceIcon(capturedPieces[index]);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	return;
}

Position Game::requestPosition(const char* message) const {
	Position position;
	char auxInput[3];

	std::cout << message;
	std::cin.getline(auxInput, 3, '\n');

	position.y = (int)(auxInput[0] - 49);
	position.x = (int)(auxInput[1] - 97);

	std::cout << position.y << " " << position.x << std::endl;

	return position;
}

bool Game::isValidPos(Position position) const {
	return (position.x >= 0 && position.x < 8) && (position.y >= 0 && position.y < 8);
}

Color Game::inCheck(Board board, Color kingColor) const {
	Position kingPos = board.getKingPos(kingColor);
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			Position piecePos = Position(col, row);
			Piece* enemyPiece = board.getPiece(piecePos);

			if (enemyPiece != nullptr && enemyPiece->getColor() != kingColor) {
				if (enemyPiece->isValidMove(piecePos, kingPos)) return enemyPiece->getColor();
			}
		}
	}

	return NONE;
}

bool Game::canExitsCheck(Color kingColor) const {
	// Itera sobre todas las casillas del tablero
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			Position pos = Position(col, row);
			Piece* piece = board.getPiece(pos);

			// Si la casilla está vacía o la pieza no es del color del jugador actual, continúa con la siguiente casilla
			if (piece == nullptr || piece->getColor() != kingColor) continue;

			// Itera sobre todas las casillas del tablero para encontrar un movimiento válido
			for (int destRow = 0; destRow < 8; destRow++) {
				for (int destCol = 0; destCol < 8; destCol++) {
					Position dest = Position(destCol, destRow);

					// Si el movimiento es válido, crea un tablero temporal y realiza el movimiento
					if (piece->isValidMove(pos, dest)) {
						Board tempBoard = board;
						tempBoard.setPiece(nullptr, pos);
						tempBoard.setPiece(piece, dest);

						// Si el rey no está en jaque en el tablero temporal, entonces hay un movimiento que puede sacar al rey del jaque
						if (inCheck(tempBoard, kingColor) == NONE) return true;
					}
				}
			}
		}
	}

	// Si no se ha encontrado ningún movimiento que pueda sacar al rey del jaque, devuelve false
	return false;
}

bool Game::exitsCheck(Position origin, Position dest) const {
	Board tempBoard = board;
	tempBoard.setPiece(tempBoard.getPiece(origin), dest);
	return inCheck(tempBoard, turn);
}

bool Game::hasLegalMove(Color color) const {
	// Itera sobre todas las casillas del tablero
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			Position pos = Position(col, row);
			Piece* piece = board.getPiece(pos);

			// Si la casilla está vacía o la pieza no es del color del jugador actual, continúa con la siguiente casilla
			if (piece == nullptr || piece->getColor() != color) continue;

			// Itera sobre todas las casillas del tablero para encontrar un movimiento válido
			for (int destRow = 0; destRow < 8; destRow++) {
				for (int destCol = 0; destCol < 8; destCol++) {
					Position dest = Position(destCol, destRow);

					// Si el movimiento es válido y saca al rey del jaque, entonces hay un movimiento legal disponible
					if (piece->isValidMove(pos, dest) && exitsCheck(pos, dest)) return true;
				}
			}
		}
	}

	// Si no se ha encontrado ningún movimiento legal, devuelve false
	return false;
}

bool Game::movePiece(Position origin, Position dest) {
	Piece* piece = board.getPiece(origin);
	Piece* enemyPiece = board.getPiece(dest);

	if (piece == nullptr) error = (char*)"La pieza seleccionada no existe.";
	else {
		if (piece->getColor() != turn) error = (char*)"La pieza seleccionada no es de tu color.";
		if (!piece->isValidMove(origin, dest)) error = (char*)"El movimiento no es válido.";
	}
	if (error != nullptr) return false;

	if (enemyPiece != nullptr) capturedPieces.push_back(enemyPiece);

	board.setPiece(nullptr, origin);
	board.setPiece(piece, dest);

	return true;
}

void Game::endTurn() {
	turn = (turn == WHITE ? BLACK : WHITE);
	error = nullptr;
}

char Game::getPieceIcon(Piece* piece) const {
	char icon = '.';
	if (piece != nullptr) {
		switch (piece->getType()) {
			case PAWN:
				icon = 'p';
				break;
			case ROOK:
				icon = 'r';
				break;
			case KNIGHT:
				icon = 'n';
				break;
			case BISHOP:
				icon = 'b';
				break;
			case QUEEN:
				icon = 'q';
				break;
			case KING:
				icon = 'k';
				break;

		}
		if (piece->getColor() == BLACK) icon -= 32;
	}

	return icon;
}