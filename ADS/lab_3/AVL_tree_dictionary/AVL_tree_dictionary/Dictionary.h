#pragma once

#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <iostream>
#include "Node.h"

using namespace std;

class Dictionary {

	Node* root;

public:
	Dictionary() { root = NULL; };
	int max(int a, int b);
	int get_height(Node* node);
	Node* insert_internal(Node* rnode, int key, string word);
	void insert(int key, string word);
	Node* right_rotate(Node* y);
	Node* left_rotate(Node* y);
	int get_balance(Node* node);
	void pre_order(Node* node);
	void post_order(Node* node);
	void in_order(Node* node);
};

int Dictionary::max(int a, int b) {
	return (a > b) ? a : b;
}

int Dictionary::get_height(Node* node) {
	
	if (node == NULL) return 0;
	else return node->height;
}

int Dictionary::get_balance(Node* node) {

	if (node == NULL) return 0;
	else return (get_height(node->left) - get_height(node->right));
}

Node* Dictionary::right_rotate(Node* y) {

	Node* x = y->left;
	Node* xr = x->right;

	x->right = y;
	y->left = xr;


	y->height = max(get_height(y->left), get_height(y->right)) + 1;
	x->height = max(get_height(x->left), get_height(x->right)) + 1;

	return x;
}

Node* Dictionary::left_rotate(Node* y) {

	Node* x = y->right;
	Node* xr = x->left;

	x->left = y;
	y->right = xr;

	y->height = max(get_height(y->left), get_height(y->right)) + 1;
	x->height = max(get_height(x->left), get_height(x->right)) + 1;

	return x;
}

Node* Dictionary::insert_internal(Node* rnode, int key, string word) {
	
	if (rnode == NULL) return new Node(key, word);

	if (key < rnode->key)
	{
		rnode->left = insert_internal(rnode->left, key, word);
	}
	else if (key > rnode->key)
	{
		rnode->right = insert_internal(rnode->right, key, word);
	}
	else return rnode;

	rnode->height = 1 + max(get_height(rnode->left), get_height(rnode->right));

	int balance = get_balance(rnode);

	if (balance > 1 && key < rnode->left->key)
	{
		return right_rotate(rnode);
	}

	if (balance<-1 && key>rnode->right->key)
	{
		return left_rotate(rnode);
	}

	if (balance > 1 && key > rnode->left->key)
	{
		rnode->left = left_rotate(rnode->left);
		return right_rotate(rnode);
	}

	if (balance < -1 && key < rnode->right->key)
	{
		rnode->right = right_rotate(rnode->right);
		return left_rotate(rnode);
	}

	return rnode;
}

void Dictionary::insert(int key, string word) {

	root = insert_internal(root, key, word);
}

void Dictionary::pre_order(Node* node) {
	
	if (node)
	{
		node->print();
		pre_order(node->left);
		pre_order(node->right);
	}
}

void Dictionary::post_order(Node* node) {

	if (node)
	{
		post_order(node->left);
		post_order(node->right);
		node->print();
	}
}

void Dictionary::in_order(Node* node) {
	
	if (node)
	{
		in_order(node->left);
		node->print();
		in_order(node->right);
	}
}

#endif // _DICTIONARY_H_
