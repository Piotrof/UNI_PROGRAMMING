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
	Ring() { this->head = nullptr; };
	Ring(Ring& other_obj);
	~Ring() = default;

	Ring<Key>& operator=(Ring<Key>& other_obj);
	bool operator==(Ring<Key>& other_obj);
	bool operator!=(Ring<Key>& other_obj);

	bool add(Key key);
	bool add_before(Key key);
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
	if (this->head == nullptr)
	{
		this->head = allocate_node(key);
		this->head->next = this->head;
		this->head->prev = this->head;
		return true;
	}
	else if (this->head->next == this->head)
	{
		Node* temp = allocate_node(key);
		this->head->next = temp;
		this->head->prev = temp;
		temp->next = this->head;
		temp->prev = this->head;
		return true;
	}
	else
	{
		Node* temp = this->head->prev;
		Node* new_node = allocate_node(key);
		temp->next = new_node;
		new_node->next = this->head;
		this->head->prev = new_node;
		new_node->prev = temp;
		return true;
	}

	return false;
}

template<typename Key>
bool Ring<Key>::add_before(Key key) {
	if (this->head == nullptr)
	{
		this->head = allocate_node(key);
		this->head->next = this->head;
		this->head->prev = this->head;
		return true;
	}
	else if (this->head->next == this->head)
	{
		Node* temp = allocate_node(key);
		this->head->next = temp;
		this->head->prev = temp;
		temp->next = this->head;
		temp->prev = this->head;
		return true;
	}
	else
	{
		Node* temp = this->head->next;
		Node* new_node = allocate_node(key);
		temp->prev = new_node;
		new_node->prev = this->head;
		this->head->next = new_node;
		new_node->next = temp;
		return true;
	}

	return false;
}

template<typename Key>
bool Ring<Key>::insert(Key key, Key prev_key) {

	if (this->head == nullptr) return false;

	Node* curr = this->head;
	Node* prev = curr->prev;

	do {
		if (prev->key == prev_key)
		{
			Node* new_node = allocate_node(key);
			new_node->prev = prev;
			new_node->next = curr;
			curr->prev = new_node;
			prev->next = new_node;
			return true;
		}

		prev = curr;
		curr = curr->next;
	} while (curr != this->head);

	return false;
}

template<typename Key>
bool Ring<Key>::remove(Key key) {
	
	if (!this->head) return false;

	Node* curr = this->head;

	do {
		if (curr->key == key)
		{
			if (curr == this->head)
			{
				Node* prev = curr->prev;
				prev->next = curr->next;
				head = curr->next;
				delete curr;
				head->prev = prev;
				return true;
			}
			else
			{
				Node* prev = curr->prev;
				prev->next = curr->next;
				Node* next = curr->next;
				delete curr;
				next->prev = prev;
				return true;
			}	
		}

		curr = curr->next;
	} while (curr != this->head);

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
	} while (curr != this->head);

	return is_removed;
}

template<typename Key>
Key Ring<Key>::traverse(int dir, int i) {

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
		cout << "El. no. " << i + 1<< ": " << curr->key << ".\n";

		curr = curr->next;
		i++;
	} while (curr != this->head);
}

//external split function
template<typename Key>
void split(Ring<Key>& source, int step_1, int dir_1, int len_1, Ring<Key>&res_1, int step_2, int dir_2, int len_2, Ring<Key>&res_2) {

	if (dir_1 != 1 && dir_1 != -1 && dir_2 != 1 && dir_2 != -1)
	{
		cout << "Incorrect value for variable dir_1 or dir_2. Set the dir variable to 1 to go clockwise, set the dir variable to -1 to go counter-clockwise.\n";
		return;
	}

	int curr_len_1 = 0, curr_len_2 = 0;
	int steps_taken_1 = 0, steps_taken_2 = 0;

	while (curr_len_1 < len_1 || curr_len_2 < len_2)
	{
		if (curr_len_1 < len_1)
		{
			if (dir_1 == 1)
			{
				for (int i = 0; i < step_1; i++)
				{
					res_1.add(source.traverse(dir_1,i + steps_taken_1));
				}
				steps_taken_1 += step_1;
				curr_len_1++;
			}
			else if (dir_1 == -1)
			{
				for (int i = 0; i < step_1; i++)
				{
					res_1.add(source.traverse(dir_1, i + steps_taken_1));
				}
				steps_taken_1 += step_1;
				curr_len_1++;
			}
		}

		if (curr_len_2 < len_2)
		{
			if (dir_2 == 1)
			{
				for (int i = 0; i < step_2; i++)
				{
					res_2.add(source.traverse(dir_2, i + steps_taken_2));
				}
				steps_taken_2 += step_2;
				curr_len_2++;
			}
			else if (dir_2 == -1)
			{
				for (int i = 0; i < step_2; i++)
				{
					res_2.add(source.traverse(dir_2, i + steps_taken_2));
				}
				steps_taken_2 += step_2;
				curr_len_2++;
			}
		}
	}
}

template<typename Key>
void split_corrected(Ring<Key>& source, int source_direction,int no_of_steps, Ring<Key>& res_1, int step_length_1, int dir_res_1, 
																			  Ring<Key>& res_2, int step_length_2, int dir_res_2) {

	if (source_direction != 1 && source_direction != -1)
	{
		cout << "source direction variable incorrect.\n";
		return;
	}

	if (dir_res_1 != 1 && dir_res_1 != -1)
	{
		cout << "res_1 direction variable incorrect.\n";
		return;
	}

	if (dir_res_2 != 1 && dir_res_2 != -1)
	{
		cout << "res_2 direction variable incorrect.\n";
		return;
	}
	
	int steps_taken = 0;
	int offset = 0;

	while (steps_taken < no_of_steps)
	{	
		for (int i = 0; i < step_length_1; i++)
		{
			if (dir_res_1 == 1)
			{
				res_1.add(source.traverse(source_direction, i + offset));
			}
			else
			{
				res_1.add_before(source.traverse(source_direction, i + offset));
			}
		}
		offset += step_length_1;

		for (int i = 0; i < step_length_2; i++)
		{
			if (dir_res_2 == 1)
			{
				res_2.add(source.traverse(source_direction, i + offset));
			}
			else
			{
				res_2.add_before(source.traverse(source_direction, i + offset));
			}	
		}
		offset += step_length_2;
		steps_taken++;
	}
}
#endif // !_RING_H_
	