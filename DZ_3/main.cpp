#include <iostream>

#include "mstring.h"

using namespace std;

int main()
{
        mstring u("Hello"), v("world!"), w(v), z;

        cout << "u+v = " << u+" "+ v << endl;
        if (u == w)
                w = 2*u + w;
        else
                w = u + v*2;
        cout << "w = " << w << endl;
        w[10] = '?';
        cout << "w = " << w << endl;
        cin >> z;
        cout << "z = " << z << endl;
        return 0;
}

