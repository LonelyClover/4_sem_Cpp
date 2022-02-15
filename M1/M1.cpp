#include <iostream>
#include <cmath>

int count_symbols(int arg)
{
  if (arg < 0)
  {
    arg *= -1;
  }
  
  int count = 0;
  do
  {
    arg /= 10;
    count += 1;
  }
  while (arg > 0);

  return count;
}

int count_symbols(int *arr, int n)
{
  int count = 0;
  
  for (int i = 0; i < n; i++)
  {
    count += count_symbols(arr[i]);
  }

  return count;
}

int count_symbols(int *ptr)
{
  return count_symbols(*ptr);
}

int count_symbols(const char *str)
{
  int count = 0;
  
  while (*str != '\0')
  {
    str += 1;
    count += 1;
  }

  return count;
}

int count_symbols(double f)
{
  if (f < 0)
  {
    f *= -1;
  }

  int count = 0;

  do 
  {
    f /= 10;
    count += 1;
  }
  while (f >= 1);

  return count;
}

int count_symbols(double f, int n)
{
  return count_symbols(f) + n;
}

/*
using namespace std;

int main()
{
  int array[7] = {18,20,3,493, 7};
  cout << count_symbols("mather") << endl;
  cout << count_symbols(12389) << endl;
  cout << count_symbols(3.14, 3) << endl;
  cout << count_symbols(123446789.56) << endl;
  cout << count_symbols(array, 5) << endl;
  cout << count_symbols(array) << endl;
  return 0;
}
*/
