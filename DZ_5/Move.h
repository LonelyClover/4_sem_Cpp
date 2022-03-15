struct Move
{
	enum Figure_id
	{
		KING = 0,
		QUEEN,
		ROOK,
		BISHOP,
		KNIGHT,
	} figure_id;
	int start[2];
	int end[2];

	Move(const char *str);
};


