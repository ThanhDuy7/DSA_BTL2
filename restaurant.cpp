#include "main.h"

int MAXSIZE = 0;
const long long MOD = 1e9 + 7;
vector<vector<long long>> C;



class Heap {
protected:
	struct HeapNode {
        int numberGuest;
        int id;
		int order;
		HeapNode() {
			numberGuest = 0;
			id = 0;
			order = 0;
		}
    };

    HeapNode* elements;
    int count;
	long long first;
    // ID, numberGuest
    unordered_map<int, int> idToIndex;  // ID, HeapIndex
	class sooner {
public:
	bool operator()(const Heap::HeapNode& a, const Heap::HeapNode& b)
	{
		if(a.numberGuest == b.numberGuest) {
			return a.order <  b.order;
		}
		return a.numberGuest < b.numberGuest;
	}
};
	priority_queue<HeapNode, vector<HeapNode>, sooner> pq;
public:
    Heap() {
        this->count = 0;
		this->first = 0;
        this->elements = new HeapNode[5];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(int item, int id) {
	}
    bool isEmpty();
    bool contains(int item);
    int peek();
    bool pop();
    int size();
    
    void printHeap()
    {
        for (int i = 0; i < MAXSIZE; i++)
           cout << elements[i].numberGuest << ", "<<elements[i].id<<", "<<elements[i].order<<endl;
    }
private:
    void reheapUp(int position);
    void reheapDown(int position);
};


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
	virtual void setOrder(int order) = 0;
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
	void setOrder(int order) { this->order = order; }
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
	void setOrder(int order) { this->order = order; }
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
		bool rotate = false;
		while (count <3) {
			balanceTree(Root,count,rotate);
			if (!rotate) 
			break;
			rotate = false;
		}
			
		
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
	HuffNode* balanceLeft(HuffNode* &root) {
		HuffNode* left = root->left();
		int leftBalance = left->left()->Level() - left->right()->Level();

		if (leftBalance >= 0) {
			root = rotateRight(root);
		} else if (leftBalance <= -1) {
			left = rotateLeft(left);
			root->setLeft(left);

			root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);


			root = rotateRight(root);

			root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
			
		}
		return root;
	}
	HuffNode* balanceRight(HuffNode* &root) {
		HuffNode* right = root->right();
		int rightBalance = right->left()->Level() - right->right()->Level();

		if (rightBalance <= -1) {
			root = rotateLeft(root);
		} else if (rightBalance >= 1) {
			right = rotateRight(right);
			root->setRight(right);


			root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);

			root = rotateLeft(root);

			root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
		}
		return root;
	}
	
	int shortestDeep(HuffNode* root) {
		if (root->isLeaf()) {
			return 0;
		}
		int left = shortestDeep(root->left());
		int right = shortestDeep(root->right());
		return min(left,right) + 1;
	}
	
	HuffNode* balanceTree(HuffNode* &root, int& count, bool &rotate) {
		if (root->isLeaf()) {
			rotate = false;
			return root;
		}
		if (count >= 3) {
			rotate = false;
			return root;
		}
		int balance = root->left()->Level() - root->right()->Level();
		
		if (balance > 1) { 
			root = balanceLeft(root);
			root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
			count++;
			rotate = true;
			return root;
		} else if (balance < -1) {
			root = balanceRight(root);
			root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
			count++;
			rotate = true;
			return root;
		} 
		HuffNode* left = root->left();
		root->setLeft(balanceTree(left,count,rotate));

		root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
		
		if (rotate) return root;
		HuffNode* right = root->right();
		root->setRight(balanceTree(right,count,rotate));
		root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
		if (rotate) return root;
		return root;
	}
	
	void print(const std::string& prefix, HuffNode* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix << (isLeft ? "|--- " : "\\--- ") << node->weight()<< " "<<node->Level();
		if (node->isLeaf()) {
			cout<<static_cast<LeafNode*>(node)->val();
		}
		cout<<endl;
        if (!node->isLeaf()) {
            print(prefix + (isLeft ? "|     " : "      "), static_cast<IntlNode*>(node)->right(), true);
            print(prefix + (isLeft ? "|     " : "      "), static_cast<IntlNode*>(node)->left(), false);
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
        delete gojo[i];  // Delete the BSTree object
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
}

void printQueue(priority_queue<HuffTree*, vector<HuffTree*>, Compare> pq) {
	while (!pq.empty()) {
		HuffTree* tree = pq.top();
		pq.pop();
		cout<<tree->root()->weight()<<" "<<tree->root()->Order()<<" | ";
	}
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
		cout<<"count"<<count<<endl;
        HuffTree* left = treeArray.top();
        treeArray.pop();
	
        HuffTree* right = treeArray.top();
        treeArray.pop();
		
        HuffTree* node =new HuffTree(left, right,++count);
		node->root()->setOrder(count);
        treeArray.push(node);
		printQueue(treeArray);
		//cout<<treeArray.size()<<": "<<node->root()->Order()<<endl;
		//node->printHuffmanTree(node->root());
		cout<<endl;
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
	Heap sukuna;
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
				lastCus->printHuffmanTree(lastCus->root());
				int ID = result % MAXSIZE + 1;
				if (result % 2 == 0) {
					gojo[ID]->add(result);
				} else {
					
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
			sukuna.printHeap();
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