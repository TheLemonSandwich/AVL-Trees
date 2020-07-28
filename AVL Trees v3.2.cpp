#include <iostream>
#include <string>

using namespace std;

struct AvlNode
{
	int reg;
	float gpa;
	string name, faculty;
	AvlNode* right;
	AvlNode* left;
	int height;

	AvlNode(int val, string name, string fac, float gpa)
	{
		reg = val;
		faculty = fac;
		this->gpa = gpa;
		this->name = name;
		right = left = NULL;
		height = 0;
	}
};

typedef AvlNode* Position;
typedef AvlNode* Avltree;

class AvlTree
{
private:
	AvlNode* root;
	void insertNode(int, string, string, float, Avltree&);
	int Height(Position);
	int max(int, int);
	void LLcase(Avltree&);
	void LRcase(Avltree&);
	void RRcase(Avltree&);
	void RLcase(Avltree&);
	void AscendingOrder(Position);
	void DescendingOrder(Position);
	void makeDeletion(Avltree&);
	void delNode(int, Avltree&);
	Position Find(AvlNode*, int) const;

public:
	AvlTree();
	void insert(int, string, string, float);
	void FindStudent(int);
	void displayInorder();
	void displayDescendingOrder();
	void deleteNode(int);
};

AvlTree::AvlTree()
{
	root = NULL;
}



//											CHECKING HEIGHT

int AvlTree::Height(Position temp)
{
	if (temp == NULL)
		return -1;
	else
		return temp->height;
}

//												MAX VALUE
int AvlTree::max(int a, int b)
{
	return a > b ? a : b;
}

//											INSERT FUNCTION

void AvlTree::insert(int val, string name, string faculty, float gpa)
{
	insertNode(val, name, faculty, gpa, root);
}

void AvlTree::insertNode(int val, string name, string faculty, float gpa, Avltree& ptr)
{
	if (ptr == NULL)
	{
		ptr = new AvlNode(val, name, faculty, gpa);
	}
	else
		if (val > ptr->reg)	//	PROCEED IN THE RIGHT SUB-TREE
		{
			insertNode(val, name, faculty, gpa, ptr->right);
			if (Height(ptr->right) - Height(ptr->left) == 2)	//	CHECKING BALANCE
			{
				if (val > ptr->right->reg)
					RRcase(ptr);
				else
					if (val < ptr->right->reg)
						RLcase(ptr);
			}
		}
		else
			if (val < ptr->reg)	// PROCEED IN THE LEFT SUB-TREE
			{
				insertNode(val, name, faculty, gpa, ptr->left);
				if (Height(ptr->left) - Height(ptr->right) == 2)	// CHECKING BALANCE
				{
					if (val < ptr->left->reg)
						LLcase(ptr);
					else
						if (val > ptr->left->reg)
							LRcase(ptr);
				}
			}

	ptr->height = max(Height(ptr->right), Height(ptr->left)) + 1;	// UPDATING HEIGHT
}

//											AVL TREE CASES

void AvlTree::LLcase(Avltree& k3)
{
	Position k2;

	k2 = k3->left;
	k3->left = k2->right;
	k2->right = k3;
	k3->height = max(Height(k3->left), Height(k3->right)) + 1;
	k2->height = max(Height(k2->right), k3->height) + 1;
	k3 = k2;
}

void AvlTree::RRcase(Avltree& k1)
{
	Position k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(Height(k1->right), Height(k1->left)) + 1;
	k2->height = max(Height(k2->right), k1->height) + 1;
	k1 = k2;
}

void AvlTree::LRcase(Avltree& k3)
{
	RRcase(k3->left);
	LLcase(k3);
}

void AvlTree::RLcase(Avltree& k1)
{
	LLcase(k1->right);
	RRcase(k1);
}

//											DISPLAYING ORDERS

void AvlTree::displayInorder()
{
	AscendingOrder(root);
}

void AvlTree::displayDescendingOrder()
{
	DescendingOrder(root);
}

//											DESCENDING ORDER

void AvlTree::DescendingOrder(Position ptr)
{
	if (ptr != NULL)
	{
		DescendingOrder(ptr->right);
		cout << ptr->name << " " << ptr->reg << endl;
		DescendingOrder(ptr->left);
	}
}

//											ASCENDING ORDER

void AvlTree::AscendingOrder(Position ptr)
{
	if (ptr != NULL)
	{
		AscendingOrder(ptr->left);
		cout << ptr->name << " " << ptr->reg << endl;
		AscendingOrder(ptr->right);
	}
}

void AvlTree::deleteNode(int val)
{
	delNode(val, root);
}

//											FINDING THE NODE BEFORE DELETION

void AvlTree::delNode(int val, Avltree& ptr)
{
	if (ptr == NULL)
	{
		cout << "Student Not Found\n";
		return;
	}
	else
		if (val < ptr->reg)
		{
			delNode(val, ptr->left);
			if (Height(ptr->right) - Height(ptr->left) == 2)
			{
				if (Height(ptr->right->left) > Height(ptr->right->right))
					RLcase(ptr);
				else
					RRcase(ptr);
			}
		}
		else
			if (val > ptr->reg)
			{
				delNode(val, ptr->right);
				if (Height(ptr->left) - Height(ptr->right) == 2)
				{
					if (Height(ptr->left->right) > Height(ptr->left->left))
						LRcase(ptr);
					else
						LLcase(ptr);
				}
			}
			else
				if (val == ptr->reg)
					makeDeletion(ptr);
}

void AvlTree::FindStudent(int reg)
{
	Position temp = Find(root, reg);
	cout << "Name: " << temp->name << endl;
	cout << "Reg: " << temp->reg << endl;
}

//											FINDING STUDENT

Position AvlTree::Find(AvlNode* k1, int id) const
{
	if (k1 == NULL)
		cout << "Student doesn't Exist\n";
	else if (id == k1->reg)
		return k1;
	else if (id < k1->reg)
	{
		Find(k1->left, id);
	}
	else if (id > k1->reg)
	{
		Find(k1->right, id);
	}
}

//											DELETION OF THE NODE

void AvlTree::makeDeletion(Avltree& ptr)
{
	Position tempPtr;

	if (ptr->right == NULL)
	{
		tempPtr = ptr;
		ptr = ptr->left;
		delete tempPtr;
	}
	else
		if (ptr->left == NULL)
		{
			tempPtr = ptr;
			ptr = ptr->right;
			delete tempPtr;
		}
		else
		{
			tempPtr = ptr->right;
			while (tempPtr->left != NULL)
				tempPtr = tempPtr->left;
			tempPtr->left = ptr->left;
			tempPtr = ptr;
			ptr = ptr->right;
			delete tempPtr;
		}
}


int main()
{
	AvlTree avlTree;
	char option;
	int reg;
	string name, faculty;
	float gpa;

	do
	{
		cout << "1.Insert a student\n"
			<< "2. Delete a student\n"
			<< "3. Show all students.\n"
			<< "4. Find a student\n\n"
			<< "Choose:";
		cin >> option;
		switch (option)
		{
		case '1':
			cin.ignore();
			cout << "Enter Name: ";
			getline(cin, name);
			cout << "Faculty: ";
			getline(cin, faculty);
			cout << "Registration Number: ";
			cin >> reg;
			cout << "GPA: ";
			cin >> gpa;
			avlTree.insert(reg, name, faculty, gpa);
			break;
		case '2':
			cout << "Enter reg To Delete: ";
			cin >> reg;
			avlTree.deleteNode(reg);
			break;
		case '3':
			cout << "Ascending Order:-\n";
			avlTree.displayInorder();
			cout << "\nDescending Order\n";
			avlTree.displayDescendingOrder();
			break;
		case '4':
			cout << "Registration Number: ";
			cin >> reg;
			avlTree.FindStudent(reg);
			break;
		default:
			exit(1);
		}

		cout << endl;
		system("pause");
		system("cls");
	} while (true);
}
