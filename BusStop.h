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

class Bus
{
	//загальна кількість вільних місць
	int places = 15;

public:
	Bus() {};
	int getFreePlaces();
	int getPlaces() { return places; }

};

class busStop
{
	PriorityQueue<People> qPeople;
	Queue<Bus> qBus;

	//Час необхідний автобусу для проїзду за маршрутом (60хвилин)
	const int timeWay = 60;
	const int maxWaitPeople = 10;
	int fPlaceInBus{};

	//метод очищення екрану
	void clrscr();
	//вивести чергу
	void print() const;
	//Додати людей у чергу
	void addEnqueToBus(const People& p);
	//Додати автобус
	void addBusEnque(const Bus& b);
	//Видалити автобус
	void delBusEnque(const Bus& b);

	//скільки людей різних категорій у черзі
	void printCategory();
	void printBusInfo();

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

//Додати автобус
void busStop::addBusEnque(const Bus& b)
{
	qBus.enqueue(b);
}

//Видалити автобус
void busStop::delBusEnque(const Bus& b)
{
	qBus.dequeue();
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

//друк інформації стосовно автобусів на маршрутці
void busStop::printBusInfo()
{
	gotoxy(0, 0);
	cout << "---------------------------------------------\n";
	gotoxy(0, 1);
	cout << "Кількість автобусів на маршруті: " << qBus.length() << '\n';
	cout << "Середній час очікування автобусу: " << timeWay / qBus.length() << "  хвилин\n";
	cout << "Пасажиромісткість автобусу:  " << qBus.peek().getPlaces() << " міст\n";
	cout << "Вільних місць у автобусі, що наближається  " << fPlaceInBus << '\n';
	cout << "---------------------------------------------\n";

	gotoxy(45, 0);
	cout << "------------------------\n";
	gotoxy(53, 1);
	cout << "Симулятор\n";
	gotoxy(53, 2);
	cout << "автобусної\n";
	gotoxy(54, 3);
	cout << "зупинки\n";
	gotoxy(45, 5);
	cout << "------------------------\n";
	for (int i{}; i < 6; i++)
	{
		gotoxy(45, i);
		cout << "|\n";
	}
}

//основний робочий метод
void busStop::startSimulation()
{
	Time t;
	int tWaitBus{};
	string peopleCategory[] = { "Пенсіонер","Вагітна", "Звичайна людина" };

	addBusEnque(Bus());

	while (true)
	{
		t.setupTime();
		t.showTime();
		tWaitBus = timeWay / qBus.length();
				
		//Умова залежності часу симуляції та пасажиропотоку
		if (t.getHour() >= 0 && t.getHour() <= 5)
		{
			if (t.elapsedM() % 45 == 0)
				addEnqueToBus(People((peopleCategory[random()])));
		}
		else if (t.getHour() > 5 && t.getHour() <= 10)
		{
			if (t.elapsedM() % 2 == 0)
			{
				addEnqueToBus(People((peopleCategory[random()])));
			}
		}
		else if (t.getHour() > 10 && t.getHour() <= 16)
		{
			if (t.elapsedM() % 5 == 0)
				addEnqueToBus(People((peopleCategory[random()])));
		}
		else if (t.getHour() > 16 && t.getHour() <= 20)
		{
			if (t.elapsedM() % 2 == 0)
			{
				addEnqueToBus(People((peopleCategory[random()])));
			}
		}
		else if (t.getHour() > 20 && t.getHour() <= 23)
		{
			if (t.elapsedM() % 20 == 0)
				addEnqueToBus(People((peopleCategory[random()])));
		}

		//видалення людей із черги (приїзд автобуса--люди сідають у автобус)
		if (t.elapsedM() % tWaitBus == 0)
		{
			fPlaceInBus = qBus.peek().getFreePlaces();

			for (size_t i{}; i < fPlaceInBus; i++)
				qPeople.dequeue();
					
			//system("pause");
			qBus.ring();
		}

		//Аналіз кількості очікуючіх пасажирів на остановці після повного кругу автобуса, якщо пасажирів
		//більше за maxWaitPeople то згідно умов додається певна кількість автобусі, також і навпаки 
		//є можливість і зменьшувати кількість автобусів на маршруті
		if (t.elapsedM() % timeWay == 0)
		{
			if (qPeople.length() >= maxWaitPeople)
				if (qPeople.length() >= maxWaitPeople && qPeople.length() <= maxWaitPeople * 2)
				{
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
				}
				else if (qPeople.length() > maxWaitPeople * 2 && qPeople.length() <= maxWaitPeople * 3)
				{
					addBusEnque(Bus()); 
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
				}
				else if (qPeople.length() > maxWaitPeople * 3 && qPeople.length() <= maxWaitPeople * 4)
				{
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
				}
				else
				{
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
					addBusEnque(Bus());
				}
			else if ((qPeople.length() < maxWaitPeople && qBus.length() >= 2))
				if (qBus.length() >= 3 && qBus.length() <= 5)
				{
					delBusEnque(Bus());
					delBusEnque(Bus());
				}
				else if (qBus.length() > 5 && qBus.length() <= 7)
				{
					delBusEnque(Bus());
					delBusEnque(Bus());
					delBusEnque(Bus());
				}
				else 
					delBusEnque(Bus());

		}

		printBusInfo();
		printCategory();

		//в одному циклі - 1 хв
		t.addTime(1);
		//"тривалість" циклу з реалізіцією через фу-цію сну
		Sleep(200); //200
		clrscr();
	}
}

//очисник активних полів екрану
void busStop::clrscr()
{
	//чистка активних полів автобусного інформера
	gotoxy(33, 1);
	cout << "   \n";
	gotoxy(34, 2);
	cout << "   \n";
	gotoxy(43, 4);
	cout << "   \n";

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

int Bus::getFreePlaces()
{
	return randMax(places);
}
