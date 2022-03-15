#include <iostream>
#include <cstring>

using namespace std;

class event
{
	private:
		char *name;
		int d;
		int m;
		int y;

	public:
		event(const char *name_, int d_, int m_, int y_);
		virtual ~event(void);

		virtual void print_res(void) const;
		void change_date(int d_, int m_, int y_);
		virtual void change_grade(bool grade) {}
		virtual void change_grade(int grade) {}
};

class test : public event
{
	private:
		bool grade;
	
	public:
		test(const char *name, int d_, int m_, int y_, bool grade_);
		void print_res(void) const;
		void change_grade(bool grade_);
};

class exam : public event
{
	private:
		int grade;
	
	public:
		exam(const char *name, int d_, int m_, int y_, int grade_);
		void print_res(void) const;
		void change_grade(int grade_);
};

event::event(const char *name_, int d_, int m_, int y_)
{
	name = new char[strlen(name_) + 1];
	strcpy(name, name_);
	d = d_;
	m = m_;
	y = y_;
}

event::~event(void)
{
	delete[] name;
}

void event::print_res(void) const
{
	cout << name << ' ' << d << ' ' << m << ' ' << y;
}

void event::change_date(int d_, int m_, int y_)
{
	d = d_;
	m = m_;
	y = y_;
}


test::test(const char *name_, int d_, int m_, int y_, bool grade_)
: event(name_, d_, m_, y_), grade(grade_) {}


void test::print_res(void) const
{
	event::print_res();
	cout << ' ' << (grade ? "true" : "false") << endl;
}

void test::change_grade(bool grade_)
{
	grade = grade_;
}


exam::exam(const char *name_, int d_, int m_, int y_, int grade_)
: event(name_, d_, m_, y_), grade(grade_) {}


void exam::print_res(void) const
{
	event::print_res();
	cout << " Grade " << grade << endl;
}

void exam::change_grade(int grade_)
{
	grade = grade_;
}


/*
int main()
{
        const int NUM =7;
        event *session[NUM];

        session[0]=new test("MS Office",2020,12,23,true);
        session[1]=new exam("Operation System",2021,1,15,2);
        session[2]=new test("Practicum",2020,12,25,false);
        session[3]=new exam("Differential equation",2021,1,20,3);
        session[4]=new test("Theory of probability",2020,12,29,true);
        session[5]=new exam("Philosophy",2021,1,24,5);
        session[6]=new exam("C++",2021,1,11,4);

        for (int i=0;i<NUM;i++)
                session[i]->print_res();

        session[2]->change_date(2021,2,24);
        session[2]->change_grade(true);

        session[1]->change_date(2021,2,13);
        session[1]->change_grade(3);

        cout<<endl;
        for (int i=0;i<NUM;i++)
                session[i]->print_res();

        for (int i=0;i<NUM;i++)
        delete session[i];
        return 0;
}
*/

