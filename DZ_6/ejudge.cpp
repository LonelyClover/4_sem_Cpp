#include <iostream>
#include <cstring>

template<typename T>
class Set
{
	private:
		T *buf;
		int len;

	public:
		Set(void);
		Set(T *arg, int arg_len);
		Set(const Set<T>& arg);
		~Set(void);

		void add(T arg);
		void add(T *arg, int arg_len);
		void del(T arg);
		bool in(T arg) const;
		void print(void) const;

		Set<T>& operator=(const Set<T>& op);
		Set<T> operator*(const Set<T>& op) const; 
		Set<T> operator+(const Set<T>& op) const; 
};

template<typename T>
Set<T>::Set(void)
{
	buf = 0;
	len = 0;
}

template<typename T>
Set<T>::Set(T *arg, int arg_len)
{
	buf = 0;
	len = 0;

	for (int i = 0; i < arg_len; i++)
	{
		add(arg[i]);
	}
}

template<typename T>
Set<T>::Set(const Set<T>& arg)
{
	len = arg.len;

	buf = new T[len];
	memcpy(buf, arg.buf, len * sizeof(T));
}

template<typename T>
Set<T>::~Set(void)
{
	delete[] buf;
}

template<typename T>
void Set<T>::add(T arg)
{
	if (buf == 0)
	{
		buf = new T[1];
		*buf = arg;
		len = 1;
		return;
	}

	int idx = len;
	for (int i = 0; i < len; i++)
	{
		if (arg == buf[i])
		{
			return;
		}
		if (arg < buf[i])
		{
			idx = i;
			break;
		}
	}

	T *new_buf = new T[len + 1];
	memcpy(new_buf, buf, idx * sizeof(T));
	new_buf[idx] = arg;
	memcpy(new_buf + idx + 1, buf + idx, (len - idx) * sizeof(T));

	delete[] buf;
	buf = new_buf;
	len += 1;
}

template<typename T>
void Set<T>::add(T *arg, int arg_len)
{
	for (int i = 0; i < arg_len; i++)
	{
		add(arg[i]);
	}
}

template<typename T>
void Set<T>::del(T arg)
{
	if (buf == 0)
	{
		return;
	}

	for (int i = 0; i < len; i++)
	{
		if (arg == buf[i])
		{
			T *new_buf = new T[len - 1];
			memcpy(new_buf, buf, i * sizeof(T));
			memcpy(new_buf + i, buf + i + 1, (len - i - 1) * sizeof(T));

			delete[] buf;
			buf = new_buf;
			len -= 1;
		}
		if (arg < buf[i])
		{
			return;
		}
	}
}

template<typename T>
bool Set<T>::in(T arg) const
{
	for (int i = 0; i < len; i++)
	{
		if (arg == buf[i])
		{
			return true;
		}

		if (arg < buf[i])
		{
			break;
		}
	}

	return false;
}			

template<typename T>
void Set<T>::print(void) const
{
	for (int i = 0; i < len; i++)
	{
		std::cout << buf[i];
		
		if (i != len - 1)
		{
			std::cout << ' ';
		}
	}

	std::cout << std::endl;
}

template<typename T>
Set<T>& Set<T>::operator=(const Set<T>& op)
{
	if (&op == this)
	{
		return *this;
	}

	delete[] buf;

	len = op.len;

	buf = new T[len];
	memcpy(buf, op.buf, len * sizeof(T));

	return *this;
}

template<typename T>
Set<T> Set<T>::operator*(const Set<T>& op) const
{
	Set<T> res;

	for (int i = 0; i < len; i++)
	{
		if (op.in(buf[i]))
		{
			res.add(buf[i]);
		}
	}

	return res;
}

template<typename T>
Set<T> Set<T>::operator+(const Set<T>& op) const
{
	Set<T> res = op;
	res.add(buf, len);
	return res;
}

/*
using namespace std;
int main()
{
				int a[] = { 1,2,3,4,5 };
        int b[] = { 3,2,6};
        Set <int> seti1(a,5),seti2,seti3,seti4;
        seti2.add(b, 3);
        seti1.print();
        seti2.print();
        seti3 = seti1*seti2;
        cout << "Intersect: ";
        seti3.print();
        seti4 = seti1 + seti2;
        cout << "Union: ";
        seti4.print();
        seti3.add(7);
        seti4.del(3);
        seti3.print();
        seti4.print();
        return 0;
}
*/
