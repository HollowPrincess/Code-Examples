// Monstry.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class Monstry {
	int* count;
	string* word;
public:
	Monstry() {
		this->count = new int(0);
		this->word = new string(" ");
	};

	/*ostream &operator<<(ostream&out) {
	out << this->word << endl;
	return out;
	};*/
	virtual void say() {}

	virtual ~Monstry() {
		delete (word);
		delete (count);
		cout << endl << "Деструктор Базы" << endl;
	}
};

class MonsterOne : public Monstry {
	int* count;
	string* word;
public:

	MonsterOne(string word) {
		this->word = new string(word);
		count = new int(1);
	}

	void say() {
		cout << endl;
		for (int count = 0; count < *this->count; count++) {
			cout << *this->word << " ";
		};
		cout << endl;
	}
	~MonsterOne() {
		delete (word);
		delete (count);
		cout << endl << "Деструктор 1" << endl;

	}

};


class MonsterTwo : public Monstry {
	int* count;
	string* word;
public:

	MonsterTwo(string word) {
		this->word = new string(word);
		count = new int(2);
	}

	void say() {
		cout << endl;
		for (int count = 0; count < *this->count; count++) {
			cout << *this->word << " ";
		};
		cout << endl;
	}
	~MonsterTwo() {
		delete (word);
		delete (count);
		cout << endl << "Деструктор 2" << endl;

	}
};

class MonsterTree : public Monstry {
	int* count;
	string* word;
public:

	MonsterTree(string word) {
		this->word = new string(word);
		count = new int(3);
	}

	void say() {
		cout << endl;
		for (int count = 0; count < *this->count; count++) {
			cout << *this->word << " ";
		};
		cout << endl;
	}
	~MonsterTree() {
		delete (word);
		delete (count);
		cout << endl << "Деструктор 3" << endl;
	}

};



int main()
{
	setlocale(LC_ALL, "Russian");

	Monstry* Mimi = new MonsterOne("Mimimi");

	Monstry* MonstryArray[3];
	MonstryArray[0] = new MonsterOne("Around");
	MonstryArray[1] = new MonsterTwo("World");
	MonstryArray[2] = new MonsterTree("La-La");

	for (int count = 0; count < 3; count++) {
		MonstryArray[count]->say();
	};
	delete Mimi;
	//memset(MonstryArray, 0, sizeof(MonstryArray));
	for (int i = 0; i < 3; i++) {
		delete MonstryArray[i];
	};
	system("pause");
	return 0;
}


