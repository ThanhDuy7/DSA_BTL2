#include "main.h"

int MAXSIZE = 0;
const long long MOD = 1e9 + 7;
vector<vector<long long>> C;

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
class BSTree {
public: 
	class Node;
private:
	Node* root;
	vector<pair<int,int>> order;
	int count;
	int first;
public:
	BSTree() : root(nullptr), count(0), first(0) {}
    ~BSTree() {}
	Node* getRoot() const {
		return root;
	}
	vector<pair<int,int>> getOrder() const {
		return order;
	}
	int getData() const {
		return root->data;
	}
	int sizeOf() {
		return count;
	}
	void clear(Node* &root) {
		if (root == NULL) return;
		clear(root->pLeft);
		clear(root->pRight);
		delete root;
		root = NULL;
		count = 0;
	}
	void clear() {
		clear(this->root);
	}
	void removeEle(const int &val,const int &key,Node* &root) {
		if (root == NULL) return;
		if (root->data == val) {
			if (root->key == key) {
				if (root->pLeft == NULL ) {
					Node* delNode = root;
					root = root->pRight;
					delete delNode;
					count--;
					return;
				} else if (root->pRight == NULL){
					Node* delNode = root;
					root = root->pLeft;
					delete delNode;
					count--;
					return;
				} else {
					Node* delNode = root->pRight;
					while (delNode->pLeft != NULL) {
						delNode = delNode->pLeft;
					}
					root->data = delNode->data;
					root->key = delNode->key;
					removeEle(delNode->data,delNode->key,root->pRight);
				}
			}  else {
				removeEle(val,key,root->pRight);
			}
		} else if ( val > root->data) {
			removeEle(val,key,root->pRight);
		} else {
			removeEle(val,key,root->pLeft);
		}
	}
	void removeNum(int num) {
		if (num >= count) {
			clear();
			return;
		}
		for (int i = 0; i < num; i++) {
			removeEle(order[i].first,order[i].second,this->root);
			order.erase(order.begin());
		}
	}
	void insert(const int &data,Node* &root) {
		if (root == NULL) {
			
			root = new Node(data);
			root->key = first++;
			count++;
			return;
		}
		if (data < root->data) {
			insert(data,root->pLeft);
		} else {
			insert(data,root->pRight);
		}
	}
	void add(int data) {
		insert(data,this->root);
		pair<int,int> p(data,first-1);
		order.push_back(p);
	}

	void print(Node* root) {
		if (root == NULL) return;
		print(root->pLeft);
		cout<<root->data<<"\n";
		print(root->pRight);
	}
	void printTree(Node* root, int indent) const {
        if (root == nullptr) {
            return;
        }

        // Print the right subtree
        printTree(root->pRight, indent + 4);

        // Print the current node with indentation
        for (int i = 0; i < indent; i++) {
            std::cout << " ";
        }
        std::cout << root->data << std::endl;

        // Print the left subtree
        printTree(root->pLeft, indent + 4);
    }
class Node
    {
    private:
        int data;
		int key;
        Node *pLeft, *pRight;
        friend class BSTree;

    public:
        Node(int value) : data(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

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
			cout<<static_cast<LeafNode*>(node)->val()<<"\n";
		} else
		cout<<node->weight()<<"\n";
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

void deleteVector(vector<BSTree*> &gojo) {
	for (auto i = 0; i < gojo.size(); i++) {
		gojo[i]->clear();
	}
	gojo.clear();
}
// Computing pascal's triangle for finding nCr
void fillPascalTriangle(int size) {

    C.resize(size + 1);

    for (int i = 0; i <= size; ++i) {

        C[i].resize(i + 1);

        // Set value of nCr = 1, for r = 0 and r = n

        C[i][0] = C[i][i] = 1;

        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
}
int countPermutations(vector<int> &nums) {

    int n = nums.size();

    if (n <= 2)
        return 1;

    // find left sub-sequence elements and right sub-sequence elements
    vector<int> left_subtree, right_subtree;

    /*
        The first element is the root of BST.
        The elements smaller than the root form the left subtree of the root node.
        The elements larger than the root form the right subtree of the root node.
    */

    for (int i = 1; i < n; ++i) {

        if (nums[i] < nums[0])
            left_subtree.push_back(nums[i]);

        else
            right_subtree.push_back(nums[i]);
    }

    // recursion with left subtree and right subtree

    long long left_res = countPermutations(left_subtree);

    long long right_res = countPermutations(right_subtree);

    int left = left_subtree.size(), right = right_subtree.size();
    int ans = (C[left + right][left] * left_res % MOD) * right_res % MOD;

    return ans;
}




void KOKUSEN(vector<BSTree*> &gojo){
	gojo[2]->add(3);
	gojo[2]->add(2);
	gojo[2]->add(3);
	gojo[2]->add(2);

	for (int i = 1; i <= MAXSIZE; i++) {
		if (gojo[i]->sizeOf() == 0) {
			cout << i << " " << "EMPTY" << endl;
			continue;
		}
		BSTree* tree = gojo[i];
		vector<pair<int,int>> order = tree->getOrder();
		int n = order.size();
		fillPascalTriangle(n);
		vector<int> firstVector;
		for (const auto& p : order) {
        	firstVector.push_back(p.first);
		}
		long long y = countPermutations(firstVector) % MAXSIZE;
		cout<<y<<endl;
		tree->removeNum(y);
		order.clear();
		order = tree->getOrder();
		for(int i = 0; i < order.size(); i++)
        cout<<order[i].first <<" "<<order[i].second <<endl;
	}
	cout<<endl;

}



bool LAPSE(HuffTree* &huffmanTree, string name, int &result)
{
	map<char, int> frequencyMap;
    for (char c : name) {
        frequencyMap[c]++;
    }
	if (frequencyMap.size() < 3) {
        // Less than 3 different characters
        return false;
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
	priority_queue<HuffTree*, vector<HuffTree*>, Compare> treeArray2 = treeArray;
	while (!treeArray2.empty()) {
		HuffTree* tree = treeArray2.top();
		treeArray2.pop();
		cout<<static_cast<LeafNode*>(tree->root())->val()<<" "<<tree->root()->weight()<<endl;
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
	return true;
}
void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;
	int result = 0;
	HuffTree* lastCus = NULL;
	vector<BSTree*> gojo;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
			for (int i = 0; i <= MAXSIZE; i++) {
				BSTree* tree = new BSTree();
				gojo.push_back(tree);
			}
    	}
        else if(str == "LAPSE") 
        {
            ss >> name;
			cout<<"LAPSE"<<" "<<name<<endl;
			HuffTree* huffmanTree = NULL;
			if (LAPSE(huffmanTree,name,result)) {
				deleteTree(lastCus);
				lastCus = huffmanTree;
				if (result % 2 == 1) {
					int ID = result % MAXSIZE + 1;
					gojo[ID]->add(result);
					gojo[ID]->add(153);
					gojo[ID]->add(500);
					gojo[ID]->add(450);
				}
                // Assuming getData is a method in your BSTree class
			} else {
				deleteTree(huffmanTree);
			}
			

    	} else if (str == "KOKUSEN") {
			cout<<"KOKUSEN"<<endl;
			KOKUSEN(gojo);
		} else if (str == "KEITEIKEN") {
			ss >> num;
			cout<<"KEITEIKEN"<<" "<<num<<endl;
			//KEITEIKEN(stoi(num));
		} else if (str == "HAND") {
			cout<<"HAND"<<endl;
			lastCus->printHuffmanTree(lastCus->root());
			lastCus->printPostOrder(lastCus->root());
		} else if (str == "LIMITLESS") {
			ss >> num;
			cout<<"LIMITLESS"<<" "<<num<<endl;
			int number = stoi(num);
			if (gojo[number]->sizeOf() == 0) {
				cout << number << " " << "EMPTY" << endl;
				continue;
			}
			gojo[number]->print(gojo[number]->getRoot());
		} else {	//CLEAVE <NUM>
			ss >> num;
			cout<<"CLEAVE"<<" "<<num<<endl;
			//CLEAVE(stoi(num));
		}
	}
	deleteVector(gojo);
	deleteTree(lastCus);
	return;
}