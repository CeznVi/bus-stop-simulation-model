#include <iostream>
#include <Windows.h>
#include <String>

#include "BusStop.h"
using namespace std;





int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    string peopleCategory[] = { "Пенсіонер","Вагітна", "Звичайна людина" };

    busStop s1;

    int count{};
    while (count < 10)
    {
        s1.addEnqueToBus(People((peopleCategory[random()])));
        count++;
    }
  
    s1.print();
    s1.printCategory();
    

    return 0;
}


