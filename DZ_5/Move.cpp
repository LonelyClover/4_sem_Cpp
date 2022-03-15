#include <cstring>
#include "Move.h"

Move::Move(const char *str)
{
	if (strlen(str) != 7 || str[1] != ' ' || str[4] != ' ')
	{
		throw "Invalid move representation: wrong format";
	}

	switch (str[0])
	{
		case 'K':
			figure_id = KING;
			break;

		case 'Q':
			figure_id = QUEEN;
			break;

		case 'R':
			figure_id = ROOK;
			break;

		case 'B':
			figure_id = BISHOP;
			break;

		case 'N':
			figure_id = KNIGHT;
			break;
		
		default:
			throw "Invalid move representation: wrong figure letter";

	}

	if (str[2] < 'a' || str[2] > 'h')
	{
		throw "Invalid move representation: wrong starting file";
	}
	start[0] = str[2] - 'a';

	if (str[3] < '1' || str[3] > '8')
	{
		throw "Invalid move representation: wrong starting rank";
	}
	start[1] = str[3] - '1';

	if (str[5] < 'a' || str[5] > 'h')
	{
		throw "Invalid move representation: wrong ending file";
	}
	end[0] = str[5] - 'a';

	if (str[6] < '1' || str[6] > '8')
	{
		throw "Invalid move representation: wrong ending rank";
	}
	end[1] = str[6] - '1';

	return;
}

