#include <iostream>

#include "mstring.h"

using namespace std;

int main()
{
	try
	{
		error();
	}
	catch(Exception exc)
	{
		cerr << exc << endl;
		return 1;
	}
	return 0;
	
}
