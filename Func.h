#pragma once
#include<iostream>
#include<Windows.h>

using namespace std;

enum ConsoleColor
{
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};

void SetColor(int text, int background);

void gotoxy(int x, int y);

int random();

template<class T>
void addElemArray(T*& arr, int& size, T elem)
{
	T* temp = new T[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = arr[i];
	}
	temp[size] = elem;
	size++;
	delete[]arr;
	arr = temp;
}

template<class T>
void printArray(T* arr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

template<class T1, class T2, class T3>
auto Sum(T1 a, T2 b, T3 c)-> decltype(a + b)
{
	return a + b + c;
}

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));

}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Рандомайзер від 0 до 2 із встановленою вірогідністю випадіння
//заданих чисел
int random()
{
	int temp{};
	temp = rand() % 100 + 1;

	if (temp <= 5)
		return 1;
	else if (temp > 5 && temp <= 25)
		return 0;
	else
		return 2;
}