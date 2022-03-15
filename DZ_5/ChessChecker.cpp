#include <iostream>
#include "Move.h"
#include "ChessChecker.h"

ChessChecker::ChessChecker(void)
{
	figures[0] = new King();
	figures[1] = new Queen();
	figures[2] = new Rook();
	figures[3] = new Bishop();
	figures[4] = new Knight();
	
	str[0] = '\0';

	return;
}

ChessChecker::~ChessChecker(void)
{
	for (int i = 0; i < 4; i++)
	{
		delete figures[i];
	}

	return;
}

void ChessChecker::load_move(std::istream& stream)
{
	stream.getline(str, 8);
	return;
}

bool ChessChecker::check_move(void) const
{
	Move move(str);

	return figures[move.figure_id] -> move(move.start, move.end);
}

