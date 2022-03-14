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

