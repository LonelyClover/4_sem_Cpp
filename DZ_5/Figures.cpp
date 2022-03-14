#include <cmath>
#include "Figures.h"

bool King::move(int *start, int *end)
{
	return
	(
		abs(end[0] - start[0]) <= 1 &&
		abs(end[1] - start[1]) <= 1
	)
	&&
	!(
		start[0] == end[0] &&
		start[1] == end[1]
	);
}

bool Queen::move(int *start, int *end)
{

	return
	(
		start[0] == end[0] ||
		start[1] == end[1] ||
		start[0] - start[1] == end[0] - end[1] ||
		start[0] + start[1] == end[0] + end[1]
	)
	&&
	!(
		start[0] == end[0] &&
		start[1] == end[1]
	);
}

bool Rook::move(int *start, int *end)
{
	return
	(
		start[0] == end[0] ||
		start[1] == end[1]
	)
	&&
	!(
		start[0] == end[0] &&
		start[1] == end[1]
	);
}

bool Bishop::move(int *start, int *end)
{
	return
	(
		start[0] - start[1] == end[0] - end[1] ||
		start[0] + start[1] == end[0] + end[1]
	)
	&&
	!(
		start[0] == end[0] &&
		start[1] == end[1]
	);
}

bool Knight::move(int *start, int *end)
{
	return
	(
		(
			abs(end[0] - start[0]) == 1 &&
			abs(end[1] - start[1]) == 2
		)
		||
		(
			abs(end[0] - start[0]) == 2 &&
			abs(end[1] - start[1]) == 1
		)
	)
	&&
	!(
		start[0] == end[0] &&
		start[1] == end[1]
	);
}

