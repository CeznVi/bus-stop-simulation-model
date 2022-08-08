#pragma once
#include<iomanip>
#include "Data.h"
#include "Queue.h"

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

public:
	busStop() { }
	
	//Додати людей у чергу
	void addEnqueToBus(const People& p);
	//вивести чергу
	void print() const;
	//скільки людей різних категорій у черзі
	void printCategory();

};

//Додати людей у чергу
void busStop::addEnqueToBus(const People& p)
{
	qPeople.enqueue(p, p.getPriority());
}

PRIORITY People::getPriority() const
{
	if (category == "Вагітна")
		return PRIORITY::SUPERHIGH;
	if (category == "Пенсіонер")
		return PRIORITY::HIGH;
	if (category == "Звичайна людина")
		return PRIORITY::LOW;
}

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

	cout << "Категорії які знаходяться у черзі: \n";

	cout << "Звичайних людей = " << people << '\n';
	cout << "Пенсіонерів = " << oldmen << '\n';
	cout << "Вагітних жінок = " << pergant << '\n';

}