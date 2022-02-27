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
};

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
  if (i < 0 || i > len)
  {
    return;
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
  if (str == NULL)
  {
    return;
  }

  if (i < 0 || i > len)
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
    return;
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
    return;
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

