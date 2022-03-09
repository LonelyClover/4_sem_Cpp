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
