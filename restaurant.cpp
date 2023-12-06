#include "main.h"

int MAXSIZE = 0;
/*
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
*/
// Heap class
template <typename E>
struct minTreeComp {
    static bool prior(const E& a, const E& b) {
        return a->weight() < b->weight();
    }
};
template <typename E, typename Comp> class heap {
private:
	E* Heap; // Pointer to the heap array
	int maxsize; // Maximum size of the heap
	int n; // Number of elements now in the heap
	// Helper function to put element in its correct place
	void siftdown(int pos) {
		while (!isLeaf(pos)) { // Stop if pos is a leaf
			int j = leftchild(pos); int rc = rightchild(pos);
			if ((rc < n) && Comp::prior(Heap[rc], Heap[j]))
			j = rc; // Set j to greater child’s value
			if (Comp::prior(Heap[pos], Heap[j])) return; // Done
			std::swap(Heap[pos], Heap[j]);
			pos = j; // Move down
		}
	}
public:
	heap(E* h, int num, int max) // Constructor
	{ Heap = h; n = num; maxsize = max; buildHeap(); }
	int size() const // Return current heap size
	{ return n; }
	bool isLeaf(int pos) const // True if pos is a leaf
	{ return (pos >= n/2) && (pos < n); }
	int leftchild(int pos) const
	{ return 2*pos + 1; } // Return leftchild position
	int rightchild(int pos) const
	{ return 2*pos + 2; } // Return rightchild position
	int parent(int pos) const // Return parent position
	{ return (pos-1)/2; }
	void buildHeap() // Heapify contents of Heap
	{ for (int i=n/2-1; i>=0; i--) siftdown(i); }
	// Insert "it" into the heap
	void insert(const E& it) {
		//Assert(n < maxsize, "Heap is full");
		int curr = n++;
		Heap[curr] = it; // Start at end of heap
		// Now sift up until curr’s parent > curr
		while ((curr!=0) &&
		(Comp::prior(Heap[curr], Heap[parent(curr)]))) {
			std::swap(Heap[curr], Heap[parent(curr)]);
			curr = parent(curr);
		}
	}
// Remove first value
	E removefirst() {
		//Assert (n > 0, "Heap is empty");
		std::swap(Heap[0], Heap[--n]); // std::swap first with last value
		if (n != 0) siftdown(0); // Siftdown new root val
		return Heap[n]; // Return deleted value
	}
	// Remove and return element at specified position
	E remove(int pos) {
		//Assert((pos >= 0) && (pos < n), "Bad position");
		if (pos == (n-1)) n--; // Last element, no work to do
		else {
			std::swap(Heap[pos], Heap[--n]); // std::swap with last value
			while ((pos != 0) &&
			(Comp::prior(Heap[pos], Heap[parent(pos)]))) {
				std::swap(Heap[pos], Heap[parent(pos)]); // Push up large key
				pos = parent(pos);
			}
			if (n != 0) siftdown(pos); // Push down small key
		}
	return Heap[n];
	}
};


// Huffman tree node abstract base class
template <typename E> class HuffNode {
public:
	virtual ~HuffNode() {} // Base destructor
	virtual int weight() = 0; // Return frequency
	virtual bool isLeaf() = 0; // Determine type
};
template <typename E> // Leaf node subclass
class LeafNode : public HuffNode<E> {
private:
	E it; // Value
	int wgt; // Weight
public:
	LeafNode(const E& val, int freq) // Constructor
	{ it = val; wgt = freq; }
	int weight() { return wgt; }
	E val() { return it; }
	bool isLeaf() { return true; }
};
template <typename E> // Internal node subclass
class IntlNode : public HuffNode<E> {
private:
	HuffNode<E>* lc; // Left child
	HuffNode<E>* rc; // Right child
	int wgt; // Subtree weight
public:
	IntlNode(HuffNode<E>* l, HuffNode<E>* r)
	{ wgt = l->weight() + r->weight(); lc = l; rc = r; }
	int weight() { return wgt; }
	bool isLeaf() { return false; }
	HuffNode<E>* left() const { return lc; }
	void setLeft(HuffNode<E>* b)	{ lc = (HuffNode<E>*)b; }
	HuffNode<E>* right() const { return rc; }
	void setRight(HuffNode<E>* b)	{ rc = (HuffNode<E>*)b; }
};
// HuffTree is a template of two parameters: the element
// type being coded and a comparator for two such elements.
template <typename E>
class HuffTree {
private:
	HuffNode<E>* Root; // Tree root
public:
	HuffTree(E& val, int freq) // Leaf constructor
	{ Root = new LeafNode<E>(val, freq); }
	// Internal node constructor
	HuffTree(HuffTree<E>* l, HuffTree<E>* r)
	{ Root = new IntlNode<E>(l->root(), r->root()); }
	~HuffTree() {} // Destructor
	HuffNode<E>* root() { return Root; } // Get root
	int weight() { return Root->weight(); } // Root weight
};

// Build a Huffman tree from a collection of frequencies
template <typename E> HuffTree<E>*
buildHuff(HuffTree<E>** TreeArray, int count) {
	heap<HuffTree<E>*, minTreeComp<E>>* forest = new heap<HuffTree<E>*, minTreeComp<E>>(TreeArray, count, count);
	HuffTree<char> *temp1, *temp2, *temp3 = NULL;
	while (forest->size() > 1) {
		temp1 = forest->removefirst(); // Pull first two trees
		temp2 = forest->removefirst(); // off the list
		temp3 = new HuffTree<E>(temp1, temp2);
		forest->insert(temp3); // Put the new tree back on list
		delete temp1; // Must delete the remnants
		delete temp2; // of the trees we created
	}
	return temp3;
}

void LAPSE(string name)
{

	std::map<char, int> frequencyMap;
    for (char c : name) {
        frequencyMap[c]++;
    }
	for (const auto& entry : frequencyMap) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
    // Step 2: Create a vector of HuffTree<char>*
    std::vector<HuffTree<char>*> treeArray;
    for (const auto& entry : frequencyMap) {
        char character = entry.first;
        int frequency = entry.second;
        treeArray.push_back(new HuffTree<char>(character, frequency));
    }

    // Step 3: Sort the vector based on frequency and character order
    std::sort(treeArray.begin(), treeArray.end(), [](const auto& a, const auto& b) {
        if (a->weight() == b->weight()) {
            return a->root()->weight() < b->root()->weight();
        }
        return a->weight() < b->weight();
    });

    // Step 4: Build a Huffman tree
    HuffTree<char>* huffmanTree = buildHuff(treeArray.data(), treeArray.size());

    // Step 5: Return the Huffman tree
    std::vector<HuffTree<char>*> result;
    result.push_back(huffmanTree);

    return;
}
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
			LAPSE(name);
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