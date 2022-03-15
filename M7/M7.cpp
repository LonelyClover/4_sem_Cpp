#include <iostream>
#include <cstring>
#include <cmath>

class Vec
{
  private:
    double *v;
    int len;

  public:
    Vec(int len_, const double *v_ = 0);
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


class Exception
{
	public:
		enum err_t
		{
			LEN_ERR,
			COORD_ERR,
			INDEX_ERR,
			DIFF_LEN_ERR,
		};

	private:
		err_t err;
		union
		{
			char method[6];
			int index;
			int len[2];
		} arg;
	
	public:
		Exception(err_t err_);
		Exception(err_t err_, const char *method);
		Exception(err_t err_, int index);
		Exception(err_t err_, int len1, int len2);
		
		friend std::ostream& operator<<(std::ostream& stream, Exception& exc);
};

Vec::Vec(int len_, const double *v_)
{
  if (len_ <= 0)
	{
		throw Exception(Exception::LEN_ERR);
	}

	v = new double[len_];
  len = len_;

  if (v_ != 0)
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
	if (coord < 0 || coord >= len)
  {
		throw Exception(Exception::COORD_ERR, "set()");
  }

  v[coord] = arg;
  
	return;
}

double Vec::get(int coord) const
{
  if (coord < 0 || coord >= len)
  {
		throw Exception(Exception::COORD_ERR, "get()");
  }

  return v[coord];
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
	if (len != op.len)
	{
		throw Exception(Exception::DIFF_LEN_ERR, len, op.len);
	}

	Vec tmp = Vec(len);

	for (int i = 0; i < len; i++)
	{
		tmp[i] = v[i] + op[i];
	}

	return tmp;
}

const Vec Vec::operator-(const Vec& op) const
{
	if (len != op.len)
	{
		throw Exception(Exception::DIFF_LEN_ERR, len, op.len);
	}

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
	if (i < 0 || i >= len)
	{
		throw Exception(Exception::INDEX_ERR, i);
	}

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

Exception::Exception(err_t err_)
{
	err = err_;
	return;
}

Exception::Exception(err_t err_, const char *method)
{
	err = err_;
	strcpy(arg.method, method);
	return;
}

Exception::Exception(err_t err_, int index)
{
	err = err_;
	arg.index = index;
	return;
}

Exception::Exception(err_t err_, int len1, int len2)
{
	err = err_;
	arg.len[0] = len1;
	arg.len[1] = len2;
	return;
}

std::ostream& operator<<(std::ostream& stream, Exception& exc)
{
	stream << "Exception: ";

	switch(exc.err)
	{
		case Exception::LEN_ERR:
			stream << "length error";
			break;
		
		case Exception::COORD_ERR:
			stream << "coordinate error in " << exc.arg.method;
			break;

		case Exception::INDEX_ERR:
			stream << "incorrect indexing: " << exc.arg.index;
			break;

		case Exception::DIFF_LEN_ERR:
			stream << "addition of vectors of different lengths: " << exc.arg.len[0] << ' ' << exc.arg.len[1];
			break; 
	}

	return stream;
}

void error(void);

using namespace std;

int main()
{
	try
	{
		error();
	}
	catch(Exception& exc)
	{
		cerr << exc << endl;
	}
	catch(...)
	{
		cerr << "Exception: unknown error" << endl;
	}
  return 0;
}

/*
void error()
{
     Vec v1(3), v2(5), v3(4);

      v3 = v1+v2;

}
*/
