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
	
	Key traverse(int dir, int i);

	void print();
};

//class methods for the Ring class
template<typename Key>
Ring<Key>::Ring(Ring& other_obj) {

	if (!this->head || !other_obj.head) return;

	Node* curr = other_obj.head;
	
	do {
		this->allocate_node(curr->key);

		curr = curr->next;
	} while (curr->next != other_obj.head);
	
	return;
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
Key Ring<Key>::traverse(int dir, int i) {

	if (!this->head) return;

	Node* curr = this->head;

	if (dir == 1)
	{
		for (int j = 0; j < i; j++)
		{
			curr = curr->next;
		}
		return curr->key;
	}
	else if (dir == -1)
	{
		for (int j = 0; j < i; j++)
		{
			curr = curr->prev;
		}

		return curr->key;
	}
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
void split(Ring<Key>& source, int step_1, int dir_1, int len_1, Ring<Key>&res_1, int step_2, int dir_2, int len_2, Ring<Key>&res_2) {
	
	if (!source->head) return;

	if (dir_1 != 1 || dir_1 != -1 || dir_2 != 1 || dir_2 != -1)
	{
		cout << "Incorrect value for variable dir_1 or dir_2. Set the dir variable to 1 to go clockwise, set the dir variable to -1 to go counter-clockwise.\n";
		return;
	}

	int curr_len_1 = 0, curr_len_2 = 0;

	while (curr_len_1 < len_1 || curr_len_2 < len_2)
	{
		if (curr_len_1 < len_1)
		{
			if (dir_1 == 1)
			{
				for (int i = 0; i < step_1; i++)
				{
					res_1.add(source.traverse(dir_1, i));
				}
			}
			else if (dir_1 == -1)
			{
				for (int i = 0; i < step_1; i++)
				{
					res_1.add(source.traverse(dir_1, i));
				}
			}
		}

		if (curr_len_2 < len_2)
		{
			if (dir_2 == 1)
			{
				for (int i = 0; i < step_2; i++)
				{
					res_2.add(source.traverse(dir_2, i));
				}
			}
			else if (dir_2 == -1)
			{
				for (int i = 0; i < step_2; i++)
				{
					res_2.add(source.traverse(dir_2, i));
				}
			}
		}
	}
}

#endif // !_RING_H_
