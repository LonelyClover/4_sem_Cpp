//	FINISHED	//

#include <iostream>
#include <cstring>

class Figure
{
	public:
		virtual ~Figure(void) { return; }
		virtual bool move(int *start, int *end) = 0;
};

class King : public Figure
{
	public:
		bool move(int *start, int *end);
};

class Queen : public Figure
{
	public:
		bool move(int *start, int *end);
};

class Rook : public Figure
{
	public:
		bool move(int *start, int *end);
};

class Bishop : public Figure
{
	public:
		bool move(int *start, int *end);
};

class Knight : public Figure
{
	public:
		bool move(int *start, int *end);
};


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

	Move(const char* str);
};

class ChessChecker 
{
	private:
		Figure *figures[5];
		char str[8];
	
	public:
		ChessChecker(void);
		~ChessChecker(void);
		void load_move(std::istream& stream);
		bool check_move(void) const;
};

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

using namespace std;

int main()
{
	try
	{
		ChessChecker checker = ChessChecker();
		
		checker.load_move(cin);

		if (checker.check_move())
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	catch(const char *str)
	{
	//	cerr << str << endl;
		cout << "NO" << endl;
	}
	catch(...)
	{
		cerr << "Unknown error" << endl;
	}

	return 0;
}
