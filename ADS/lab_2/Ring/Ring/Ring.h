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

	Node head;
public:
	Ring() = default;
	Ring(Ring& other_obj);
	~Ring() = default;
};

//class methods for the Ring class
template<typename Key>
Ring<Key>::Ring(Ring& other_obj) {

}

//external split function
template<typename Key>
void split(Ring<Key>& source, int step, int len, Ring<Key>&res_1, Ring<Key>&res_2) {

}

#endif // !_RING_H_
