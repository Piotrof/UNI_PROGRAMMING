#pragma once
#ifndef _RING_H_
#define _RING_H_

using namespace std;

template<typename Key>
class Ring {
private:
	struct Node {

		Key key;
		Node* prev;
		Node* next;
	};

	Node* allocate_node(Key key) {
		Node* new_node = new Node{ key, nullptr, nullptr };

		return new_node;
	};

	Node* head;

public:
	Ring() = default;
	Ring(Ring& other_obj);
	~Ring() = default;

	bool add(Key key);

	void print();
};

//class methods for the Ring class
template<typename Key>
Ring<Key>::Ring(Ring& other_obj) {

	Node* curr = this->head;


}

template<typename Key>
bool Ring<Key>::add(Key key) {

	Node* curr = this->head->prev;
	curr->next = allocate_node(key);
	Node* temp = curr;
	curr = curr->next;
	curr->next = this->head;
	curr->prev = temp;
	this->head->prev = curr;
}

template<typename Key>
void Ring<Key>::print() {

	if (!this->head) return;

	Node* curr = this->head;
	int i = 0;

	cout << "Printing Ring.\n";
	do {
		cout << "El. no. " << i << ": " << curr->key << ".\n";

		curr = curr->next;
	} while (curr->next != this->head);
}

//external split function
template<typename Key>
void split(Ring<Key>& source, int step, int len, Ring<Key>&res_1, Ring<Key>&res_2) {

}

#endif // !_RING_H_
