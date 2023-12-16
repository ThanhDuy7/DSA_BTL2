#include "main.h"

int MAXSIZE;
//---------------------------------------------------------------------------------------------------------
										/*HAM LAPSE*/
// Huffman tree node abstract base class
class HuffNode {
public:
	int height = -1;
public:
	virtual ~HuffNode() {} // Base destructor
	virtual int weight() = 0; // Return frequency
	virtual bool isLeaf() = 0; // Determine type
	virtual char val() = 0;
	virtual HuffNode* &left() = 0;
	virtual HuffNode* &right() = 0;
	virtual void setLeft(HuffNode* &a) = 0;
	virtual void setRight(HuffNode* &b) = 0;
};

// Leaf node subclass
class LeafNode : public HuffNode {
private:
	char it; // Value
	int wgt; // Weight
	HuffNode* lc; // Left child
	HuffNode* rc; // Right child
public:
	LeafNode(const char& val, int freq) // Constructor
	{
		it = val; wgt = freq;
		height = 0;
		lc = NULL;
		rc = NULL;
	}
	int weight() { return wgt; }
	char val() { return it; }
	bool isLeaf() { return true; }
	HuffNode*& left() {
		return lc;
	}
	HuffNode*& right() {
		return rc;
	}
	void setLeft(HuffNode* &a) { return; }
	void setRight(HuffNode* &b) { return; }
};
// Internal node subclass
class IntlNode : public HuffNode {
private:
	HuffNode* lc; // Left child
	HuffNode* rc; // Right child
	int wgt; // Subtree weight
public:
	IntlNode(HuffNode*& l, HuffNode*& r)
	{
		wgt = l->weight() + r->weight(); lc = l; rc = r;
		height = l->height > r->height ? l->height + 1 : r->height + 1;
	}
	int weight() { return wgt; }
	bool isLeaf() { return false; }
	HuffNode* &left() { return lc; }
	void setLeft(HuffNode* &b)
	{
		lc = b;
	}
	HuffNode* &right() { return rc; }
	void setRight(HuffNode* &b)
	{
		rc = b;
	}
	char val() {
		char t = '\0';
		return t;
	}
};

// HuffTree is a template of two parameters: the element
// type being coded and a comparator for two such elements.
static int order_hufftree;
class HuffTree {
private:
	HuffNode* Root; // Tree root
	int order;
public:
	HuffTree(char& val, int freq) // Leaf constructor
	{
		Root = new LeafNode(val, freq);
		order = 0;
	}
	// Internal node constructor
	HuffTree(HuffTree* &l, HuffTree* &r)
	{
		HuffNode* left_root = l->root();
		HuffNode* right_root = r->root();
		Root = new IntlNode(left_root, right_root);
		order = order_hufftree;
		++order_hufftree;
	}
	~HuffTree() {} // Destructor
	HuffNode* root() { return Root; } // Get root
	int weight() { return Root->weight(); } // Root weight
	int get_order() { return order; }  // order

	void print(const std::string& prefix, HuffNode* node, bool isLeft) {
		if (node != nullptr) {
			std::cout << prefix << (isLeft ? "|-- " : "\\-- ") << node->weight();
			if (node->isLeaf()) {
				std::cout << static_cast<LeafNode*>(node)->val();
			}
			std::cout << endl;
			if (!node->isLeaf()) {
				print(prefix + (isLeft ? "|   " : "    "), static_cast<IntlNode*>(node)->left(), true);
				print(prefix + (isLeft ? "|   " : "    "), static_cast<IntlNode*>(node)->right(), false);
			}
		}
	}
	void printHuffmanTree() {
		if (!Root) {
			std::cout << "The tree is empty." << std::endl;
			return;
		}

		print("", Root, false);
	}

	HuffNode* rotateLeft(HuffNode* root) {
		HuffNode* tmp = root->right();
		HuffNode* temp = tmp->left();
		tmp->setLeft(root);
		root->setRight(temp);
		return tmp;
	}

	HuffNode* rotateRight(HuffNode* root) {
		HuffNode* tmp = root->left();
		HuffNode* temp = tmp->right();
		tmp->setRight(root);
		root->setLeft(temp);
		return tmp;
	}

	bool implement(HuffNode*& root, int& count) {
		if (root->isLeaf()) return false;
		else if (root->left()->height == root->right()->height) return false;
		else if (count == 0) return false;
		else if (root->left()->height - root->right()->height == 1) return false;
		else if (root->left()->height - root->right()->height == -1) return false;
		else {
			if (root->left()->height - root->right()->height > 1) {
				if (root->left()->left()->height - root->left()->right()->height == 0) {
					root = rotateRight(root);
					--count;
					root->right()->height = root->right()->left()->height > root->right()->right()->height ? root->right()->left()->height + 1 : root->right()->right()->height + 1;
					root->height = root->left()->height > root->right()->height ? root->left()->height + 1 : root->right()->height + 1;
				}
				else if (root->left()->left()->height - root->left()->right()->height >= 1) {				//LL
					root = rotateRight(root);
					--count;
					root->right()->height = root->right()->left()->height > root->right()->right()->height ? root->right()->left()->height + 1 : root->right()->right()->height + 1;
					root->height = root->left()->height > root->right()->height ? root->left()->height + 1 : root->right()->height + 1;
				}
				else {																						//LR
					HuffNode* left = root->left();
					HuffNode* newl = rotateLeft(left);
					root->setLeft(newl);
					root = rotateRight(root);
					--count;
					root->right()->height = root->right()->left()->height > root->right()->right()->height ? root->right()->left()->height + 1 : root->right()->right()->height + 1;
					root->left()->height = root->left()->left()->height > root->left()->right()->height ? root->left()->left()->height + 1 : root->left()->right()->height + 1;
					root->height = root->left()->height > root->right()->height ? root->left()->height + 1 : root->right()->height + 1;
				}
			}
			else {
				if (root->right()->left()->height - root->right()->right()->height == 0) {
					root = rotateLeft(root);
					--count;
					root->left()->height = root->left()->left()->height > root->left()->right()->height ? root->left()->left()->height + 1 : root->left()->right()->height + 1;
					root->height = root->left()->height > root->right()->height ? root->left()->height + 1 : root->right()->height + 1;
				}
				else if (root->right()->left()->height - root->right()->right()->height <= -1) {			//RR
					root = rotateLeft(root);
					--count;
					root->left()->height = root->left()->left()->height > root->left()->right()->height ? root->left()->left()->height + 1 : root->left()->right()->height + 1;
					root->height = root->left()->height > root->right()->height ? root->left()->height + 1 : root->right()->height + 1;
				}
				else {																						//RL
					HuffNode* right = root->right();
					HuffNode* newr = rotateRight(right);
					root->setRight(newr);
					root = rotateLeft(root);
					--count;
					root->left()->height = root->left()->left()->height > root->left()->right()->height ? root->left()->left()->height + 1 : root->left()->right()->height + 1;
					root->right()->height = root->right()->left()->height > root->right()->right()->height ? root->right()->left()->height + 1 : root->right()->right()->height + 1;
					root->height = root->left()->height > root->right()->height ? root->left()->height + 1 : root->right()->height + 1;
				}
			}
		}
		return true;
	}

	void update_height(HuffNode*& root) {
		root->height = root->left()->height > root->right()->height ? root->left()->height + 1 : root->right()->height + 1;
	}

	bool balance(HuffNode*& root, int& count) {
		if (root == NULL) return false;
		else if (root->isLeaf()) return false;
		else if (count == 0) return false;
		else {
			if (implement(root, count)) return true;
			if (balance(root->left(), count)) {
				update_height(root);
				return true;
			}
			if (balance(root->right(), count)) {
				update_height(root);
				return true;
			}
			return false;
		}
	}

	void balanceHuff() {
		int count = 3;
		while (balance(Root, count)) {
			continue;
		}
	}

};

// Build a Huffman tree from a collection of frequencies
// Build a Huffman tree from a collection of frequencies
class minTreecomp {
public:
	bool operator() (HuffTree*& p1, HuffTree*& p2) {
		if (p1->weight() > p2->weight()) return true;
		else if (p1->weight() == p2->weight()) {
			if (p1->root()->isLeaf() && p2->root()->isLeaf()) {
				if (isupper(p1->root()->val()) && islower(p2->root()->val())) {
					return true;
				}
				else if (islower(p1->root()->val()) && isupper(p2->root()->val())) {
					return false;
				}
				else {
					return p1->root()->val() > p2->root()->val();
				}
			}
			else {
				return p1->get_order() > p2->get_order();
			}
		}
		else return false;
	}
};

HuffTree* khachhang = NULL;													// khachhang den nha hang gan day nhat phuc vu cho ham HAND

HuffTree*
buildHuff(HuffTree** &TreeArray, int count) {
	priority_queue<HuffTree*, vector<HuffTree*>, minTreecomp> forest;
	for (int i = 0; i < count; i++) {
		forest.push(TreeArray[i]);
	}
	HuffTree* temp1, * temp2, * temp3 = NULL;
	if (forest.size() == 1) {
		temp3 = forest.top();
		forest.pop();
	}
	while (forest.size() > 1) {
		temp1 = forest.top(); // Pull first two trees
		forest.pop();
		temp2 = forest.top(); // off the list
		forest.pop();
		temp3 = new HuffTree(temp1, temp2);
		//TODO balance hufftree before put it into forest
		temp3->balanceHuff();
		//-------------------
		forest.push(temp3); // Put the new tree back on list
		delete temp1;
		delete temp2;
	}
	return temp3;
}

char caesar(char ch, int freq) {
	if (isupper(ch)) {
		// Apply Caesar cipher transformation for uppercase letters
		return static_cast<char>((ch - 'A' + freq) % 26 + 'A');
	}
	// Check if the character is a lowercase letter
	else if (islower(ch)) {
		// Apply Caesar cipher transformation for lowercase letters
		return static_cast<char>((ch - 'a' + freq) % 26 + 'a');
	}
	// Return unchanged character for non-alphabetic characters
	return ch;
}

void traversal(HuffNode*& root, string& t, map<char, string>& table) {
	if (root == NULL) return;
	else if (root->isLeaf()) {
		table.insert({ root->val(),t });
		return;
	}
	else {
		string phu = t;
		t += '0';
		HuffNode* tmp = root->left();
		traversal(tmp, t, table);

		t = phu;
		t += '1';
		tmp = root->right();
		traversal(tmp, t, table);
	}
}
string binary(HuffTree*& tree, string name) {
	map<char, string> table;
	string t = "";
	HuffNode* tmp = tree->root();
	if (!tmp->isLeaf()) traversal(tmp, t, table);
	else {
		t += '0';
		table.insert({ tmp->val(), t });
	}
	string bi = "";
	for (unsigned int i = 0; i < name.length(); i++) {
		bi += table[name[i]];
	}
	string X = "";
	for (unsigned int i = bi.length() - 1; i > (bi.length() - 11); --i) {
		if (i < 0) break;
		X += bi[i];
	}
	return X;
}

int binaryToDecimal(const string& binaryString) {
	int decimalNumber = 0;
	int binaryLength = binaryString.length();

	for (int i = 0; i < binaryLength; ++i) {
		char binaryChar = binaryString[i];

		int binaryDigit = binaryChar - '0';

		decimalNumber += binaryDigit * pow(2, binaryLength - 1 - i);
	}

	return decimalNumber;
}

int LAPSE(string name) {
	map<char, int> hash;
	for (unsigned int i = 0; i < name.length(); i++) {
		if (hash.find(name[i]) == hash.end()) {
			hash.insert({ name[i], 1 });
		}
		else {
			hash[name[i]] += 1;
		}
	}
	string name_after_caesar = "";
	for (unsigned int i = 0; i < name.length(); i++) {
		name_after_caesar += caesar(name[i], hash[name[i]]);
	}
	map<char, int> hash_after_caesar;
	for (auto it = hash.begin(); it != hash.end(); it++) {
		char tmp = it->first;
		int tmp_freq = it->second;
		tmp = caesar(tmp, tmp_freq);
		if (hash_after_caesar.find(tmp) == hash_after_caesar.end()) hash_after_caesar.insert({ tmp,tmp_freq });
		else hash_after_caesar[tmp] += tmp_freq;
	}
	// after encrypt caesar, buid HUFFMAN tree
	HuffTree** TreeArray = new HuffTree * [hash_after_caesar.size()];
	int index = 0;
	order_hufftree = 1;
	for (auto it = hash_after_caesar.begin(); it != hash_after_caesar.end(); it++) {  //create an array to store sub hufftree that is still a leafnode 
		char tmp = it->first;
		int freq = it->second;
		TreeArray[index] = new HuffTree(tmp, freq);
		++index;
		//cout << it->first << " " << it->second << endl;
	}

	khachhang = buildHuff(TreeArray, index);    // build hufftree hoan chinh
	//khachhang->printHuffmanTree();
	string bin = binary(khachhang, name_after_caesar);
	int RESULT = binaryToDecimal(bin);
	order_hufftree = 1;
	//cout << RESULT << endl;
	delete[]TreeArray;
	TreeArray = NULL;
	return RESULT;
}

void clearTreeNode(HuffNode*& root) {
	if (root == NULL) return;
	else {
		HuffNode* l = root->left();
		clearTreeNode(l);
		HuffNode* r = root->right();
		clearTreeNode(r);
		delete root;
		root = NULL;
	}
}

void clear(HuffTree*& tree) {
	if (tree != NULL) {
		HuffNode* root = tree->root();
		clearTreeNode(root);
		delete tree;
		tree = NULL;
	}
}
//---------------------------------------------------------------------------------------------------------
										/*HAM HAND*/
void in_order(HuffNode* root) {
	if (root->isLeaf()) {
		cout << root->val() << "\n";
	}
	else {
		in_order(root->left());
		cout << root->weight() << "\n";
		in_order(root->right());
	}
}
void HAND(HuffTree* &khachhang) {
	in_order(khachhang->root());
}
//---------------------------------------------------------------------------------------------------------
					/*CLASS XAY DUNG NHA HANG CUA GOJO - VO LUONG KHONG XU*/
class GOJO {
public:
	class Node;
	class quanlidanhsach;
public:
	Node** khuvuc;
	set<int> quanli;                        // cau truc nay chi chua ID nhung khu vuc co khach hang
	quanlidanhsach* order_khach;			// cau truc nay giup xu li FIFO result cua tung khach trong tung khu vuc
public:
	GOJO() {
		khuvuc = new Node * [MAXSIZE + 1];  
		order_khach = new quanlidanhsach[MAXSIZE + 1]; //vector order_khach dung cach nay de tao ra mang co kich thuoc la MAXSIZE + 1
		for (int i =  0; i <= MAXSIZE; i++) {
			khuvuc[i] = NULL;
		}
	}

	~GOJO() {
		for (int i = 0; i <= MAXSIZE; i++) {
			if (khuvuc[i] != NULL) {
				clear(khuvuc[i]);
			}
			// chua thu hoi memory leak cua tung BST
		}
		delete[]khuvuc;
		delete[]order_khach;
	}
	void clear(Node*& root) {
		if (root == NULL) return;
		else {
			clear(root->left);
			clear(root->right);
			delete root;
			root = NULL;
		}
	}

	void insert(Node* &root, const int& RESULT,const int& id) {
		if (root == NULL) {
			root = new Node(RESULT, id, NULL, NULL);
			quanli.insert(id);
		}
		else if (RESULT >= root->result) {
			insert(root->right, RESULT, id);
		}
		else {
			insert(root->left, RESULT, id);
		}
	}

	void deleteNode(Node* &root, int RESULT) {
		if (root == NULL) return;
		else if (RESULT < root->result) {
			deleteNode(root->left, RESULT);
		}
		else if (RESULT > root->result) {
			deleteNode(root->right, RESULT);
		}
		else {
			if (root->left == NULL && root->right == NULL) {
				delete root;
				root = NULL;
			}
			else if (root->left == NULL) {
				Node* tmp = root;
				root = root->right;
				delete tmp;
				tmp = NULL;
			}
			else if (root->right == NULL) {
				Node* tmp = root;
				root = root->left;
				delete tmp;
				tmp = NULL;
			}
			else {
				Node* tmp = root->right;
				while (tmp->left != NULL) {
					tmp = tmp->left;
				}
				root->result = tmp->result;
				deleteNode(root->right, tmp->result);
			}
		}
	}
									// duoc goi khi dung ham LAPSE trong nha hang GOJO
	void nhankhach(int RESULT) {
		int id_khu_vuc = RESULT % MAXSIZE + 1;
		insert(khuvuc[id_khu_vuc], RESULT, id_khu_vuc);
		order_khach[id_khu_vuc].list_khachhang.push(RESULT);
		
	}
	//---------------------------------------------------
								/*dem so lan hoan vi*/
	// Function to precompute the
	// factorial of 1 to N
	void calculateFact(int fact[], int N)
	{
		fact[0] = 1;
		for (long long int i = 1; i < N; i++) {
			fact[i] = fact[i - 1] * i;
		}
	}

	int nCr(int fact[], int N, int R)
	{
		if (R > N)
			return 0;

		// nCr= fact(n)/(fact(r)*fact(n-r))
		int res = fact[N] / fact[R];
		res /= fact[N - R];

		return res;
	}
	
	int countWays(vector<int>& arr, int fact[]) {
		// Store the size of the array
		int N = arr.size();

		// Base case
		if (N <= 2) {
			return 1;
		}

		// Store the elements of the
		// left subtree of BST
		vector<int> leftSubTree;

		// Store the elements of the
		// right subtree of BST
		vector<int> rightSubTree;

		// Store the root node
		int root = arr[0];

		for (int i = 1; i < N; i++) {

			// Push all the elements
			// of the left subtree
			if (arr[i] < root) {
				leftSubTree.push_back(
					arr[i]);
			}

			// Push all the elements
			// of the right subtree
			else {
				rightSubTree.push_back(
					arr[i]);
			}
		}

		// Store the size of leftSubTree
		int N1 = leftSubTree.size();

		// Store the size of rightSubTree
		//int N2 = rightSubTree.size();

		// Recurrence relation
		int countLeft
			= countWays(leftSubTree,
				fact);
		int countRight
			= countWays(rightSubTree,
				fact);

		return nCr(fact, N - 1, N1)
			* countLeft * countRight;
	}

	void pre_order(Node* root, vector<int>& arr) {
		if (root == NULL) return;
		else {
			arr.push_back(root->result);
			pre_order(root->left, arr);
			pre_order(root->right, arr);
		}
	}

	int count_hoan_vi(Node* root) {
		vector<int> arr;
		pre_order(root, arr);

		// Store the size of arr
		int N = arr.size();

		// Store the factorial up to N
		int* fact = new int[N];

		// Precompute the factorial up to N
		calculateFact(fact, N);

		int Y = countWays(arr, fact);

		delete[]fact;

		return Y;
	}
	//----------------------------------------------------
									//duoc goi khi dung ham KOKUSEN
	void KOKUSEN() {
		set<int>::iterator it;
		for (it = quanli.begin(); it != quanli.end(); ++it) {		//cho vong lap duyet het cac khu vuc co ton tai khach hang
			unsigned int Y = count_hoan_vi(khuvuc[*it]) % MAXSIZE;
			if (Y >= order_khach[*it].list_khachhang.size()) {						//duoi het khach trong khu vuc
				while (!order_khach[*it].list_khachhang.empty()) {
					deleteNode(khuvuc[*it], order_khach[*it].list_khachhang.front());
					order_khach[*it].list_khachhang.pop();
				}
			}
			else {													//duoi Y khach trong khu vuc
				for (unsigned int i = 0; i < Y; i++) {
					deleteNode(khuvuc[*it], order_khach[*it].list_khachhang.front());
					order_khach[*it].list_khachhang.pop();
				}
			}
		}
	}
	//-----------------------------------------------------
	
	void print(Node* root) {
		if (root == NULL) return;
		else {
			print(root->left);
			cout << root->result << endl;
			print(root->right);
		}
	}
	//duoc goi khi dung ham LIMITLESS
	void LIMITLESS(int NUM) {
		print(khuvuc[NUM]);
	}
	//-----------------------------------------------------
public:
	class Node {
	public:
		int ID;
		int result;
		Node* left;
		Node* right;
	public:
		Node(int RESULT, int id, Node* pleft, Node* pright) {
			this->result = RESULT;
			this->left = pleft;
			this->right = pright;
			this->ID = id;
		}
		Node() {
			this->result = 0;
			this->left = NULL;
			this->right = NULL;
			this->ID = 0;
		}
	};

	class quanlidanhsach {
	public:
		queue<int> list_khachhang;
	};
};
// ---------------------------------------------------------------------------------------------------------
					/*CLASS XAY DUNG NHA HANG CUA SUKUNA - PHUC MA NGU CHUA*/

class SUKUNA {
public:
	class Node;
	class nodecomp {
	public:
		bool operator() (Node*& p1, Node*& p2) {
			if (p1->soluong > p2->soluong) return true;
			else if (p1->soluong == p2->soluong) {
				if (p1->thu_tu_su_dung < p2->thu_tu_su_dung) return true;
			}
			return false;
		}
	};
private:
	Node** khuvuc;
	int capacity;
	int count;
	
public:
	SUKUNA() {
		khuvuc = new Node*[MAXSIZE];
		capacity = MAXSIZE;
		count = 0;
	}
	~SUKUNA() {
		for (int i = 0; i < count; i++) {
			delete khuvuc[i];
		}
		delete[]khuvuc;
		count = 0;
	}

	void update_thu_tu_su_dung_khu_vuc() {
		for (int i = 0; i < count; i++) {
			++khuvuc[i]->thu_tu_su_dung;
		}
	}

	void swap(Node* &first, Node* &second) {
		Node* tmp = first;
		first = second;
		second = tmp;
	}

	void reheapUp(int index) {
		if (index == 0 || index >= count) return;
		int parent = (index - 1) / 2;
		if (khuvuc[parent]->soluong > khuvuc[index]->soluong) {
			swap(khuvuc[parent], khuvuc[index]);
			reheapUp(parent);
		}
		else if (khuvuc[parent]->soluong == khuvuc[index]->soluong) {
			if (khuvuc[parent]->thu_tu_su_dung < khuvuc[index]->thu_tu_su_dung) {
				swap(khuvuc[parent], khuvuc[index]);
				reheapUp(parent);
			}
		}
	}

	void reheapDown(int index) {
		int left = index * 2 + 1;
		if (left >= count) return;

		int right = index * 2 + 2;
		if (right >= count) {
			if (khuvuc[left]->soluong < khuvuc[index]->soluong) {
				swap(khuvuc[left], khuvuc[index]);
				reheapDown(left);
			}
			else if (khuvuc[left]->soluong == khuvuc[index]->soluong) {
				if (khuvuc[left]->thu_tu_su_dung > khuvuc[index]->thu_tu_su_dung) {
					swap(khuvuc[left], khuvuc[index]);
					reheapDown(left);
				}
			}
		}
		else {
			int child = 0;
			if (khuvuc[left]->soluong < khuvuc[right]->soluong) child = left;
			else if (khuvuc[left]->soluong > khuvuc[right]->soluong) child = right;
			else {
				if (khuvuc[left]->thu_tu_su_dung > khuvuc[right]->thu_tu_su_dung) child = left;
				else child = right;
			}
			if (khuvuc[child]->soluong < khuvuc[index]->soluong) {
				swap(khuvuc[child], khuvuc[index]);
				reheapDown(child);
			}
			else if (khuvuc[child]->soluong == khuvuc[index]->soluong) {
				if (khuvuc[child]->thu_tu_su_dung > khuvuc[index]->thu_tu_su_dung) {
					swap(khuvuc[child], khuvuc[index]);
					reheapDown(child);
				}
			}
		}
	}

	void buildheap() {
		for (int i = count / 2; i >= 0; --i) {
			reheapDown(i);
		}
	}

	void remove(int index) {
		if (index >= count) return;
		Node* tmp = khuvuc[index];
		khuvuc[index] = khuvuc[count - 1];
		khuvuc[count - 1] = NULL;
		--count;
		delete tmp; tmp = NULL;
		buildheap();
	}

	/*khi LAPSE duoc goi thi tro toi nhankhach*/
	void nhankhach(int result) {
		int id_khuvuc = result % MAXSIZE + 1;
		if (count == 0) {
			khuvuc[0] = new Node(result, id_khuvuc);
			++count;
		}
		else {
			int index = -1;
			for (int i = 0; i < count; i++) {
				if (khuvuc[i]->ID == id_khuvuc) {
					index = i;
					break;
				}
			}
			if (index != -1) {
				khuvuc[index]->add_list(result);
				update_thu_tu_su_dung_khu_vuc();
			}
			else {
				khuvuc[count] = new Node(result, id_khuvuc);
				update_thu_tu_su_dung_khu_vuc();
				++count;
			}
			buildheap();
		}
	}

											/*Khi KEITEIKEN duoc goi*/
	void KEITEIKEN(int NUM) {
		if (count <= 0 || NUM <= 0) return;
		priority_queue<Node*, vector<Node*>, nodecomp> order;
		if (NUM >= count) {							//khi NUM >= so luong khu vuc 
			for (int i = 0; i < count; i++) {
				order.push(khuvuc[i]);
			}
			while (!order.empty()) {
				Node* tmp = order.top();
				order.pop();
				tmp->duoi_khach(NUM);
				update_thu_tu_su_dung_khu_vuc();
				if (tmp->soluong == 0) {
					int index = tmp - khuvuc[0];
					remove(index);    //su dung ham remove thi tu dong buildheap
				}
				else {
					buildheap();
				}
			}
		}
		else {						//khi NUM < so luong khu vuc
			for (int i = 0; i < count; i++) {					// dau tien ta phai dua het cac node khu vuc vao priority_queue.
				order.push(khuvuc[i]);
			}
			for (int i = 0; i < NUM; i++) {						// do tinh chat cua priority_queue la dua ra element be nhat nhu ta quy dinh nen ta chi can lay ra NUM lan la thoa yeu cau de bai
				Node* tmp = order.top();
				order.pop();
				tmp->duoi_khach(NUM);
				update_thu_tu_su_dung_khu_vuc();
				if (tmp->soluong == 0) {
					int index = tmp - khuvuc[0];
					remove(index);    //su dung ham remove thi tu dong buildheap
				}
				else {
					buildheap();
				}
			}
		}
	}
	/*khi CLEAVE duoc goi*/
	void print(Node* tmp, int& NUM) {
		if (tmp->soluong == 0) return;
		queue<int> temp = tmp->khachhang;
		stack<int> list;
		while (!temp.empty()) {
			list.push(temp.front());
			temp.pop();
		}
		int n = NUM >= tmp->soluong ? tmp->soluong : NUM ;
		for (int i = 0; i < n; i++) {
			cout << tmp->ID << "-" << list.top() << "\n";
			list.pop();
		}
	}
	void print_pre_order(int index, int& NUM) {
		if (index >= count || index < 0) return;
		else {
			print(khuvuc[index], NUM);
			print_pre_order(index * 2 + 1, NUM);
			print_pre_order(index * 2 + 2, NUM);
		}
	}
	void CLEAVE(int NUM) {
		print_pre_order(0, NUM);
		
	}

public:
	class Node{
	public:
		int ID = 0;
		int soluong = 0;
		int thu_tu_vao_heap = 0;
		int thu_tu_su_dung = 0;							//khi nhan khach hoac xoa khach tu khu vuc nay thi thu_tu_su_dung se cho = 0
		queue<int> khachhang;
	public:
		Node(int result, int id) {
			ID = id;
			khachhang.push(result);
			soluong += 1;
			thu_tu_su_dung = 0;							//khi nhan khach co nghia la khu vuc nay da duoc su dung de nhan khach nen cho = 0
		}
		void add_list(int result) {
			soluong += 1;
			khachhang.push(result);
			thu_tu_su_dung = 0;							//khi nhan khach co nghia la khu vuc nay da duoc su dung de nhan khach nen cho = 0
		}
		void duoi_khach(int NUM) {						// duoi NUM khach hang tai khu vuc nay
			//int i = 0;
			if (NUM >= soluong) {
				while(!khachhang.empty()) {
					cout << khachhang.front() << "-" << ID << "\n";
					khachhang.pop();
				}
				soluong = 0;
				thu_tu_su_dung = 0;
			}
			else {
				for (int i = 0; i < NUM; i++) {
					cout << khachhang.front() << "-" << ID << "\n";
					khachhang.pop();
				}
				soluong -= NUM;
				thu_tu_su_dung = 0;
			}
		}
	};
};

//---------------------------------------------------------------------------------------------------------
					/* kiem tra xem ten cua khach co it nhat 3 ky tu khac nhau khong*/
bool DongYNhanKhach(string name) {  
	vector<char> checkName;
	bool flag = false;
	bool name_dat_yeu_cau = false;
	checkName.push_back(name[0]);
	// dau tien la ktra ten khach hang co du toi thieu 3 ky tu tro len hay khong
	// thuat toan la tao ra mot vector char va push back ki tu dau tien trong ten khach hang
	//sau do cho vao for chay tu ki tu second den ki tu final trong ten khach
	//cho tung ki tu vao vong for nho hon chay tu ki tu dau tien trong vector den ki tu cuoi cua vector, neu ton tai ki nao trong vector trung voi ki tu hien tai trong name thi break vong for nho ben trong
	// vong for lon chay cho den khi vector co 3 ki tu khac nhau thi dat yeu cau va break vong for lon
	for (unsigned int i = 1; i < name.length(); i++) {
		flag = true;
		for (unsigned int j = 0; j < checkName.size(); j++) {
			if (name[i] == checkName[j]) {
				flag = false;
				break;
			}
		}
		if (flag) checkName.push_back(name[i]);
		if (checkName.size() >= 3) {
			name_dat_yeu_cau = true;
			break;
		}
	}
	return name_dat_yeu_cau;
}     
//---------------------------------------------------------------------------------------------------------------
									/* THUC THI QUA TRINH DIEU HANH NHA HANG*/

void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;

	GOJO* G = NULL;						

	SUKUNA* S = NULL;

	
	while (ss >> str) {
		if (str == "MAXSIZE") {
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
			G = new GOJO();					/*NHA HANG GOJO MO CUA*/
			S = new SUKUNA();				/*NHA HANG SUKUNA MO CUA*/
			//cout << maxsize << endl;
		}
		else if (str == "LAPSE") {
			ss >> name;
			if (DongYNhanKhach(name)) {
				clear(khachhang);
				int RESULT = LAPSE(name);
				//cout << RESULT << endl;
				if (RESULT % 2 != 0) G->nhankhach(RESULT);
				else S->nhankhach(RESULT);
				//cout << "LAPSE " << name << endl;
			}
		}
		else if (str == "KOKUSEN") {
			G->KOKUSEN();
			//cout << "KOKUSEN " << endl;
		}
		else if (str == "KEITEIKEN") {
			ss >> num;
			S->KEITEIKEN(stoi(num));
			//cout << "KEITEIKEN " << num << endl;
		}
		else if (str == "HAND") {
			if(khachhang != NULL)
			HAND(khachhang);
			//cout << "HAND " << endl;
		}
		else if (str == "LIMITLESS") {
			ss >> num;
			G->LIMITLESS(stoi(num));
			//cout << "LIMITLESS " << num << endl;
		}
		else if (str == "CLEAVE") {
			ss >> num;
			S->CLEAVE(stoi(num));
			//cout << "CLEAVE " << num << endl;
		}
	}

	if(G!= NULL) delete G;
	if(S != NULL) delete S;
	if(khachhang != NULL) clear(khachhang);
}