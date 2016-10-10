// ConsoleApplication4.cpp: ���������� ����� ����� ��� ����������� ����������. 
// 

#include "stdafx.h" 
#include <iostream> 
using namespace std;

//Binary Tree 

class TreeNode {
public:
	int value;
	TreeNode* left; //��������� �� ��������� �������� 
	TreeNode* right;

	//����������� ����������� 

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
		//�� ������ �������� 
		if (p.left) {
			left = new TreeNode(*p.left);
		}
		if (p.right) {
			right = new TreeNode(*p.right);
		}
		return *this;
	}

	//�������� ���������� �� ������������� �������� 
	TreeNode(int val) : value(val), left(0), right(0) { }

	//���������� 
	~TreeNode() {
		delete left;
		delete right;
	}


};


class Tree {
	TreeNode* root; //������ � ��������-����� 
public:
	//����������� �������� ������ ������ � ���������� ��������� �������� 

	Tree(int a) {
		root = new TreeNode(a);
	}


	//�������� �����
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

	//����������� ����������� 
	Tree(const Tree&Copied) {
		root = new TreeNode(*Copied.root);
	}

	//����� �������������� 
	TreeNode* search(int a) {
		//����� ������ 
		TreeNode* v = root;
		TreeNode* vp = root;
		while (v != 0) {
			//�������� � ������� �������: 
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


	//�������� ������� �������� � ������
	bool find(int a) {
		bool answer = false;
		if (search(a) != 0) {
			answer = true;
		};
		return answer;
	}

	//����� ���������� boolean 

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

	//���������� 
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