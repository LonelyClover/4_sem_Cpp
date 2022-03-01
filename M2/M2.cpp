#include <iostream>
#include <cstring>

char* left(char *str, int N)
{

  char *ptr = str;

  if (N < 0)
  {
    *str = '\0';
		return str;
  }

  while (*ptr != '\0' && N != 0)
  {
    ptr += 1;
    N -= 1;
  }

  *ptr = '\0';

  return str;
}

int count_digits(unsigned long num)
{
  int count = 0;
  
  do
  {
    num /= 10;
    count += 1;
  }
  while (num != 0);

  return count;
}

unsigned long left(unsigned long num, int N)
{
  if (N < 0)
  {
    return 0;
  }

  N = count_digits(num) - N;
  
  if (N < 0)
  {
    return num;
  }

  while (num > 0 && N > 0)
  {
    num /= 10;
    N -= 1;
  }

  return num;
}

using namespace std;

int main()
{
  char token[7] = {};
  cin.getline(token, 7);

  if (strcmp(token, "string") == 0)
  {
    char str[101] = {};
    int N;
    
    cin.getline(str, 101);
    cin >> N;

    cout << left(str, N) << endl;
  }
  else if (strcmp(token, "number") == 0)
  {
    unsigned long num;
    int N;
    cin >> num >> N;

    cout << left(num, N) << endl;
  }
  else
  {
    cout << 0 << endl;
  }

  return 0;
}

