#pragma once

#include <iostream>
#include <fstream>
#include<map>

using namespace std;

template <typename Key, typename Info>
class Dictionary {

private:
	struct Node {
		Key key;
		Info info;
		int height;
		Node* left;
		Node* right;

		Node() = default;

		Node(const Key& k, const Info& i) {
			key = k;
			info = i;
			left = nullptr;
			right = nullptr;
		}
	};

	Node* root;
	int size = 0;

	Node* copyNodes(Node* src) {
		if (!src) return nullptr;
		Node* n = new Node(src->key, src->info);
		n->left = copyNodes(src->left);
		n->right = copyNodes(src->right);

		size++;
		heightRepair(n);

		return n;
	}

	int height(Node* n) const {
		if (n) return n->height;
		else return 0;
	}

	int balanceFactorCalc(Node* n) {
		return height(n->right) - height(n->left);
	}

	Node* performBalance(Node* n) {
		if (!n) return NULL;
		heightRepair(n);

		if (balanceFactorCalc(n) == 2) {
			if (balanceFactorCalc(n->right) < 0) n->right = rotateRight(n->right);
			return rotateLeft(n);
		}

		if (balanceFactorCalc(n) == -2) {
			if (balanceFactorCalc(n->left) > 0) n->left = rotateLeft(n->left);
			return rotateRight(n);
		}
		return n; // no balancing needed
	}

	Node* rotateRight(Node* n) {
		if (n) return rotator(n, 'r');
		else return NULL;
	}

	Node* rotateLeft(Node* n) {
		if (n) return rotator(n, 'l');
		else return NULL;
	}

	Node* rotator(Node* n, char rotate) {

		Node* x = nullptr;

		if (rotate == 'r') {
			x = n->left;
			n->left = x->right;
			x->right = n;
		}
		else if (rotate == 'l') {
			x = n->right;
			n->right = x->left;
			x->left = n;
		}

		heightRepair(n);
		heightRepair(x);

		return x;
	}

	void heightRepair(Node* n) {
		int heightLeft = height(n->left);
		int heightRight = height(n->right);

		if (heightLeft > heightRight) n->height = 1 + heightLeft;
		else n->height = 1 + heightRight;
	}

	void cleanup(Node* n) {
		if (n) {
			cleanup(n->left);
			cleanup(n->right);
			delete n;
			size = 0;
		}
	}

	Node* exists(Node* n, const Key& k) const {
		if (!n)
			return NULL;
		if (n->key == k)
			return n;
		if (n->key < k)
			return exists(n->right, k);
		else if (n->key > k)
			return exists(n->left, k);
		else return NULL;
	}

	Node* remove(Node* n, const Key& k) {
		if (!n)
			return NULL;
		if (k < n->key)
			n->left = remove(n->left, k);
		else if (k > n->key)
			n->right = remove(n->right, k);
		else {
			Node* ln = n->left;
			Node* rn = n->right;
			delete n;

			if (!rn) return ln;

			Node* min = findMin(rn);
			min->right = removeMin(rn);
			min->left = ln;
			size--;
			return performBalance(min);
		}
		return performBalance(n);
	}

	Node* findMin(Node* n) {
		return n->left ? findMin(n->left) : n;
	}

	Node* removeMin(Node* n) {
		if (n->left == 0) return n->right;

		n->left = removeMin(n->left);

		return performBalance(n);
	}

	Node* insert(Node* n, const Key& k, const Info& i) {
		if (!n) {
			size++;
			return new Node(k, i);
		}
		if (k < n->key)
			n->left = insert(n->left, k, i);
		else
			if (k > n->key)
				n->right = insert(n->right, k, i);
			else {
				n->info = i;
				return n;
			}

		return performBalance(n);
	}

	void printInOrder(ostream& output) const {
		printInOrder(output, root);
	}

	void printInOrder(ostream& out, Node* n) const {
		if (!n) return;
		printInOrder(out, n->left);
		cout << "[" << n->key << "|" << n->info << "]  ";
		printInOrder(out, n->right);
	}

	void printInOrder(Node* n) const {
		if (!n) return;
		printInOrder(n->left);
		cout << "[" << n->key << "|" << n->info << "]  ";
		printInOrder(n->right);
	}

	void draw(Node* n, int step = 0, string mark = "T ") const {
		if (!n) {
			cout << indent(step) << "X";
			return;
		}

		draw(n->right, step + 8, "{r} ");
		cout << endl;

		cout << indent(step) << mark << "k: " << n->key << " i: " << n->info << endl;

		draw(n->left, step + 8, "{l} ");

		cout << endl << indent(step);
	}

	string indent(int indent) const {
		string out;
		for (auto i = 0; i < indent; i++) out += "  ";
		return out;
	}

	public: 
		Dictionary() {
			root = nullptr;
		}

		Dictionary(const Dictionary& src) {
			root = copyNodes(src.root);
		}

		~Dictionary() {
			cleanup(root);
		}

		void insert(const Key& k, const Info& i) {
			root = insert(root, k, i);
		}
		
		void remove(const Key& k) {
             root = remove(root, k); 
        }

		bool exists(const Key& k) const { 
			exists(this->root, k);
			return true;
		}

		void print() const {
			cout << "===Dictionary==" << endl;
			cout << "size: " << getSize() << " height: " << height(root) << endl;
			printInOrder(root);
			cout << endl;
		}

		void draw() const {
			draw(root);
		}

		int getSize() const
		{
			return size;
		}
};

Dictionary <string, int> counter(const string& filename) {

	ifstream file(filename);
	string word;
	map<std::string, int> cont;


	while (!file.eof())
	{
		file >> word;
		if (cont.find(word) == cont.end())
			cont[word] = 1;
		else ++cont[word];
	}

	Dictionary <string, int> dict;

	for (auto& element : cont)
		dict.insert(element.first, element.second);

	return dict;
}