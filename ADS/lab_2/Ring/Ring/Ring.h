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

	Ring<Key>& operator=(Ring<Key>& other_obj);
	bool operator==(Ring<Key>& other_obj);
	bool operator!=(Ring<Key>& other_obj);

	bool add(Key key);
	bool insert(Key key, Key prev_key);

	bool remove(Key key);
	bool remove_all(Key key);
	
	void print();
};

//class methods for the Ring class
template<typename Key>
Ring<Key>::Ring(Ring& other_obj) {

	Node* curr = this->head;


}

template<typename Key>
Ring<Key>& Ring<Key>::operator=(Ring<Key>& other_obj) {

	if (!this->head || !other_obj.head) return; 

	Node* curr = this->head;
	Node* curr_other = other_obj.head;

	do {
		Node* temp = curr->next;
		delete curr;
		curr = temp;
	} while (curr->next != this->head);

	delete this->head;

	do {
		this->add(curr_other->key);

		curr_other = curr_other->next;
	} while (curr_other->next != other_obj.head);
}

template<typename Key>
bool Ring<Key>::operator==(Ring<Key>& other_obj) {

	if (!this->head || !other_obj.head) return false;

	Node* curr = this->head;
	Node* curr_other = other_obj.head;

	do {

		if (curr->key != curr_other->key)
		{
			return false;
		}

		curr = curr->next;
		curr_other = curr_other->next;
	} while (curr->next != this->head);

	return true;
}

template<typename Key>
bool Ring<Key>::operator!=(Ring<Key>& other_obj) {
	
	if (!this->head || !other_obj.head) return false;

	if (this == other_obj)
	{
		return true;
	}
	else
	{
		return false;
	}
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
bool Ring<Key>::insert(Key key, Key prev_key) {

	if (!this->head) return false;

	Node* curr = this->head;

	do {
		if (curr->prev->key == prev_key)
		{
			curr->prev->next = allocate_node(key);
			curr->prev->next->prev = curr->prev;
			curr->prev->next->next = curr;
			return true;
		}

		curr = curr->next;
	} while (curr->next != this->head);

	return false;
}

template<typename Key>
bool Ring<Key>::remove(Key key) {
	
	if (!this->head) return false;

	Node* curr = this->head;

	do {
		if (curr->key == key)
		{
			curr->prev->next = curr->next;
			delete curr;
			return true;
		}

		curr = curr->next;
	} while (curr->next != this->head);

	return false;
}

template<typename Key>
bool Ring<Key>::remove_all(Key key) {

	if (!this->head) return false;

	Node* curr = this->head;
	bool is_removed = false;

	do {
		if (curr->key == key)
		{
			curr->prev->next = curr->next;
			delete curr;
			is_removed = true;
		}

		curr = curr->next;
	} while (curr->next != this->head);

	return is_removed;
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
void split(Ring<Key>& source, int step, int dir, Ring<Key>&res_1, Ring<Key>&res_2) {

}

#endif // !_RING_H_
