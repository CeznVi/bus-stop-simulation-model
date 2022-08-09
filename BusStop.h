#pragma once
#include<iomanip>
#include "Data.h"
#include "Queue.h"
#include "Time.h"

class People
{
	string category;

public:
	People() {}
	People(string d) : category(d) {}
	PRIORITY getPriority() const;
	string getCategory() const;
	friend ostream& operator<<(ostream& out, const People& p);
};



class busStop
{
	PriorityQueue<People> qPeople;
	
	//метод очищення екрану
	void clrscr();
	//вивести чергу
	void print() const;
	//Додати людей у чергу
	void addEnqueToBus(const People& p);
	//скільки людей різних категорій у черзі
	void printCategory();

public:
	busStop() { }
	//основний метод
	void startSimulation();

};

//Додати людей у чергу
void busStop::addEnqueToBus(const People& p)
{
	qPeople.enqueue(p, p.getPriority());
}
//Гетер пріорітету
PRIORITY People::getPriority() const
{
	if (category == "Вагітна")
		return PRIORITY::SUPERHIGH;
	if (category == "Пенсіонер")
		return PRIORITY::HIGH;
	if (category == "Звичайна людина")
		return PRIORITY::LOW;
}
//Друк черги
void busStop::print() const
{
	qPeople.print();
}

ostream& operator<<(ostream& out, const People& p)
{
	out << setw(10) << left << p.category;
	return out;
}

string People::getCategory() const
{
	return category;
}

//метод показання кількості людей згідно категорій
void busStop::printCategory()
{
	int oldmen{}, pergant{}, people{};
	string t;

	for (size_t i{}; i < qPeople.length(); i++)
	{
		t = qPeople.show(i).getCategory();

		if (t == "Пенсіонер")
			oldmen++;
		else if (t == "Вагітна")
			pergant++;
		else if (t == "Звичайна людина")
			people++;
		
		t.clear();
	}
	
	for (int i{}; i < 8; i++)
	{
		gotoxy(88, i);
		cout << "|\n";
	}

	gotoxy(89, 0);
	cout << "------------------------------\n";
	gotoxy(89, 1);
	cout << "Людей у черзі: " << qPeople.length() << '\n';
	gotoxy(89, 2);
	cout << "------------------------------\n";
	gotoxy(89, 3);
	cout << "Із них: \n";
	gotoxy(89, 4);
	cout << "Вагітних жінок = " << pergant << '\n';
	gotoxy(89, 5);
	cout << "Пенсіонерів = " << oldmen << '\n';
	gotoxy(89, 6);
	cout << "Звичайних людей = " << people << '\n';
	gotoxy(89, 7);
	cout << "------------------------------\n";




}

void busStop::startSimulation()
{
	Time t;

	string peopleCategory[] = { "Пенсіонер","Вагітна", "Звичайна людина" };

	while (true)
	{
		t.setupTime();
		t.showTime();
		
		//Умова залежності часу симуляції та пасажиропотоку
		if (t.getHour() >= 0 && t.getHour() <= 5)
		{
			if (t.elapsedM() % 45 == 0)
				addEnqueToBus(People((peopleCategory[random()])));
		}
		else if (t.getHour() > 5 && t.getHour() <= 10)
		{
			if (t.elapsedM() % 5 == 0)
				addEnqueToBus(People((peopleCategory[random()])));
		}
		else if (t.getHour() > 10 && t.getHour() <= 16)
		{
			if (t.elapsedM() % 10 == 0)
				addEnqueToBus(People((peopleCategory[random()])));
		}
		else if (t.getHour() > 16 && t.getHour() <= 20)
		{
			if (t.elapsedM() % 5 == 0)
				addEnqueToBus(People((peopleCategory[random()])));
		}
		else if (t.getHour() > 20 && t.getHour() <= 23)
		{
			if (t.elapsedM() % 40 == 0)
				addEnqueToBus(People((peopleCategory[random()])));
		}


		printCategory();

		//прискорення часу
		t.addTime(1);

		Sleep(100);
		clrscr();
	}
}

//очисник активних полів екрану
void busStop::clrscr()
{
	//чистка активних полів годинника
	gotoxy(72, 3);
	cout << "  \n";
	gotoxy(80, 3);
	cout << "  \n";
	//чистка активних полів пасажирів
	gotoxy(103, 1);
	cout << "    \n";
	gotoxy(106, 4);
	cout << "    \n";
	gotoxy(103, 5);
	cout << "    \n";
	gotoxy(107, 6);
	cout << "    \n";
}


