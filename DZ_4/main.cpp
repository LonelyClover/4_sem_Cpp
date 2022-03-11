#include <iostream>

#include "mstring.h"

using namespace std;

int main()
{
	try
	{
		error();
	}
	catch(const Exception& exc)
	{
		cerr << exc << endl;
	}
	return 0;
	
}
