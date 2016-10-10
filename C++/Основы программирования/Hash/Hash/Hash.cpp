// Hash.cpp: определяет точку входа для консольного приложения.
//
/*Написать базовый вариант хэш-таблицы для работы с целыми числами 
(или строками, или другими объектами на ваш выбор). 
Реализовать хэш-таблицу как массив списков 
(размер массива 31, хэш-функция по желанию, можно взять любую самую простую). 
Граммотно определить для хэш-таблицы конструктор копирования, деструктор и оператор равенства.

*/

#include "stdafx.h"
#include <iostream>
using namespace std;

struct Node       //Структура являющаяся звеном списка
{
	int* x;     //Значение x будет передаваться в список
	Node *Next, *Prev; 
};

class myList   //Создаем тип данных Список
{	
public:
	
	Node *Head, *Tail; //Указатели на адреса начала списка и его конца
	myList() :Head(NULL), Tail(NULL) {}; 
		
	~myList() //Деструктор
	{
		if (Head != nullptr) {
			while (Head) 
			{
				Tail = Head->Next; 
				delete Head; 
				Head = Tail; 
			}
		}
	}

	void Add(int x)
	{
		Node *temp = new Node; 
		temp->Next = NULL;  

		temp->x = new int(x);

		if (Head != NULL) 
		{
			temp->Prev = Tail; 
			Tail->Next = temp; 
			Tail = temp; 
		}
		else 
		{
			temp->Prev = NULL; 
			Head = Tail = temp; 
		}
	}

	void eraseNode(int value) {	
		Node *bye = Head;
		Node *tmp = Head;
		while (tmp != Tail) {
			if (*tmp->x == value) {
				bye = tmp;
				break;
			}
			else {
				tmp = tmp->Next;
			}
		}
		if (*tmp->x == *Tail->x) {
			bye = Tail;
		}
		//Node *copyNextNode = bye->Next;
		//Node *copyPreviousNode = bye->Prev;
		if (bye->Prev != nullptr && bye->Next != nullptr) {
			bye->Prev->Next = bye->Next;
			bye->Next->Prev = bye->Prev;
		}
		else if (bye->Next != nullptr) {
			bye->Next->Prev = NULL;
			Head = bye->Next;			
		}
		else if (bye->Prev != nullptr) {
			bye->Prev->Next = NULL;
			Tail = bye->Prev;
		}
		//copyNextNode->Prev = bye->Prev;
		//copyPreviousNode->Next = bye->Next;
		bye->x=NULL;
	}

	bool search(int value) {
		
		if (Head != NULL) {
			
			if (*Head->x == value) {
				return true;
			}
			Node* tmp = new Node;
			tmp = Head;
			while (tmp->Next) {
				if (*tmp->x == value) {
					return true;
				}
				else {
					tmp = tmp->Next;
				}
			}
			if (*Tail->x == value) {
				return true;
			}
		}
		return false;
	}	

	//оператор =
	myList &operator=(const myList& Some) {
		if (Head != nullptr) {
			while (Head) 
			{
				Tail = Head->Next; 
				delete Head; 
				Head = Tail; 
			}
		}
		this->Head = this->Tail = NULL;
		if (Some.Head != nullptr) {
			Node* tmp = Some.Head;			
			while (tmp != Some.Tail) {
				this->Add(*tmp->x);
				tmp = tmp->Next;
			}
			if (Some.Tail->x != nullptr) { this->Add(*Some.Tail->x); }
		}
		return *this;
	}
};

class myHash : public myList{
	
public:
	myList* myArray[3];
	//конструктор
	myHash() {	
		for (int i = 0; i < 3; i++) {
			myArray[i] = new myList();
		};
	}

	//Хэш функция
	int HashFunction(int value) {
		int numOfCell;
		numOfCell = value % 3;
		return numOfCell;
	}

	//распихивание элементов по спискам
	void add(int value) {
		int numOfCell = HashFunction(value);
		if (search(value,numOfCell) == false){
			myArray[numOfCell]->Add(value);
		};
	}
	//поиск элементов
	bool search(int value, int numOfCell) {		
		bool result;
		result = myArray[numOfCell]->search(value);
		return result;
	}
	//удаление элементов
	void eraseNode(int value) {
		int numOfCell = HashFunction(value);
		if (search(value, numOfCell)) {
			myArray[numOfCell]->eraseNode(value);
		}
	}
	//конструктор копии
	myHash (const myHash&SomeHash) {
		for (int i = 0; i < 3; i++) {
			myArray[i] = new myList();
		};
		for (int i = 0; i < 3; i++) {			
			*myArray[i] = *SomeHash.myArray[i];
		}
	}
	
	//оператор =
	myHash &operator=(const myHash& SomeHash) {
		for (int i = 0; i < 3; i++) {
			
			*myArray[i] = *SomeHash.myArray[i];
		}
		return *this;
	}

	//деструктор
	~myHash() {
		for (int i = 0; i < 3; i++) {
			myArray[i]->~myList();
		};		
	}

};



int main()
{
	
	myHash First;
	First.add(5);
	First.add(1);
	First.add(32);
	First.add(5);
	First.add(35);
	First.add(45);
	First.eraseNode(45);

	myHash Second;
	Second = First;

	myHash Third(First);



	system("pause");
    return 0;
}

