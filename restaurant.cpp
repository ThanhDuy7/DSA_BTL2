#include "main.h"

int MAXSIZE = 0;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}
template <class T>
class AVLtree
{
public: 
	class Node;
private:
	Node* root;
protected:
	int getHeightRec(Node* node) {
		if (node == NULL) return 0;
		return node->height;
		int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
	}
public:
	AVLtree(): root(NULL) {}
	~AVLtree(){}
	int getHeight() {
		return this->getHeightRec(this->root);
	}
	void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

	void AVLdelete(Node* &root,const T &value, bool &shorter) {
		if (root == NULL) {
			shorter = false;
			return;
		} else if (value < root->data) {
			AVLdelete(root->pLeft, value, shorter);
			if (shorter) {
				deleteRightBalance(root, shorter);
			}
		} else if (value > root->data) {
			AVLdelete(root->pRight, value, shorter);
			if (shorter) {
				deleteLeftBalance(root, shorter);
			}
		} else {
			Node* temp = root;
			if (!root->pRight) {
				root = root->pLeft;
				shorter = true;
				delete temp;
				return;
			}
			if (!root->pLeft) {
				root = root->pRight;
				shorter = true;
				delete temp;
				return;
			}
			temp = root->pLeft;
			while(temp->pRight) {
				temp = temp->pRight;
			}
			
		}
	}
	void remove(const T &value)
    {
        if (root == NULL) return;
		bool shorter;
		AVLdelete(root,value,shorter);
    }
	class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "LAPSE") // RED <NAME> <ENERGY>
        {
            ss >> name;
			cout<<"LAPSE"<<" "<<name<<endl;
			//LAPSE(name);
    	} else if (str == "KOKUSEN") {
			cout<<"KOKUSEN"<<endl;
			//KOKUSEN();
		} else if (str == "KEITEIKEN") {
			ss >> num;
			cout<<"KEITEIKEN"<<" "<<num<<endl;
			//KEITEIKEN(stoi(num));
		} else if (str == "HAND") {
			cout<<"HAND"<<endl;
			//HAND();
		} else if (str == "LIMITLESS") {
			ss >> num;
			cout<<"LIMITLESS"<<" "<<num<<endl;
			//LIMITLESS(stoi(num));
		} else {	//CLEAVE <NUM>
			ss >> num;
			cout<<"CLEAVE"<<" "<<num<<endl;
			//CLEAVE(stoi(num));
		}
	}
	return;
}