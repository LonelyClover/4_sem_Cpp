#include <iostream>
#include <cstring>

class mstring
{
  private:
    char *buf;
    int len;

  public:
    mstring(void);
    mstring(const mstring& str);
    mstring(const char *str);
    ~mstring(void);

    int length(void) const;
    bool isempty(void) const;
    void add(char c);
    void add(const char *str);
    void insert(char c, int i);
    void insert(const char *str, int i);
    void del(int i);
    void del(int i, int j);
    int search(const char *str) const;
    void replace(const char *sub_str, const char *new_str);
    void print(void) const;

		const mstring operator+(const mstring& srt) const;
		const mstring operator+(const char* srt) const;
		const mstring operator*(int n) const;
		const mstring& operator=(const mstring& str);
		bool operator>(const mstring& str) const;
		bool operator<(const mstring& str) const;
		bool operator>=(const mstring& str) const;
		bool operator<=(const mstring& str) const;
		bool operator==(const mstring& str) const;
		char& operator[](int i) const;
	
		friend const mstring operator+(const char *str, const mstring& mstr);
		friend const mstring operator*(int n, const mstring& str);	
		friend std::ostream& operator<<(std::ostream& stream, const mstring& str);
		friend std::istream& operator>>(std::istream& stream, mstring& str);
};

class Exception
{
	private:
		char *method;
		int argc;
		int *argv;

	public:
		Exception(const char *str, int a);
		Exception(const char *str, int a, int b);
		Exception(const Exception& exc);
		~Exception(void);

		const Exception& operator=(const Exception& exc);

		friend std::ostream& operator<<(std::ostream& stream, const Exception& exc);
};

void error(void);

mstring::mstring(void)
{
  len = 1;
  buf = new char[len];
  buf[0] = '\0';
  return;
}

mstring::mstring(const mstring& str)
{
  len = str.len;
  buf = new char[len];
  memcpy(buf, str.buf, len);
  return;
}

mstring::mstring(const char *str)
{
  if (str == NULL)
  {
    len = 1;
    buf = new char[len];
    buf[0] = '\0';
    return;
  }

  len = strlen(str) + 1;
  buf = new char[len];
  memcpy(buf, str, len);
  return;
}

mstring::~mstring(void)
{
  delete[] buf;
  return;
}

int mstring::length(void) const
{
  return len - 1;
}

bool mstring::isempty(void) const
{
  return len == 1;
}

void mstring::add(char c)
{
  int new_len = len + 1;
  char *new_buf = new char[new_len];
  
  memcpy(new_buf, buf, len);
  new_buf[new_len - 2] = c;
  new_buf[new_len - 1] = '\0';
  
  delete[] buf;
  buf = new_buf;
  len = new_len;
}

void mstring::add(const char *str)
{
  if (str == NULL)
  {
    return;
  }

  int new_len = len + strlen(str);
  char *new_buf = new char[new_len];
  
  memcpy(new_buf, buf, len);
  memcpy(new_buf + len - 1, str, strlen(str) + 1);
  
  delete[] buf;
  buf = new_buf;
  len = new_len;
}

void mstring::insert(char c, int i)
{
  if (i < 0 || i > len || (len == 1 && i == 1))
  {
    throw Exception("insert", i);
  }

  int new_len = len + 1;
  char *new_buf = new char[new_len];
  
  memcpy(new_buf, buf, i);
  new_buf[i] = c;
  memcpy(new_buf + i + 1, buf + i, len - i);

  delete[] buf;
  buf = new_buf;
  len = new_len;
}

void mstring::insert(const char *str, int i)
{
  if (i < 0 || i > len)
  {
    throw Exception("insert", i);
  }

  if (str == NULL)
  {
    return;
  }

  int new_len = len + strlen(str);
  char *new_buf = new char[new_len];
  
  memcpy(new_buf, buf, i);
  memcpy(new_buf + i, str, strlen(str));
  memcpy(new_buf + i + strlen(str), buf + i, len - i);

  delete[] buf;
  buf = new_buf;
  len = new_len;
}

void mstring::del(int i)
{
  if (i < 0 || i >= len - 1)
  {
    throw Exception("del", i);
  }

  int new_len = len - 1;
  char *new_buf = new char[new_len];
  
  memcpy(new_buf, buf, i);
  memcpy(new_buf + i, buf + i + 1, len - i - 1);

  delete[] buf;
  buf = new_buf;
  len = new_len;
}

void mstring::del(int i, int j)
{
  if (i < 0 || i > j || j >= len - 1)
  {
    throw Exception("del", i, j);
  }
  
  int new_len = len - (j - i + 1);
  char *new_buf = new char[new_len];

  memcpy(new_buf, buf, i);
  memcpy(new_buf + i, buf + j + 1, len - j - 1);

  delete[] buf;
  buf = new_buf;
  len = new_len;
}

int mstring::search(const char *str) const
{
  if (str == NULL)
  {
    return -1;
  }

  char *ptr = strstr(buf, str);

  if (ptr == NULL)
  {
    return -1;
  }

  return ptr - buf;
}

void mstring::replace(const char *sub_str, const char *new_str)
{
  int i = this -> search(sub_str);

  if (i == -1)
  {
    return;
  }

  this -> del(i, i + strlen(sub_str) - 1);
  this -> insert(new_str, i);
  return;
}

void mstring::print(void) const
{
  std::cout << buf << std::endl;
}

const mstring mstring::operator+(const mstring& str) const
{
	mstring temp = mstring(*this);
	
	temp.add(str.buf);
	
	return temp;
}

const mstring mstring::operator+(const char *str) const
{
	mstring temp = mstring(*this);
	
	temp.add(str);
	
	return temp;
}

const mstring mstring::operator*(int n) const
{
	if (n < 0)
	{
		throw Exception("operator*", n);
	}

	if (n == 0)
	{
		return mstring();
	}

	mstring temp = mstring(*this);
	
	for (int i = 0; i < n - 1; i++)
	{
		temp.add(buf);
	}
	
	return temp;
}

const mstring& mstring::operator=(const mstring& str)
{
	if (&str == this)
	{
		return *this;
	}
	
	len = str.len;

	delete[] buf;
	buf = new char[len];

	memcpy(buf, str.buf, len);
	
	return *this;
}

bool mstring::operator>(const mstring& str) const
{
	return strcmp(buf, str.buf) > 0;
}

bool mstring::operator<(const mstring& str) const
{
	return strcmp(buf, str.buf) < 0;
}

bool mstring::operator>=(const mstring& str) const
{
	return strcmp(buf, str.buf) >= 0;
}

bool mstring::operator<=(const mstring& str) const
{
	return strcmp(buf, str.buf) <= 0;
}

bool mstring::operator==(const mstring& str) const
{
	return strcmp(buf, str.buf) == 0;
}

char& mstring::operator[](int i) const
{
	if (i < 0 || i >= len - 1)
	{
		throw Exception("operator[]", i);
	}

	return buf[i];
}

const mstring operator+(const char *str, const mstring& mstr)
{
	mstring temp = mstring(str);
	
	return temp + mstr;
}

const mstring operator*(int n, const mstring& str)
{
	if (n < 0)
	{
		throw Exception("operator*", n);
	}

	if (n == 0)
	{
		return mstring();
	}

	mstring temp = mstring(str);
	
	for (int i = 0; i < n - 1; i++)
	{
		temp.add(str.buf);
	}
	
	return temp;
}

std::ostream& operator<<(std::ostream& stream, const mstring& str)
{
	stream << str.buf;
	return stream;
}

std::istream& operator>>(std::istream& stream, mstring& str)
{
	str = mstring();
	
	char c;

	while (!stream.eof())
	{
		stream.get(c);

		if (c == '\n')
		{
			break;
		}

		str.add(c);
	}

	return stream;
}

Exception::Exception(const char *str, int a)
{
	method = new char[strlen(str) + 1];
	strcpy(method, str);

	argc = 1;
	argv = new int[argc];
	argv[0] = a;
	
	return;
}

Exception::Exception(const char *str, int a, int b)
{
	method = new char[strlen(str) + 1];
	strcpy(method, str);

	argc = 2;
	argv = new int[argc];
	argv[0] = a;
	argv[1] = b;
	
	return;
}

Exception::Exception(const Exception& exc)
{
	method = new char[strlen(exc.method) + 1];
	strcpy(method, exc.method);

	argc = exc.argc;
	argv = new int[argc];
	memcpy(argv, exc.argv, argc * sizeof(int));

	return;
}

const Exception& Exception::operator=(const Exception& exc)
{
	if (&exc == this)
	{
		return *this;
	}

	delete[] method;
	delete[] argv;

	method = new char[strlen(exc.method) + 1];
	strcpy(method, exc.method);

	argc = exc.argc;
	argv = new int[argc];
	memcpy(argv, exc.argv, argc * sizeof(int));

	return *this;
}


Exception::~Exception(void)
{
	delete[] method;
	delete[] argv;
	return;
}

std::ostream& operator<<(std::ostream& stream, const Exception& exc)
{
	stream << "Exception: problem in " << exc.method << " incorrect parameter:";
	for (int i = 0; i < exc.argc; i++)
	{
		stream << exc.argv[i];
		if (i != exc.argc - 1)
		{
			stream << ' ';
		}
	}
	return stream;
}

using namespace std;

int main()
{
	try
	{
		error();
	}
	catch(Exception exc)
	{
		cerr << exc << endl;
		return 1;
	}
	return 0;
	
}
