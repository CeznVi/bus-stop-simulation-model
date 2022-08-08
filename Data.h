#pragma once

enum PRIORITY
{
	LOW, MEDIUM, HIGH, SUPERHIGH
};

template<class T>
class Data
{
public:
	T value;
	Data* next = nullptr;
	PRIORITY pri = PRIORITY::LOW;
};

