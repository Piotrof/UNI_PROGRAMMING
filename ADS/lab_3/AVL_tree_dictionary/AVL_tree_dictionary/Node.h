#pragma once

#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <iomanip>

using namespace std;

class Node {

	int key;
	string word;
	Node* left;
	Node* right;
	int height;

public:
	Node();
	Node(int key, string word);
	void print() const;

	friend class Dictionary;
};

Node::Node() {

	left = NULL;
	right = NULL;
	height = 1;
	word = "";
	key = 1;
}

Node::Node(int key, string word) {
	this->key = key;
	this->word = word;
	left = NULL;
	right = NULL;
	height = 1;
}

void Node::print() const {
	cout << key << " " << word << endl;
}

#endif // !_NODE_H_
