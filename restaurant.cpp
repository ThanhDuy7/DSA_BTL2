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
		queue<int> orderQueue;
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
			return a.order >  b.order;
		}
		return a.numberGuest > b.numberGuest;
	}
};
	priority_queue<HeapNode, vector<HeapNode>, sooner> pq;
public:
    Heap() {
        this->count = 0;
		this->first = 0;
        this->elements = new HeapNode[10];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(int item, int id) {
		if (idToIndex.find(id) != idToIndex.end()) {
			int index = idToIndex[id];
			elements[index].numberGuest++;
			elements[index].order = first++;
			elements[index].orderQueue.push(item);
			vector<HeapNode> tempVector;
			while (!pq.empty()) {
				HeapNode node = pq.top();
				pq.pop();
				if (node.id == id) {
					node.numberGuest = elements[index].numberGuest;
					node.order = elements[index].order;
					node.orderQueue = elements[index].orderQueue;

				}
				tempVector.push_back(node);
				if (node.id == id) {
					break;
				}
			}

			for (const auto& node : tempVector) {
				pq.push(node);
			}	
			reheapDown(index);
		}else {
			elements[count].numberGuest = 1;
			elements[count].id = id;
			elements[count].order = first++;
			elements[count].orderQueue.push(item);
			idToIndex[id] = count;
			pq.push(elements[count]);
			count++;
			reheapUp(count-1);
		}
	}
	void remove(int num) {
		if (count == 0) return;
		int n = num;
		if (n > count) n = count;
		vector<HeapNode> tempVector;
		for (int i = 0; i < n; i++) {
			HeapNode node = pq.top();
			pq.pop();
			int index = idToIndex[node.id];
			for (int j = 0; j < num;j++) {
				node.numberGuest--;
				cout<<node.orderQueue.front()<<"-"<<node.id<<"\n";
				node.orderQueue.pop();
				if (node.numberGuest == 0) break;
			}
			if (node.numberGuest > 0) {
				node.order = first++;	
				elements[index] = node;
				reheapUp(index);
				tempVector.push_back(node);
			} else {
				idToIndex.erase(node.id);
				elements[index] = elements[--count];
				elements[count] = HeapNode();
				if (count == 0) break;
				idToIndex[elements[index].id] = index;
				reheapUp(index);
				reheapDown(index);
			}
		}
		for (const auto& node : tempVector) {
			pq.push(node);
		}

	}
	
	void preOrder (int index,const int num) {
		if (index >= count) return;
		queue<int> q = elements[index].orderQueue;
		stack<int> s;
		int i = 0;
		while (!q.empty()) {
			
			s.push(q.front());
			q.pop();
			
		}
		while (!s.empty()) {
			if (i == num) break;
			cout<<elements[index].id<<"-"<<s.top()<<"\n";
			s.pop();
			i++;
		}

		preOrder(2*index+1,num);
		preOrder(2*index+2,num);
	}
	void setCapacity(int maxsize) {
		HeapNode* newElements = new HeapNode[maxsize];
		delete[] elements;
		elements = newElements;
		
	}
	void reheapUp(int position) {
		while (position > 0) {
			int parent = (position - 1) / 2;
			if (elements[position].numberGuest < elements[parent].numberGuest) {
				HeapNode temp = elements[position];
				elements[position] = elements[parent];
				elements[parent] = temp;
				idToIndex[elements[position].id] = position;
				idToIndex[elements[parent].id] = parent;
				position = parent;
			} else if (elements[position].numberGuest == elements[parent].numberGuest) {
				if (elements[position].order < elements[parent].order) {
					HeapNode temp = elements[position];
					elements[position] = elements[parent];
					elements[parent] = temp;
					idToIndex[elements[position].id] = position;
					idToIndex[elements[parent].id] = parent;
					position = parent;
			} else {
				break;
			}
		} else {
			break;
		}
	}
	}
	void reheapDown(int position) {
		int child = 2 * position + 1;
		while (child < count) {
			int rightChild = child + 1;
			if (rightChild < count && elements[rightChild].numberGuest < elements[child].numberGuest) {
				child = rightChild;
			} else if (rightChild < count && elements[rightChild].numberGuest == elements[child].numberGuest) {
				if (elements[rightChild].order < elements[child].order) {
					child = rightChild;
				}
			}
			if (elements[position].numberGuest > elements[child].numberGuest) {
				HeapNode temp = elements[position];
				elements[position] = elements[child];
				elements[child] = temp;
				idToIndex[elements[position].id] = position;
				idToIndex[elements[child].id] = child;
				position = child;
				child = 2 * position + 1;
			} else if (elements[position].numberGuest == elements[child].numberGuest) {
				if (elements[position].order > elements[child].order) {
					HeapNode temp = elements[position];
					elements[position] = elements[child];
					elements[child] = temp;
					idToIndex[elements[position].id] = position;
					idToIndex[elements[child].id] = child;
					position = child;
					child = 2 * position + 1;
				} else {
					break;
				}
			} else {
				break;
			}
		}
	
	}
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
			removeEle(order[0].first,order[0].second,this->root);
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
			root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
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
		
		if (rightBalance <= 0) {
			root = rotateLeft(root);
			root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
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
		
		HuffNode* left = root->left();
		HuffNode* right = root->right();
		int balance = left->Level() - right->Level();
		
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
		
		root->setLeft(balanceTree(left,count,rotate));

		root->setLevel(max(root->left()->Level(),root->right()->Level()) + 1);
		
		if (rotate) return root;
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
	void printInOrder(HuffNode* node) {
		if (!node) {
			return;
		}
		printInOrder(node->left());
		if (node->isLeaf()) {
			cout<<static_cast<LeafNode*>(node)->val()<<"\n";
		} else
		cout<<node->weight()<<"\n";
		printInOrder(node->right());
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
	for (unsigned int i = 0; i < gojo.size(); i++) {
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

    vector<int> left_subtree, right_subtree;

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
		tree->removeNum(y);
		order.clear();
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
	int count = 0;
	
	while (treeArray.size() > 1) {
        HuffTree* left = treeArray.top();
        treeArray.pop();
	
        HuffTree* right = treeArray.top();
        treeArray.pop();
		
        HuffTree* node =new HuffTree(left, right,++count);
		node->root()->setOrder(count);
        treeArray.push(node);
		delete left;
		delete right;
    }
	huffmanTree = treeArray.top();
	treeArray.pop();
	
	if (huffmanTree->root()->isLeaf()) {
		result = 0;
		return false;
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
	}
	return true;
}
void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;
	int result = 0;
	HuffTree* lastCus = NULL;
	HuffTree* huffmanTree = NULL;
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
			sukuna.setCapacity(MAXSIZE);

    	}
        else if(str == "LAPSE") 
        {
            ss >> name;
			
			if (LAPSE(huffmanTree,name,result)) {
				deleteTree(lastCus);
				lastCus = huffmanTree;
				int ID = result % MAXSIZE + 1;

				if (result % 2 == 1) {
					gojo[ID]->add(result);
				} else {
					sukuna.push(result,ID);
				}
				
			} 
			

    	} else if (str == "KOKUSEN") {
			KOKUSEN(gojo);
		} else if (str == "KEITEIKEN") {
			ss >> num;
			int count = stoi(num);
			sukuna.remove(count);
		} else if (str == "HAND") {
			lastCus->printInOrder(lastCus->root());
		} else if (str == "LIMITLESS") {
			ss >> num;
			int number = stoi(num);
			if (number > MAXSIZE) continue;
			if (gojo[number]->sizeOf() == 0) {
				continue;
			}
			gojo[number]->print(gojo[number]->getRoot());
		} else {	
			ss >> num;
			int x = stoi(num);
			sukuna.preOrder(0,x);
		}
	}
	deleteVector(gojo);
	deleteTree(lastCus);
	return;
}