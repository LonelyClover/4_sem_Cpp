enum Figure_id
{
	KING = 0,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
};

struct Move
{
	Figure_id figure_id;
	int start[2];
	int end[2];
};

Move parce_move(const char *str);

