#include <iostream>

class Quotient
{
  private:
    int num;
    unsigned int den;

    int gcd(int a, int b) const;

  public:
    Quotient(int n = 0, int d = 1)
    {
      if (d == 0)
      {
        d = 1;
      }
      else if (d < 0)
      {
        n *= -1;
        d *= -1;
      }
      
      const int div = gcd(n, d);
      
      num = n / div;
      den = d / div;
    }

    void print() const;
};

/*
int main()
{
  while (true)
  {
    int n, d;
    std::cin >> n >> d;
    Quotient q(n, d);
    q.print();
  }
  return 0;
}
*/

int Quotient::gcd(int a, int b) const
{
  int temp;
  
  if (a < 0)
  {
    a *= -1;
  }

  if (a < b)
  {
    temp = a;
    a = b;
    b = temp;
  }

  while (b != 0) 
  {
    a = a % b;
    if (a < b)
    {
      temp = a;
      a = b;
      b = temp;
    }
  }

  return a;
}

void Quotient::print() const
{
  if (den == 1)
  {
    std::cout << num << std::endl;
  }
  else
  {
    std::cout << num << "/" << den << std::endl;
  }
}
