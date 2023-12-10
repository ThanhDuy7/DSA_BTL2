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
	virtual int Level() = 0;
	virtual int Order() = 0;
	virtual void setLevel(int level) = 0;
	virtual HuffNode<E>* left() = 0;
	virtual HuffNode<E>* right() = 0;
	virtual void setLeft(HuffNode<E>* b) = 0;
	virtual void setRight(HuffNode<E>* b) = 0;
};
template <typename E> // Leaf node subclass
class LeafNode : public HuffNode<E> {
private:
	E it; // Value
	int wgt; // Weight
	int order;
	int level;
public:
	LeafNode(const E& val, int freq, int order) // Constructor
	{ it = val; wgt = freq; this->order = order; level = 0;}
	int weight() { return wgt; }
	int Level() { return level; }
	void setLevel(int level) { this->level = level; }
	int Order() { return order; }
	E val() { return it; }
	bool isLeaf() { return true; }
	HuffNode<E>* left() {return NULL;}
	HuffNode<E>* right() {return NULL;}
	void setLeft(HuffNode<E>* b) {}
	void setRight(HuffNode<E>* b) {}
};
template <typename E> // Internal node subclass
class IntlNode : public HuffNode<E> {
private:
	HuffNode<E>* lc; // Left child
	HuffNode<E>* rc; // Right child
	int wgt; // Subtree weight
	int order;
	int level;
public:
	IntlNode(HuffNode<E>* l, HuffNode<E>* r, int order)
	{ wgt = l->weight() + r->weight(); lc = l; rc = r; this->order = order; level = max(l->Level(), r->Level())+1;}
	int weight() { return wgt; }
	int Level() { return level; }
	void setLevel(int level) { this->level = level; }
	int Order() { return order; }
	bool isLeaf() { return false; }
	HuffNode<E>* left() { return lc; }
	void setLeft(HuffNode<E>* b)	{ lc = (HuffNode<E>*)b; }
	HuffNode<E>* right() { return rc; }
	void setRight(HuffNode<E>* b)	{ rc = (HuffNode<E>*)b; }
	
};
// HuffTree is a template of two parameters: the element
// type being coded and a comparator for two such elements.
template <typename E>
class HuffTree {
private:
	HuffNode<E>* Root; // Tree root
public:
	HuffTree(E& val, int freq, int order) // Leaf constructor
	{ Root = new LeafNode<E>(val, freq, order); }
	// Internal node constructor
	HuffTree(HuffTree<E>* l, HuffTree<E>* r, int order)
	{ 
		Root = new IntlNode<E>(l->root(), r->root(), order);
		int count = 0;
		balanceTree(Root,count);
	}
	~HuffTree() {
		deleteTree(Root);
		Root = NULL;
	} // Destructor
	HuffNode<E>* root() { return Root; } // Get root
	int weight() { return Root->weight(); }
	int Order() { return Root->Order(); }// Root level
	int Level() { return Root->Level(); }// Root order
	void deleteTree(HuffNode<E>* node) {
		if (node->isLeaf()) {
			delete node;
			return;
		}
		deleteTree(node->left());
		deleteTree(node->right());
		delete node;
	}
HuffNode<E>* rotateRight(HuffNode<E>* &root) {
		HuffNode<E>* temp = root->left();
		root->setLeft(temp->right());
		temp->setRight(root);
		root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
		temp->setLevel(max(temp->left()->Level(),root->Level()) + 1);
		return temp;
	}
	HuffNode<E>* rotateLeft(HuffNode<E>* &root) {
		HuffNode<E>* temp = root->right();
		root->setRight(temp->left());
		temp->setLeft(root);
		root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
		temp->setLevel(max(temp->left()->Level(),root->Level()) + 1);
		return temp;
	}
	void balanceLeft(HuffNode<E>* &root) {
		HuffNode<E>* left = root->left();
		int leftBalance = left->left()->Level() - left->right()->Level();

		if (leftBalance >= 0) {
			root = rotateRight(root);
		} else if (leftBalance <= -1) {
			left = rotateLeft(left);
			root = rotateRight(root);
		}
	}
	void balanceRight(HuffNode<E>* &root) {
		HuffNode<E>* right = root->right();
		int rightBalance = right->left()->Level() - right->right()->Level();

		if (rightBalance <= -1) {
			root = rotateLeft(root);
		} else if (rightBalance >= 1) {
			right = rotateRight(right);
			root = rotateLeft(root);
		}
	}
	void balanceTree(HuffNode<E>* &root, int& count) {
		if (root->isLeaf()) {
			return;
		}
		if (count >= 3) return;
		int balance = root->left()->Level() - root->right()->Level();

		if (balance > 1) { // leftHigher
			balanceLeft(root);
			count++;
		} else if (balance < -1) {
			balanceRight(root);
			count++;
		}
		HuffNode<E>* left = root->left();
		balanceTree(left,count);
		HuffNode<E>* right = root->right();
		balanceTree(right,count);
		
	}
	void print(const std::string& prefix, HuffNode<E>* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix << (isLeft ? "|--- " : "\\--- ") << node->weight()<< " "<<node->Level();
		if (node->isLeaf()) {
			cout<<static_cast<LeafNode<E>*>(node)->val();
		}
		cout<<endl;
        if (!node->isLeaf()) {
            print(prefix + (isLeft ? "|     " : "      "), static_cast<IntlNode<E>*>(node)->left(), true);
            print(prefix + (isLeft ? "|     " : "      "), static_cast<IntlNode<E>*>(node)->right(), false);
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
    bool operator()(HuffTree<char>* &a, HuffTree<char>* 
	&b)
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
	while (TreeArray.size() != 1) {
        // Node which has least frequency
        HuffTree<char>* left = TreeArray.top();
        // Remove node from Priority Queue
        TreeArray.pop();

        HuffTree<char>* right = TreeArray.top();
        TreeArray.pop();

        // A new node is formed with frequency left->freq + right->freq
        // We take data as '$' because we are only concerned with the frequency
		cout<<count<<endl;
        HuffTree<char>* node =new HuffTree<char>(left, right,++count);
        // Push back node created to the Priority Queue
        TreeArray.push(node);
    }
    return TreeArray.top();
		
}


void buildHuffCodes(HuffNode<char>* root, string code, unordered_map<char, string>& huffCodes) {
    if (root->isLeaf()) {
        huffCodes[static_cast<LeafNode<char>*>(root)->val()] = code;
        return;
    }

    buildHuffCodes(root->left(), code + "0", huffCodes);
    buildHuffCodes(root->right(), code + "1", huffCodes);
}

// Function to encrypt a string using Huffman codes
string encryptString(const string& input, const unordered_map<char, string>& huffCodes) {
    string result;
    for (char ch : input) {
		if (huffCodes.count(ch) > 0) {
    	result += huffCodes.at(ch);
        }
    }
    return result;
}
void LAPSE(string name)
{
	if (name.size() <= 3) return;
	map<char, int> frequencyMap;
    for (char c : name) {
        frequencyMap[c]++;
    }
	string encryptedName = name;
    for (char& c : encryptedName) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + frequencyMap[c]) % 26 + base;
        }
    }
	cout<<encryptedName<<endl;

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
   HuffTree<char>* huffmanTree = buildHuff(treeArray,0);
   treeArray.pop();
	huffmanTree->printHuffmanTree(huffmanTree->root());
	int result;
	if (huffmanTree->root()->isLeaf()) {
		result = 0;
	} else {
		unordered_map<char, string> huffCodes;
    	buildHuffCodes(huffmanTree->root(), "", huffCodes);


	for (const auto& entry : huffCodes) {
		char character = entry.first;
		string code = entry.second;
		cout << character << " " << code << endl;	
	}
    	string s = encryptString(encryptedName, huffCodes);
		cout << "Encrypted String: " << s << endl;
		string str = "";
		int n = s.size();
		for (int i = n - 1; i > n - 11; i--) {
			if (i < 0) break;
			str +=	s[i];
		}
		cout<<str<<endl;
		bitset<64> bits(str);
		result = bits.to_ulong();
		cout<<result<<endl;
	}
	delete huffmanTree;
	huffmanTree = NULL;
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