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
/*
template <typename E> class heap {
private:
	E* Heap; // Pointer to the heap array
	int maxsize; // Maximum size of the heap
	int n; // Number of elements now in the heap
	// Helper function to put element in its correct place
	void siftdown(int pos) {
		while (!isLeaf(pos)) { // Stop if pos is a leaf
			int j = leftchild(pos); int rc = rightchild(pos);
			if (rc < n) {
				if (Heap[rc]->weight() < Heap[j]->weight()) 
					j = rc; // Set j to greater child’s value
			}
			if (Heap[pos]->weight() < Heap[j]->weight()) return; // Done
			swap(Heap[pos], Heap[j]);
			pos = j; // Move down
		}
	}
public:
	heap(E* h, int num, int max) // Constructor
	{ Heap = h; n = num; maxsize = max;}
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
		int curr = n++;
		Heap[curr] = it; // Start at end of heap
		// Now sift up until curr’s parent > curr
		while ((curr!=0) &&
		(Heap[curr] < Heap[parent(curr)])) {
			swap(Heap[curr], Heap[parent(curr)]);
			curr = parent(curr);
		}
	}
	void printHeap() const {
        for (int i = 0; i < n; ++i) {
            cout << Heap[i] << " ";
        }
        cout << std::endl;
    }
// Remove first value
	E removefirst() {
		//Assert (n > 0, "Heap is empty");
		swap(Heap[0], Heap[--n]); // std::swap first with last value
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
			(Heap[pos] < Heap[parent(pos)])) {
				swap(Heap[pos], Heap[parent(pos)]); // Push up large key
				pos = parent(pos);
			}
			if (n != 0) siftdown(pos); // Push down small key
		}
	return Heap[n];
	}
};
*/


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
	HuffNode<E>* Root;
	int order;
	int level; // Tree root
public:
	HuffTree(E& val, int freq, int order) // Leaf constructor
	{ Root = new LeafNode<E>(val, freq); this->order = order; this->level = 1;}
	// Internal node constructor
	HuffTree(HuffTree<E>* l, HuffTree<E>* r, int order)
	{ Root = new IntlNode<E>(l->root(), r->root()); this->order = order;
		this->level = max(l->level, r->level) + 1;}
	~HuffTree() {} // Destructor
	HuffNode<E>* root() { return Root; } // Get root
	int weight() { return Root->weight(); }
	int Order() { return order;}// Root weight
	void print(const std::string& prefix, HuffNode<E>* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix << (isLeft ? "|-- " : "\\-- ") << node->weight();
		if (node->isLeaf()) {
			cout<<static_cast<LeafNode<E>*>(node)->val();
		}
		cout<<endl;
        if (!node->isLeaf()) {
            print(prefix + (isLeft ? "|   " : "    "), static_cast<IntlNode<E>*>(node)->left(), true);
            print(prefix + (isLeft ? "|   " : "    "), static_cast<IntlNode<E>*>(node)->right(), false);
        } 
    }
}
	void printHuffmanTree(HuffNode<E>* node) {
		if (!node) {
			std::cout << "The tree is empty." << std::endl;
			return;
		}

		print("", node, false);
	}
};
class Compare {
public:
    bool operator()(HuffTree<char>* a, HuffTree<char>* b)
    {
        if(a->weight() == b->weight()) {
            if (a->root()->isLeaf() && b->root()->isLeaf()) {
				LeafNode<char>* leafA = static_cast<LeafNode<char>*>(a->root());
				LeafNode<char>* leafB = static_cast<LeafNode<char>*>(b->root());
                return leafA->val() > leafB->val();
            }
			return a->Order() > b->Order();
        }
        // Defining priority on the basis of frequency
        return a->weight() > b->weight();
    }
};
// Build a Huffman tree from a collection of frequencies
template <typename E> HuffTree<E>*
buildHuff(priority_queue<HuffTree<E>*, vector<HuffTree<E>*>, Compare> TreeArray, int count) {
	HuffTree<char> *temp1, *temp2, *temp3 = NULL;
	while (TreeArray.size() != 1) {
        // Node which has least frequency
        HuffTree<char>* left = TreeArray.top();
        // Remove node from Priority Queue
        TreeArray.pop();

        HuffTree<char>* right = TreeArray.top();
        TreeArray.pop();

        // A new node is formed with frequency left->freq + right->freq
        // We take data as '$' because we are only concerned with the frequency
        HuffTree<char>* node =new HuffTree<char>(left, right,++count);
        // Push back node created to the Priority Queue
        TreeArray.push(node);
    }
    return TreeArray.top();
		
}

void LAPSE(string name)
{

	map<char, int> frequencyMap;
    for (char c : name) {
        frequencyMap[c]++;
    }
	vector<pair<char, int>> sortedEntries(frequencyMap.begin(), frequencyMap.end());

	frequencyMap.clear();
	for (auto& entry : sortedEntries) {
        char character = entry.first;
        int frequency = entry.second;
		char encryptedChar;	
        // Encrypt using Caesar cipher with step equal to frequency
		if (character >= 'A' && character <= 'Z') {
			encryptedChar = 'A' + (character - 'A' + frequency) % 26;
		} else {
			encryptedChar = 'a' + (character - 'a' + frequency) % 26;
		}
        entry.first = encryptedChar;

        // Recount the frequency of the encrypted character
        frequencyMap[encryptedChar]+=frequency;
    }
	sortedEntries.assign(frequencyMap.begin(), frequencyMap.end());
	sort(sortedEntries.begin(), sortedEntries.end(), [](const auto& a, const auto& b) {
    if (a.second == b.second) {
        return a.first < b.first; // Sort by character if frequencies are equal
    }
    return a.second < b.second;
});
for (const auto& entry : sortedEntries) {
	char character = entry.first;
	int frequency = entry.second;
	cout << character << " " << frequency << endl;	
}

    // Step 2: Create a vector of HuffTree<char>*
    priority_queue<HuffTree<char>*, vector<HuffTree<char>*>, Compare> treeArray;
    for (const auto& entry : sortedEntries) {
        char character = entry.first;
        int frequency = entry.second;
        treeArray.push(new HuffTree<char>(character, frequency,0));
    }

    // Step : Build a Huffman tree
   HuffTree<char>* huffmanTree = buildHuff(treeArray, treeArray.size());
	huffmanTree->printHuffmanTree(huffmanTree->root());
    //result.push_back(huffmanTree);

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