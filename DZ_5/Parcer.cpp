#include <cstring>
#include "Parcer.h"

Move parce_move(const char *str)
{
	if (strlen(str) != 7 || str[1] != ' ' || str[4] != ' ')
	{
		throw "Invalid move representation: wrong format";
	}
	
	Move move = Move();

	switch (str[0])
	{
		case 'K':
			move.figure_id = KING;
			break;

		case 'Q':
			move.figure_id = QUEEN;
			break;

		case 'R':
			move.figure_id = ROOK;
			break;

		case 'B':
			move.figure_id = BISHOP;
			break;

		case 'N':
			move.figure_id = KNIGHT;
			break;
		
		default:
			throw "Invalid move representation: wrong figure letter";

	}

	if (str[2] < 'a' || str[2] > 'h')
	{
		throw "Invalid move representation: wrong starting file";
	}
	move.start[0] = str[2] - 'a';

	if (str[3] < '1' || str[3] > '8')
	{
		throw "Invalid move representation: wrong starting rank";
	}
	move.start[1] = str[3] - '1';

	if (str[5] < 'a' || str[5] > 'h')
	{
		throw "Invalid move representation: wrong ending file";
	}
	move.end[0] = str[5] - 'a';

	if (str[6] < '1' || str[6] > '8')
	{
		throw "Invalid move representation: wrong ending rank";
	}
	move.end[1] = str[6] - '1';

	return move;
}

