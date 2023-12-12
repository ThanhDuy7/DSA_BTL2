#include "main.h"

int MAXSIZE = 0;
/*
template <class T>
class AVLtree
{
public: 
	class Node;
private:
	Node* root;
public:
	AVLtree(): root(NULL) {}
	~AVLtree(){}
	int getHeight() {
		return this->getHeightRec(this->root);
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
class HuffNode {
public:
	virtual ~HuffNode() {} // Base destructor
	virtual int weight() = 0; // Return frequency
	virtual bool isLeaf() = 0; // Determine type
	virtual int Level() = 0;
	virtual int Order() = 0;
	virtual void setLevel(int level) = 0;
	virtual HuffNode* left() = 0;
	virtual HuffNode* right() = 0;
	virtual void setLeft(HuffNode* b) = 0;
	virtual void setRight(HuffNode* b) = 0;
};
// Leaf node subclass
class LeafNode : public HuffNode {
private:
	char it; // Value
	int wgt; // Weight
	int order;
	int level;
public:
	LeafNode(const char& val, int freq, int order) // Constructor
	{ it = val; wgt = freq; this->order = order; level = 0;}
	int weight() { return wgt; }
	int Level() { return level; }
	void setLevel(int level) { this->level = level; }
	int Order() { return order; }
	char val() { return it; }
	bool isLeaf() { return true; }
	HuffNode* left() {return NULL;}
	HuffNode* right() {return NULL;}
	void setLeft(HuffNode* b) {}
	void setRight(HuffNode* b) {}
};
// Internal node subclass
class IntlNode : public HuffNode {
private:
	HuffNode* lc; // Left child
	HuffNode* rc; // Right child
	int wgt; // Subtree weight
	int order;
	int level;
public:
	IntlNode(HuffNode* &l, HuffNode* &r, int order)
	{ wgt = l->weight() + r->weight(); lc = l; rc = r; this->order = order; level = max(l->Level(), r->Level())+1;}
	int weight() { return wgt; }
	int Level() { return level; }
	void setLevel(int level) { this->level = level; }
	int Order() { return order; }
	bool isLeaf() { return false; }
	HuffNode* left() { return lc; }
	void setLeft(HuffNode* b)	{ lc = (HuffNode*)b; }
	HuffNode* right() { return rc; }
	void setRight(HuffNode* b)	{ rc = (HuffNode*)b; }
	
};
// HuffTree is a template of two parameters: the element
// type being coded and a comparator for two such elements.
class HuffTree {
private:
	HuffNode* Root; // Tree root
public:
	HuffTree(char& val, int freq, int order) // Leaf constructor
	{ Root = new LeafNode(val, freq, order); }
	// Internal node constructor
	HuffTree(HuffTree* &l, HuffTree* &r, int order)
	{ 
		HuffNode* left = l->root();
		HuffNode* right = r->root();
		Root = new IntlNode(left, right, order);
		int count = 0;
		balanceTree(Root,count);
	}
	~HuffTree() {
	}
	HuffNode* root() { return Root; } // Get root
	int weight() { return Root->weight(); }
	int Order() { return Root->Order(); }// Root level
	int Level() { return Root->Level(); }// Root order
	
HuffNode* rotateRight(HuffNode* &root) {
		HuffNode* temp = root->left();
		root->setLeft(temp->right());
		temp->setRight(root);
		root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
		temp->setLevel(max(temp->left()->Level(),root->Level()) + 1);
		return temp;
	}
	HuffNode* rotateLeft(HuffNode* &root) {
		HuffNode* temp = root->right();
		root->setRight(temp->left());
		temp->setLeft(root);
		root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
		temp->setLevel(max(temp->left()->Level(),root->Level()) + 1);
		return temp;
	}
	void balanceLeft(HuffNode* &root) {
		HuffNode* left = root->left();
		int leftBalance = left->left()->Level() - left->right()->Level();

		if (leftBalance >= 0) {
			root = rotateRight(root);
		} else if (leftBalance <= -1) {
			left = rotateLeft(left);
			root = rotateRight(root);
		}
	}
	void balanceRight(HuffNode* &root) {
		HuffNode* right = root->right();
		int rightBalance = right->left()->Level() - right->right()->Level();

		if (rightBalance <= -1) {
			root = rotateLeft(root);
		} else if (rightBalance >= 1) {
			right = rotateRight(right);
			root = rotateLeft(root);
		}
	}
	void balanceTree(HuffNode* &root, int& count) {
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
		HuffNode* left = root->left();
		balanceTree(left,count);
		HuffNode* right = root->right();
		balanceTree(right,count);
	}
	void print(const std::string& prefix, HuffNode* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix << (isLeft ? "|--- " : "\\--- ") << node->weight()<< " "<<node->Level();
		if (node->isLeaf()) {
			cout<<static_cast<LeafNode*>(node)->val();
		}
		cout<<endl;
        if (!node->isLeaf()) {
            print(prefix + (isLeft ? "|     " : "      "), static_cast<IntlNode*>(node)->left(), true);
            print(prefix + (isLeft ? "|     " : "      "), static_cast<IntlNode*>(node)->right(), false);
        } 
    }
}
	void printHuffmanTree(HuffNode* node) {
		if (!node) {
			std::cout << "The tree is empty." << std::endl;
			return;
		}

		print("", node, false);
	}
	void printPostOrder(HuffNode* node) {
		if (!node) {
			return;
		}
		printPostOrder(node->left());
		printPostOrder(node->right());
		if (node->isLeaf()) {
			cout<<static_cast<LeafNode*>(node)->val()<<endl;
		} else
		cout<<node->weight()<<endl;
	}
};
class Compare {
public:
    bool operator()(HuffTree* a, HuffTree* b)
    {
        if(a->weight() == b->weight()) {
            if (a->root()->isLeaf() && b->root()->isLeaf()) {
				LeafNode* leafA = static_cast<LeafNode*>(a->root());
				LeafNode* leafB = static_cast<LeafNode*>(b->root());
				if (leafA->val() >= 'A' && leafA->val() <= 'Z' && leafB->val() >= 'a' && leafB->val() <= 'z') {
					return true;
				} else if (leafA->val() >= 'a' && leafA->val() <= 'z' && leafB->val() >= 'A' && leafB->val() <= 'Z') {
					return false;
				}else	return leafA->val() > leafB->val();
            }
			return a->Order() > b->Order();
        }
        // Defining priority on the basis of frequency
        return a->weight() > b->weight();
    }
};

void buildHuffCodes(HuffNode* root, string code, unordered_map<char, string>& huffCodes) {
    if (root->isLeaf()) {
        huffCodes[static_cast<LeafNode*>(root)->val()] = code;
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

void deleteRoot(HuffNode* &root) {
	if (!root) {
		return;
	}
	if (root->isLeaf()) {
		delete root;
		root = NULL;
		return;
	}
	HuffNode* left = root->left();
	HuffNode* right = root->right();
	deleteRoot(left);
	deleteRoot(right);
	delete root;
	root = NULL;
}
void deleteTree(HuffTree* &tree) {
	if (!tree) {
		return;
	}
	HuffNode* root = tree->root();
	deleteRoot(root);
	delete tree;
}
void LAPSE(HuffTree* &huffmanTree, string name)
{
	map<char, int> frequencyMap;
    for (char c : name) {
        frequencyMap[c]++;
    }
	if (frequencyMap.size() < 3) {
        // Less than 3 different characters
        return;
    }
	string encryptedName = name;
    for (char& c : encryptedName) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + frequencyMap[c]) % 26 + base;
        }
    }

	vector<pair<char, int>> sortedEntries(frequencyMap.begin(), frequencyMap.end());
	
	frequencyMap.clear();
	for (auto& entry : sortedEntries) {
        char character = entry.first;
        int frequency = entry.second;
		char encryptedChar;	
		if (character >= 'A' && character <= 'Z') {
			encryptedChar = 'A' + (character - 'A' + frequency) % 26;
		} else {
			encryptedChar = 'a' + (character - 'a' + frequency) % 26;
		}
        entry.first = encryptedChar;
        frequencyMap[encryptedChar]+=frequency;
    }
	sortedEntries.assign(frequencyMap.begin(), frequencyMap.end());
    // Step 2: Create a vector of HuffTree<char>*
    priority_queue<HuffTree*, vector<HuffTree*>, Compare> treeArray;
    for (const auto& entry : sortedEntries) {
        char character = entry.first;
        int frequency = entry.second;
		HuffTree* manTree = new HuffTree(character, frequency,0);
        treeArray.push(manTree);
    }
	priority_queue<HuffTree*, vector<HuffTree*>, Compare> copyTreeArray = treeArray;
for (int i = 0; i < treeArray.size(); i++) {
		HuffTree* tree = copyTreeArray.top();
		copyTreeArray.pop();
		LeafNode* leafA = static_cast<LeafNode*>(tree->root());
		cout<<leafA->val()<<" "<<leafA->weight()<<endl;
	}
	int count = 0;
	
	while (treeArray.size() > 1) {
        HuffTree* left = treeArray.top();
        treeArray.pop();

        HuffTree* right = treeArray.top();
        treeArray.pop();
        HuffTree* node =new HuffTree(left, right,++count);
        treeArray.push(node);
		delete left;
		delete right;
    }
	huffmanTree = treeArray.top();
	treeArray.pop();
	

	//huffmanTree->printHuffmanTree(huffmanTree->root());
	int result;
	
	if (huffmanTree->root()->isLeaf()) {
		result = 0;
	} else {
		unordered_map<char, string> huffCodes;
    	buildHuffCodes(huffmanTree->root(), "", huffCodes);
    	string s = encryptString(encryptedName, huffCodes);
		string str = "";
		int n = s.size();
		for (int i = n - 1; i > n - 11; i--) {
			if (i < 0) break;
			str +=	s[i];
		}
		bitset<64> bits(str);
		result = bits.to_ulong();
		cout<<result<<endl;
	}
	return;
}
void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;
	HuffTree* huffmanTree = NULL;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "LAPSE") 
        {
            ss >> name;
			cout<<"LAPSE"<<" "<<name<<endl;
			LAPSE(huffmanTree,name);
    	} else if (str == "KOKUSEN") {
			cout<<"KOKUSEN"<<endl;
			//KOKUSEN();
		} else if (str == "KEITEIKEN") {
			ss >> num;
			cout<<"KEITEIKEN"<<" "<<num<<endl;
			//KEITEIKEN(stoi(num));
		} else if (str == "HAND") {
			cout<<"HAND"<<endl;
			huffmanTree->printHuffmanTree(huffmanTree->root());
			huffmanTree->printPostOrder(huffmanTree->root());
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
	//delete enter;
	return;
}