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

