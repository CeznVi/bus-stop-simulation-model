#pragma once

class Time
{
	int h{}, m{}, s{};
	time_t zerotime;

public:
	Time()
	{
		setT();
	}

	void setupTime();
	void setT();
	void showTime() const;
	int elapsedM();
	int getHour();
	void addTime(int hour, int min);
};

//����� ����
void Time::setupTime()
{
	//s = time(0) - zerotime;

	if (s == 60)
	{
		m += 1;
		zerotime += 60;
	};

	if (m >= 60)
	{
		h += 1;
		m = 0;
	}
	
	if (h >= 24)
	{
		h = 0;
		m = 0;
		s = 0;
	}

}

//����� ����������� �������� �������
void Time::setT()
{
	zerotime = time(0);
}

//������ ���� ������
void Time::showTime() const
{
	gotoxy(70, 0);
	cout << "------------------\n";
	gotoxy(70, 1);
	cout << "��� � ���������\n";
	gotoxy(70, 2);
	cout << "����� : ������ \n";
	gotoxy(72, 3);
	cout << h;
	gotoxy(80, 3);
	cout << m;
	gotoxy(70, 4);
	cout << "------------------\n";
}

//������ ������ ������
int Time::elapsedM()
{
	int tempM{};
	tempM = m + (h * 60);
	return tempM;
}

int Time::getHour()
{
	return h;
}

void Time::addTime(int min, int hour = 0)
{
	h += hour;
	m += min;
}
