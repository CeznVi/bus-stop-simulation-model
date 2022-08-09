#include <iostream>
#include <Windows.h>
#include <String>
#include "BusStop.h"
#include "Time.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    busStop s1;
    s1.startSimulation();
  
    return 0;
}


