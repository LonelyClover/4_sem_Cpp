#include <iostream>
#include "ChessChecker.h"

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
		//cerr << str << endl;
		cout << "NO" << endl;
	}
	catch(...)
	{
		cerr << "Unknown error" << endl;
	}

	return 0;
}
