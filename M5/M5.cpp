//	FINISHED	//

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
    double euc_norm(void) const;
    double max_norm(void) const;
    void print(void) const;

		const Vec operator+(const Vec& op) const;
		const Vec operator-(const Vec& op) const;
		const Vec operator*(double a) const;
		const Vec& operator=(const Vec& op);
		bool operator==(const Vec& op) const;
		double& operator[](int i) const;
		
		friend const Vec operator*(double a, const Vec& op);
		friend std::ostream& operator<<(std::ostream& stream, const Vec& op);
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
  len = vec.len;
  v = new double[len];
	memcpy(v, vec.v, len * sizeof(double));

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

const Vec Vec::operator+(const Vec& op) const
{
	Vec tmp = Vec(len);

	for (int i = 0; i < len; i++)
	{
		tmp[i] = v[i] + op[i];
	}

	return tmp;
}

const Vec Vec::operator-(const Vec& op) const
{
	Vec tmp = Vec(len);

	for (int i = 0; i < len; i++)
	{
		tmp[i] = v[i] - op[i];
	}

	return tmp;
}

const Vec Vec::operator*(double a) const
{
	Vec tmp = Vec(len);

	for (int i = 0; i < len; i++)
	{
		tmp[i] = v[i] * a;
	}

	return tmp;
}

const Vec& Vec::operator=(const Vec& op)
{
	if (&op == this)
	{
		return *this;
	}

	len = op.len;

	delete[] v;
	v = new double[len];

	memcpy(v, op.v, len * sizeof(double));

	return *this;
}

bool Vec::operator==(const Vec& op) const
{
	if (len != op.len)
	{
		return false;
	}

	return !memcmp(v, op.v, len * sizeof(double));
}

double& Vec::operator[](int i) const
{
	return v[i];
}

const Vec operator*(double a, const Vec& op)
{	
	Vec tmp = Vec(op.len);

	for (int i = 0; i < op.len; i++)
	{
		tmp[i] = op[i] * a;
	}

	return tmp;
}

std::ostream& operator<<(std::ostream& stream, const Vec& op)
{
	stream << '(';
	
	for (int i = 0; i < op.len; i++)
	{
		stream << op[i];
		if (i != op.len - 1)
		{
			stream << ',';
		}
	}

	stream << ')';

	return stream;
}


/*
using namespace std;
int main()
{
        double y1[4] = {1,2,3,4};
        double y2[4] = {-2,1,3,-3};

        Vec u(4, y1), v(4, y2);
        Vec w(4);
				
        cout << "u = " << u << endl;
        cout << "v = " << v << endl;
        w = u = u;
        cout << "w = u = " << w << endl;
        w = u + v;
        cout << "w = 4.*u + v*3 = " << w << endl;
        w[2] = 3;
        w[0] = -1;
        cout << "w = " << w << endl;

        return 0;
}
*/
