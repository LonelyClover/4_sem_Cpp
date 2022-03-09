#include <iostream>
#include "mstring.h"

using namespace std;

void error()
{
	mstring str("abc");
	cout << str[2] << endl;
}
