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

		/**
		 * default constructor.
		 * 
		 */
		Node() = default;

		/**
		 * constructor with set parameters.
		 * 
		 * \param k
		 * \param i
		 */
		Node(const Key& k, const Info& i) {
			key = k;
			info = i;
			left = nullptr;
			right = nullptr;
		}
	};

	Node* root;
	int size = 0;

	/**
	 * a function used to copy nodes.
	 * 
	 * \param src pointer to the source node
	 * \return a pointer to the newly copied node
	 */
	Node* copyNodes(Node* src) {
		if (!src) return nullptr;
		Node* n = new Node(src->key, src->info);
		n->left = copyNodes(src->left);
		n->right = copyNodes(src->right);

		size++;
		heightRepair(n);

		return n;
	}

	/**
	 * a height getter.
	 * 
	 * \param n pointer to the node
	 * \return the height of node n
	 */
	int height(Node* n) const {
		if (n) return n->height;
		else return 0;
	}

	/**
	 * a function to calculate the balance of the node.
	 * 
	 * \param n a pointer to the node
	 * \return the balance factor of node n
	 */
	int balanceFactorCalc(Node* n) {
		return height(n->right) - height(n->left);
	}
	
	/**
	 * a function to perform the balancing of the tree.
	 * 
	 * \param n a pointer to the node to be baslanced
	 * \return a pointer to node n after the balancing is performed
	 */
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

	/**
	 * a function to perform a right-rotation.
	 * 
	 * \param n a pointer to the node to be rotated
	 * \return pointer to node n after rotation
	 */
	Node* rotateRight(Node* n) {
		if (n) return rotator(n, 'r');
		else return NULL;
	}

	/**
	 * a function to perform a left-rotation.
	 * 
	 * \param n a pointer to the node to be rotated
	 * \return pointer to node n after rotation
	 */
	Node* rotateLeft(Node* n) {
		if (n) return rotator(n, 'l');
		else return NULL;
	}

	/**
	 * a rotator function.
	 * 
	 * \param n a pointer to the node to be rotated
	 * \param rotate a symbol for the direction of the rotation r - right, l - left
	 * \return 
	 */
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

	/**
	 * a function to recalculate the height of a node.
	 * 
	 * \param n a pointer to the node which height should be recalculated
	 */
	void heightRepair(Node* n) {
		int heightLeft = height(n->left);
		int heightRight = height(n->right);

		if (heightLeft > heightRight) n->height = 1 + heightLeft;
		else n->height = 1 + heightRight;
	}

	/**
	 * a function for clearing a whole tree.
	 * 
	 * \param n
	 */
	void cleanup(Node* n) {
		if (n) {
			cleanup(n->left);
			cleanup(n->right);
			delete n;
			size = 0;
		}
	}

	/**
	 * a function for checkin if a node with a given key already exists within the tree.
	 * 
	 * \param n a pointer to the node
	 * \param k a reference to the key to be checked
	 * \return NULL if such a node does not exist
	 */
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

	/**
	 * a function for removing a node from the tree.
	 * 
	 * \param n a pointer to the node
	 * \param k a reference to a key which should be removed
	 */
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

	/**
	 * a function for finding the minimum of a branch.
	 * 
	 * \param n a pointer to a node
	 * \return 
	 */
	Node* findMin(Node* n) {
		return n->left ? findMin(n->left) : n;
	}

	/**
	 * a function for removing the minimum of a branch.
	 * 
	 * \param n a pointer to a node
	 * \return 
	 */
	Node* removeMin(Node* n) {
		if (n->left == 0) return n->right;

		n->left = removeMin(n->left);

		return performBalance(n);
	}

	/**
	 * a function for inserting a node into the tree.
	 * 
	 * \param n a pointer to a node 
	 * \param k a reference to the key of the node which is to be inserted
	 * \param i a reference to the info of the node which is to be inserted
	 * \return 
	 */
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

	/**
	 * a function for printing the tree in order to an output.
	 * 
	 * \param output
	 */
	void printInOrder(ostream& output) const {
		printInOrder(output, root);
	}

	/**
	 * the internal function for printing the tree in order to an output.
	 * 
	 * \param out
	 * \param n
	 */
	void printInOrder(ostream& out, Node* n) const {
		if (!n) return;
		printInOrder(out, n->left);
		cout << "[" << n->key << "|" << n->info << "]  ";
		printInOrder(out, n->right);
	}

	/**
	 * .
	 * 
	 * \param n
	 */
	void printInOrder(Node* n) const {
		if (!n) return;
		printInOrder(n->left);
		cout << "[" << n->key << "|" << n->info << "]  ";
		printInOrder(n->right);
	}

	/**
	 * a function to draw a graphical representation of the whole tree.
	 * 
	 * \param n a pointer to the root node
	 * \param step the number of the step
	 * \param mark a mark denoting the node T - root, {r} - right, {l} - left
	 */
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

	/**
	 * an automated indenter.
	 * 
	 * \param indent the number of indents which should be made
	 * \return 
	 */
	string indent(int indent) const {
		string out;
		for (auto i = 0; i < indent; i++) out += "  ";
		return out;
	}

	public:

		/**
		 * a default constructor.
		 * 
		 */
		Dictionary() {
			root = nullptr;
		}

		/**
		 * a copy constructor.
		 * 
		 * \param src a reference pointer to a source disctionary
		 */
		Dictionary(const Dictionary& src) {
			root = copyNodes(src.root);
		}

		/**
		 * a default destructor.
		 * 
		 */
		~Dictionary() {
			cleanup(root);
		}

		/**
		 * a function for adding a node.
		 * 
		 * \param k the key to be inserted
		 * \param i the info to be inserted
		 */
		void insert(const Key& k, const Info& i) {
			root = insert(root, k, i);
		}
		
		/**
		 * a function for removing a node.
		 * 
		 * \param k the key to be removed
		 */
		void remove(const Key& k) {
             root = remove(root, k); 
        }

		/**
		 * a function for checking if a node with the given tree exists within the tree.
		 * 
		 * \param k the key to be checked for
		 * \return 
		 */
		bool exists(const Key& k) const { 
			exists(this->root, k);
			return true;
		}

		/**
		 * a function for printing the contents of the tree.
		 * 
		 */
		void print() const {
			cout << "===Dictionary==" << endl;
			cout << "size: " << getSize() << " height: " << height(root) << endl;
			printInOrder(root);
			cout << endl;
		}

		/**
		 * a function for drawing a graphical representation of the tree.
		 * 
		 */
		void draw() const {
			draw(root);
		}

		/**
		 * a getter for the size of the Dictionary.
		 * 
		 * \return the size
		 */
		int getSize() const
		{
			return size;
		}
};

/**
 * an external function which inputs words from a text file into a Dictionary.
 * 
 * \param filename the name of the file to be processed
 * \return 
 */
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