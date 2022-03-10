#include <iostream>
#include "mstring.h"

using namespace std;

void error()
{
	mstring str;
	str.insert("", 1);
	cout << "QQQ" << endl;
}
