#include <iostream>
#include <cstring>

namespace Constant
{
	const int PLAYER_AMOUNT = 11;
	const int TEAM_AMOUNT = 2;
	const char *TEAM_LABELS[TEAM_AMOUNT] = {"Zenit", "CSKA"};
}

class Player
{
	public:
		enum Team
		{
			ZENIT = 0,
			CSKA,
		};

	private:
		int number;
		Team team;
		int in_team_id;

		static Player *team_list[Constant::TEAM_AMOUNT][Constant::PLAYER_AMOUNT];
		static int team_count[Constant::TEAM_AMOUNT];

	public:
		Player(const char *team_, int number_);
		~Player(void);
		void Print(void) const;
		
		static void Print_teams(void);
};

class Exception
{
	protected:
		char *message;
		char *name;

	public:
		Exception(const char *message_, const char *name_);
		~Exception(void);

		friend std::ostream& operator<<(std::ostream& stream, const Exception& exc);
};

class NumberException : public Exception
{
	private:
		int number;

	public:
		NumberException(const char *message_, const char *name_, int number_) : Exception(message_, name_), number(number_) {}
		
		friend std::ostream& operator<<(std::ostream& stream, const NumberException& exc);
};

Player *Player::team_list[Constant::TEAM_AMOUNT][Constant::PLAYER_AMOUNT] = {};
int Player::team_count[Constant::TEAM_AMOUNT] = {};

Player::Player(const char *team_, int number_)
{
	if (strcmp(team_, "Zenit") == 0)
	{
		team = ZENIT;
	}
	else if (strcmp(team_, "CSKA") == 0)
	{
		team = CSKA;
	}
	else
	{
		throw Exception("Wrong name", team_);
	}

	if (team_count[team] == Constant::PLAYER_AMOUNT)
	{
		throw Exception("Too many players", Constant::TEAM_LABELS[team]);
	}

	number = number_;

	if (number < 1)
	{
		throw NumberException("Wrong number", Constant::TEAM_LABELS[team], number);
	}

	in_team_id = 0;

	for (int i = 0; i < Constant::PLAYER_AMOUNT; i++)
	{
		if (team_list[team][i] == 0)
		{
			in_team_id = i;
			break;
		}
		else if (number == team_list[team][i]->number)
		{
			throw NumberException("Double number", Constant::TEAM_LABELS[team], number);
		}
	}
	
	team_list[team][in_team_id] = this;
	team_count[team] += 1;
}

Player::~Player(void)
{
	for (int i = in_team_id; i < Constant::PLAYER_AMOUNT - 1; i++)
	{
		team_list[team][i] = team_list[team][i + 1];
	}
	team_list[team][Constant::PLAYER_AMOUNT - 1] = 0;

	team_count[team] -= 1;
}

void Player::Print(void) const
{
	std::cout << Constant::TEAM_LABELS[team] << ' ' << number << std::endl;
}

void Player::Print_teams(void)
{
	for (int t = 0; t < Constant::TEAM_AMOUNT; t++)
	{
		if (team_count[t] == 0)
		{
			return;
		}

		std::cout << Constant::TEAM_LABELS[t] << ':';
		
		for (int i = 0; i < team_count[t]; i++)
		{
			std::cout << ' ' << team_list[t][i]->number;
		}

		std::cout << std::endl;
	}
}

Exception::Exception(const char *message_, const char *name_)
{
	message = new char[strlen(message_) + 1];
	strcpy(message, message_);

	name = new char[strlen(name_) + 1];
	strcpy(name, name_);
}

Exception::~Exception(void)
{
	delete[] message;
	delete[] name;
}

std::ostream& operator<<(std::ostream& stream, const Exception& exc)
{
	stream << "Exception: " << exc.message << " in team " << exc.name;

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const NumberException& exc)
{
	stream << "Exception: " << exc.message << " in team " << exc.name << " Error number: " << exc.number;

	return stream;
}

void test_players();

int main()
{
	try
	{
		test_players();
	}
	catch(NumberException& exc)
	{
		std::cerr << exc << std::endl;
	}
	catch(Exception& exc)
	{
		std::cerr << exc << std::endl;
	}
	return 0;
}
/*
void test_players()
{
        Player pl1("Zenit", 0);
        Player pl2("Zenit", 11);
        Player pl3("Zenit", 3);
        Player pl4("Zenit", 4);
        Player pl5("Zenit", 5);
        Player pl6("Zenit", 6);
        Player pl7("Zenit", 7);
        Player pl8("Zenit", 8);
        Player pl9("Zenit", 9);
        Player plA("Zenit", 1);
        Player plB("Zenit", 2);

        Player pl0("Zenit", 112);
        pl1.Print();
        Player::Print_teams();
}
*/
