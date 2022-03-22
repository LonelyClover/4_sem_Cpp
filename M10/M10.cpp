#include <iostream>
#include <cstring>
#include <cmath>

template<typename T>
class Vec
{
  private:
    T *v;
    int len;

  public:
    Vec<T>(int len_, const T *v_ = 0);
    Vec<T>(const Vec& vec);
    ~Vec<T>(void);
    
    void set(T arg, int coord);
    T get(int coord) const;
    //double euc_norm(void) const;
    T max_norm(void) const;
    //void print(void) const;

		const Vec<T> operator+(const Vec<T>& op) const;
		//const Vec operator-(const Vec& op) const;
		const Vec<T> operator*(T a) const;
		T operator^(const Vec<T>& op) const;
		const Vec<T>& operator=(const Vec<T>& op);
		const Vec<T>& operator+=(const Vec<T>& op);
		bool operator==(const Vec<T>& op) const;
		T& operator[](int i) const;
		
		template<typename T1>
		friend const Vec<T1> operator*(T1 a, const Vec<T1>& op);
		
		template<typename T1>
		friend std::ostream& operator<<(std::ostream& stream, const Vec<T1>& op);
};


class Exception
{
	public:
		enum err_t
		{
			LEN_ERR,
			COORD_ERR,
			INDEX_ERR,
			ADD_ERR,
			MUL_ERR,
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

template<typename T>
Vec<T>::Vec(int len_, const T *v_)
{
  if (len_ <= 0)
	{
		throw Exception(Exception::LEN_ERR);
	}

	v = new T[len_];
  len = len_;

  if (v_ != 0)
  {
    memcpy(v, v_, len_ * sizeof(T));
    return;
  }

  for (int i = 0; i < len; i++)
  {
    v[i] = 0;
  }

  return;
}

template<typename T>
Vec<T>::Vec(const Vec<T>& vec)
{
  len = vec.len;
  v = new T[len];
	memcpy(v, vec.v, len * sizeof(T));

  return;
}

template<typename T>
Vec<T>::~Vec(void)
{
  delete[] v;
}

template<typename T>
void Vec<T>::set(T arg, int coord)
{
	if (coord < 0 || coord >= len)
  {
		throw Exception(Exception::COORD_ERR, "set()");
  }

  v[coord] = arg;
  
	return;
}

template<typename T>
T Vec<T>::get(int coord) const
{
  if (coord < 0 || coord >= len)
  {
		throw Exception(Exception::COORD_ERR, "get()");
  }

  return v[coord];
}

/*
double Vec::euc_norm(void) const
{
  T s = 0;

  for (int i = 0; i < len; i++)
  {
    s += v[i] * v[i];
  }

  return sqrt(s);
}
*/

template<typename T>
T Vec<T>::max_norm(void) const
{
  T m = 0;

  for (int i = 0; i < len; i++)
  {
    if (m < abs(v[i]))
    {
      m = abs(v[i]);
    }
  }

  return m;
}

/*
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
*/

template<typename T>
const Vec<T> Vec<T>::operator+(const Vec<T>& op) const
{
	if (len != op.len)
	{
		throw Exception(Exception::ADD_ERR, len, op.len);
	}

	Vec<T> tmp = Vec<T>(len);

	for (int i = 0; i < len; i++)
	{
		tmp[i] = v[i] + op[i];
	}

	return tmp;
}

/*
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
*/

template<typename T>
const Vec<T> Vec<T>::operator*(T a) const
{
	Vec<T> tmp = Vec<T>(len);

	for (int i = 0; i < len; i++)
	{
		tmp[i] = v[i] * a;
	}

	return tmp;
}

template<typename T>
T Vec<T>::operator^(const Vec& op) const
{
	if (len != op.len)
	{
		throw Exception(Exception::MUL_ERR, len, op.len);
	}

	T res = 0;

	for (int i = 0; i < len; i++)
	{
		res += v[i] * op[i];
	}

	return res;
}

template<typename T>
const Vec<T>& Vec<T>::operator=(const Vec<T>& op)
{
	if (&op == this)
	{
		return *this;
	}

	len = op.len;

	delete[] v;
	v = new T[len];

	memcpy(v, op.v, len * sizeof(T));

	return *this;
}

template<typename T>
const Vec<T>& Vec<T>::operator+=(const Vec<T>& op)
{
	if (len != op.len)
	{
		throw Exception(Exception::ADD_ERR, len, op.len);
	}

	for (int i = 0; i < len; i++)
	{
		v[i] += op[i];
	}

	return *this;
}

template<typename T>
bool Vec<T>::operator==(const Vec<T>& op) const
{
	if (len != op.len)
	{
		return false;
	}

	return !memcmp(v, op.v, len * sizeof(T));
}

template<typename T>
T& Vec<T>::operator[](int i) const
{
	if (i < 0 || i >= len)
	{
		throw Exception(Exception::INDEX_ERR, i);
	}

	return v[i];
}

template<typename T>
const Vec<T> operator*(T a, const Vec<T>& op)
{	
	Vec<T> tmp = Vec<T>(op.len);

	for (int i = 0; i < op.len; i++)
	{
		tmp[i] = op[i] * a;
	}

	return tmp;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vec<T>& op)
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

		case Exception::ADD_ERR:
			stream << "addition of vectors of different lengths: " << exc.arg.len[0] << ' ' << exc.arg.len[1];
			break;

		case Exception::MUL_ERR:
			stream << "multiplication of vectors of different lengths: " << exc.arg.len[0] << ' ' << exc.arg.len[1];
			break; 
	}

	return stream;
}

void Vector(void);

using namespace std;

int main()
{
	try
	{
		Vector();
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
void Vector()
{
      double wd[3] = {1.5,2.3,-1.7};
      double wd2[4] = {1.1,2.3,4.5,6.7};
      Vec<double>  vd1(3, wd), vd2(4, wd2);
      vd2 += vd1;
      cout << "vd1 = " << vd1 << endl;
      cout << "vd2 = " << vd2 << endl;
      double prd = vd1^vd2;
      cout << "vd1^vd2 = " << prd << endl;
      vd2 = vd1 = vd1;
      cout << "vd2 = " << vd2 << endl;
}
*/
