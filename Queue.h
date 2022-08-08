#pragma once
#include<initializer_list>
#include<cassert>
#include"Data.h"
#include"Func.h"

using namespace std;

template<class T>
class Queue
{
	Data<T>* first = nullptr;
	Data<T>* last = nullptr;
	size_t   size = 0;

public:
	Queue() {}
	Queue(initializer_list<T> list);
	~Queue();
	Queue(const Queue& q);
	Queue& operator=(const Queue& q);
	void enqueue(const T& value);
	void dequeue();
	T peek();
	size_t length() const;
	bool isEmpty() const;
	void clear();
	void print() const;
	void print(int x, int y);

	void ring();

};

template<class T>
Queue<T>::Queue(initializer_list<T> list)
{
	for (auto i = list.begin(); i < list.end(); i++)
	{
		enqueue(*i);
	}

	/*for (T l : list)
	{
		enqueue(l);
	}*/
}

template<class T>
inline Queue<T>::~Queue()
{
	this->clear();
}

template<class T>
Queue<T>::Queue(const Queue& q)
{
	Data<T>* temp = q.first;
	while (temp)
	{
		this->enqueue(temp->value);
		temp = temp->next;
	}
}

template<class T>
void Queue<T>::enqueue(const T& value)
{
	if (size == 0)
	{
		first = new Data<T>;
		first->value = value;
		last = first;
	}
	else
	{
		last->next = new Data<T>;
		last->next->value = value;
		last = last->next;
	}
	size++;
}

template<class T>
void Queue<T>::dequeue()
{
	if (size > 0)
	{
		Data<T>* temp = first;
		first = first->next;
		delete temp;
		size--;
		last = (size == 0) ? nullptr : last;
	}
}

template<class T>
T Queue<T>::peek()
{
	assert(size > 0);
	return first->value;
}

template<class T>
size_t Queue<T>::length() const
{
	return size;
}

template<class T>
bool Queue<T>::isEmpty() const
{
	return size == 0;
}

template<class T>
void Queue<T>::clear()
{
	/*while (size)
		dequeue();*/

	Data<T>* temp = first;
	while (temp)
	{
		first = first->next;
		delete temp;
		temp = first;
	}
	last = nullptr;
	size = 0;
}

template<class T>
void Queue<T>::print() const
{
	Data<T>* temp = first;
	while (temp)
	{
		cout << temp->value << endl;
		temp = temp->next;
	}
	cout << endl;
}

template<class T>
void Queue<T>::print(int x, int y)
{
	Data<T>* temp = first;
	for (size_t i = 0; i < size; i++)
	{
		if (i <= 10)
		{
			gotoxy(x, y++);
			cout << temp->value << endl;
		}
		else
		{
			if (i < size - 10)
			{
				if (i == size - 10)
				{
					gotoxy(x, y++);
					cout << "======^^^=====" << endl;
				}
				else
				{
					gotoxy(x, y++);
					cout << temp->value << endl;
				}
			}
		}

		temp = temp->next;
	}
	cout << endl;
}

template<class T>
void Queue<T>::ring()
{
	/*this->enqueue(first->value);
	this->dequeue();*/

	if (size > 1)
	{
		Data<T>* temp = first;
		first = first->next;
		last->next = temp;
		last = temp;
		last->next = nullptr;
	}
}



/////////////////  PRIORITY QUEUE //////////////

template<class T>
class PriorityQueue
{
	Data<T>* first = nullptr;
	Data<T>* last = nullptr;
	size_t   size = 0;

public:
	PriorityQueue() {}
	PriorityQueue(initializer_list<T> list);
	~PriorityQueue();
	PriorityQueue(const PriorityQueue& q);
	PriorityQueue& operator=(const PriorityQueue& q);
	void enqueue(const T& value, PRIORITY pri = PRIORITY::LOW);
	void dequeue();
	T peek();
	T show(size_t pos) const;
	size_t length() const;
	bool isEmpty() const;
	void clear();
	void print() const;

};

template<class T>
void PriorityQueue<T>::enqueue(const T& value, PRIORITY pri)
{
	Data<T>* temp = new Data<T>;
	temp->value = value;
	temp->pri = pri;

	if (size == 0)
	{
		first = last = temp;
		size++;
		return;
	}

	if (pri <= last->pri)
	{
		last->next = temp;
		last = temp;
	}
	else if (pri > first->pri)
	{
		temp->next = first;
		first = temp;
	}
	else
	{
		Data<T>* pos = first;
		while (pri <= pos->next->pri)
		{
			pos = pos->next;
		}
		temp->next = pos->next;
		pos->next = temp;
	}
	size++;
}


template<class T>
PriorityQueue<T>::PriorityQueue(initializer_list<T> list)
{
	for (auto i = list.begin(); i < list.end(); i++)
	{
		enqueue(*i);
	}

	/*for (T l : list)
	{
		enqueue(l);
	}*/
}

template<class T>
inline PriorityQueue<T>::~PriorityQueue()
{
	this->clear();
}

template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& q)
{
	Data<T>* temp = q.first;
	while (temp)
	{
		this->enqueue(temp->value);
		temp = temp->next;
	}
}


template<class T>
void PriorityQueue<T>::dequeue()
{
	if (size > 0)
	{
		Data<T>* temp = first;
		first = first->next;
		delete temp;
		size--;
		last = (size == 0) ? nullptr : last;
	}
}

template<class T>
T PriorityQueue<T>::peek()
{
	assert(size > 0);
	return first->value;
}

template<class T>
size_t PriorityQueue<T>::length() const
{
	return size;
}

template<class T>
bool PriorityQueue<T>::isEmpty() const
{
	return size == 0;
}

template<class T>
void PriorityQueue<T>::clear()
{
	/*while (size)
		dequeue();*/

	Data<T>* temp = first;
	while (temp)
	{
		first = first->next;
		delete temp;
		temp = first;
	}
	last = nullptr;
	size = 0;
}

template<class T>
void PriorityQueue<T>::print() const
{
	Data<T>* temp = first;
	while (temp)
	{
		cout << temp->value << endl;
		temp = temp->next;
	}
	cout << endl;
}

template<class T>
T PriorityQueue<T>::show(size_t pos) const
{
	assert(pos < size);
	size_t count{};

	Data<T>* temp = first;

	for(size_t i{}; i < pos; i++)
		temp = temp->next;
	
	
	return temp->value;
}