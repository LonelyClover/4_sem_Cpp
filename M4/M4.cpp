#include <iostream>
#include <cstring>
#include <cmath>

class Vec
{
  private:
    double *v;
    int len;

  public:
    Vec(int len_, const double *v_ = NULL);
    Vec(const Vec& vec);
    ~Vec(void);
    
    void set(double arg, int coord);
    double get(int coord) const;
    int getLen() const;
    double euc_norm(void) const;
    double max_norm(void) const;
    void print(void) const;
};

Vec::Vec(int len_, const double *v_)
{
  v = new double[len_];
  len = len_;

  if (v_ != NULL)
  {
    memcpy(v, v_, len_ * sizeof(double));
    return;
  }

  for (int i = 0; i < len; i++)
  {
    v[i] = 0;
  }

  return;
}

Vec::Vec(const Vec& vec)
{
  len = vec.getLen();
  v = new double[len];

  for (int i = 0; i < len; i++)
  {
    v[i] = vec.get(i);
  }

  return;
}

Vec::~Vec(void)
{
  delete[] v;
}

void Vec::set(double arg, int coord)
{
  if (coord >= 0 && coord < len)
  {
    v[coord] = arg;
  }

  return;
}

double Vec::get(int coord) const
{
  if (coord >= 0 && coord < len)
  {
    return v[coord];
  }

  return 0;
}

int Vec::getLen(void) const
{
  return len;
}

double Vec::euc_norm(void) const
{
  double s = 0;

  for (int i = 0; i < len; i++)
  {
    s += v[i] * v[i];
  }

  return sqrt(s);
}

double Vec::max_norm(void) const
{
  double m = 0;

  for (int i = 0; i < len; i++)
  {
    if (m < abs(v[i]))
    {
      m = abs(v[i]);
    }
  }

  return m;
}

void Vec::print(void) const
{
  std::cout << '(';
  for (int i = 0; i < len; i++)
  {
    std::cout << v[i];
    if (i != len - 1)
    {
      std::cout << ',';
    }
  }
  std::cout << ')' << std::endl;
}

/*
using namespace std;
int main(void)
{
    double y1[3] = {1,2,3};
    double y2[5] = {2,1,0,5,7};
    Vec x(3, y1), y(5, y2), z(4);
    Vec u = x;

    y.print();
    x.print();
    z.print();
    u.print();

    x.set(23, 2);  u.set(34, 1);  z.set(-3, 3);
    cout << "x[2] = " << x.get(2) << endl;
    cout << "u[1] = " << u.get(1) << endl;
    cout << "euc_norma y: " << y.euc_norm() << endl;
    cout << "max_norma z: " << z.max_norm() << endl;
    return 0;
}
*/
