#include <iostream>
#include <cstring>

class Flower
{
	private:
		enum Color 
		{
			PINK = 0,
			WHITE
		} color;
		int n;
		
		static int count[2];
	
	public:
		Flower(const char *color_ = "", int n_ = 10);
		~Flower(void);
		static void Print_flowers(void);
};

int Flower::count[2] = {0, 0};

Flower::Flower(const char *color_, int n_)
{
	n = n_;
	
	if (strcmp(color_, "white") == 0)
	{
		color = WHITE;
	}
	else if (strcmp(color_, "pink") == 0)
	{
		color = PINK;
	}
	else if (count[WHITE] == count[PINK])
	{
		color = static_cast<Flower::Color>(n % 2);
	}
	else
	{
		color = count[WHITE] < count[PINK] ? WHITE : PINK;
	}

	count[color] += 1;
}

Flower::~Flower(void)
{
	count[color] -= 1;
}

void Flower::Print_flowers(void)
{
	std::cout << "White: " << count[WHITE] << " Pink: " << count[PINK] << std::endl;
}

/*
using namespace std;
int main()
{
       Flower fl1("white", 3);
       Flower fl2("pink", 5);
       Flower fl3("white", 7);
       Flower::Print_flowers();
       Flower fl4("green");
       Flower::Print_flowers();
       Flower fl5("blue", 17);
       Flower::Print_flowers();
       Flower fl6;
       Flower::Print_flowers();
       Flower fl7;
       Flower::Print_flowers();
       return 0;
}
*/
