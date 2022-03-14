#include "Figures.h"

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

