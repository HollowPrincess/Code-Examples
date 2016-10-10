// ConsoleApplication4.cpp: определяет точку входа для консольного приложения. 
// 

#include "stdafx.h" 
#include <iostream> 
using namespace std;

//Binary Tree 

class TreeNode {
public:
	int value;
	TreeNode* left; //указатели на следующие элементы 
	TreeNode* right;

	//конструктор копирования 

	TreeNode(const TreeNode& a) {
		value = a.value;
		if (a.left) {
			left = new TreeNode(*a.left);
		}
		else {
			left = 0;
		}

		if (a.right) {
			right = new TreeNode(*a.right);
		}
		else {
			right = 0;
		}
	}


	TreeNode& operator=(const TreeNode& p) {
		if (left != 0) {
			delete left;
		}
		if (right != 0) {
			delete right;
		}
		value = p.value;
		//не забыть проверку 
		if (p.left) {
			left = new TreeNode(*p.left);
		}
		if (p.right) {
			right = new TreeNode(*p.right);
		}
		return *this;
	}

	//создание указателей на потенциальных потомков 
	TreeNode(int val) : value(val), left(0), right(0) { }

	//деструктор 
	~TreeNode() {
		delete left;
		delete right;
	}


};


class Tree {
	TreeNode* root; //доступ к вершинам-узлам 
public:
	//конструктор создания нового дерева и добавление корневого значения 

	Tree(int a) {
		root = new TreeNode(a);
	}


	//оператор суммы
	Tree& operator+(const Tree& something)const {
		Tree* newTree = new Tree(*this);
		newTree->addNode(*something.root);
		return (*newTree);
	}

	void addNode(TreeNode& tempNode) {
		this->add(tempNode.value);
		if (tempNode.right) {
			this->addNode(*tempNode.right);
		}

		if (tempNode.left) {
			this->addNode(*tempNode.left);
		}
	}

	//конструктор копирования 
	Tree(const Tree&Copied) {
		root = new TreeNode(*Copied.root);
	}

	//поиск местоположения 
	TreeNode* search(int a) {
		//метод класса 
		TreeNode* v = root;
		TreeNode* vp = root;
		while (v != 0) {
			//значение в текущей вершине: 
			int y = v->value;
			if (y == a) {
				vp = v;
				v = 0;
			}
			else {
				if (a<y) {
					vp = v;
					v = v->left;
				}
				else {
					vp = v;
					v = v->right;
				};
			};
		};
		return vp;
	};


	//проверка наличия элемента в дереве
	bool find(int a) {
		bool answer = false;
		if (search(a) != 0) {
			answer = true;
		};
		return answer;
	}

	//метод добавления boolean 

	bool add(int a) {
		TreeNode* searchRes = search(a);
		int val = searchRes->value;
		if (val == a) {
			return false;
		}
		else {
			TreeNode* newNode = new TreeNode(a);
			if (val < a) {
				searchRes->right = newNode;
				//newNode ->parent=searchRes; 
			}
			else {
				searchRes->left = newNode;
				//newNode ->parent=searchRes; 
			};
			return true;
		};
	}


	Tree& operator=(const Tree& p) {
		root = new TreeNode(*p.root);
		return *this;
	}

	//деструктор 
	~Tree() {
		delete root;
	}

};





int _tmain(int argc, _TCHAR* argv[])
{
	Tree Y(10);
	Y.add(52);
	Y.add(11);
	Y.add(1);
	Y.add(9);
	Y.add(7);

	bool ask = Y.find(7);
	cout << ask << endl;

	Tree Treesecond = Y;
	Tree newTree(4);
	newTree = Y;

	Tree X(5);
	X.add(6);
	X.add(9);
	X.add(1);
	X.add(8);
	X.add(9);
	Tree TreeThird = X + Y;


	system("pause");
	return 0;
}