#pragma once
#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

using namespace std;

//class declaration
template<typename Key, typename Info>
class Sequence {
private:
    struct Node {
        Key key;
        Info info;
        Node* next;
    };

    Node* head;
    Node* tail;

    Node* allocate_node(Key key, Info info) {
        Node* new_node = new Node{ key, info, nullptr };

        return new_node;
    };

public:
    
    /**
     * \brief a default constructor.
     * 
     */
    Sequence();

    /**
     * \brief a default destructor.
     * 
     */
    ~Sequence() = default;

    /**
     * \brief a copy constructor.
     * 
     * \param other_object - a reference to a Sequence class object which contents will be copied.
     */
    Sequence(const Sequence<Key, Info>& other_object);


    /**
     * \brief an overloaded copy operator.
     * 
     * \param other_object - a reference to a Sequence class object which contents will be copied.
     * \return - a reference to the newly created Sequence class object.
     */
    Sequence<Key, Info>& operator=(const Sequence<Key, Info>& other_object);

    /**
     * \brief an overloaded addition operator.
     * 
     * \param other_object - a reference to a Sequence class object which contents will be copied.
     * \return a reference to the newly created Sequence class object.
     */
    Sequence<Key, Info>& operator+(const Sequence<Key, Info>& other_object);

    /**
     * \brief an overloaded boolean comparison operator.
     * 
     * \param rhs - a reference to a Sequence class object which will be compared against.
     * \return true if the Sequences match, false if the sequences don't match.
     */
    bool operator==(const Sequence<Key, Info>& rhs);

    /**
     * \brief an overloaded boolean comparison operator.
     * 
     * \param rhs - a reference to a Sequence class object which will be compared against.
     * \return false if the sequences match, true if the sequences don't match.
     */
    bool operator!=(const Sequence<Key, Info>& rhs);


    /**
     * \brief a function which adds a new element to the sequence.
     * 
     * \param key - the key of the newly added element.
     * \param info - the info of the newly added element.
     */
    void add(Key key, Info info);

    /**
     * \brief a function which pushes an element to the back of the sequence.
     * 
     * \param key - the key of the element.
     * \param info - the info of the element.
     */
    void push_back(const Key& key, const Info& info);

    /**
     * \brief a function which pushes an element to the front of the sequence.
     * 
     * \param key - the key of the element.
     * \param info - the info of the element.
     */
    void push_front(const Key& key, const Info& info);

    /**
     * \brief a function which removes all elements with a given key from the sequence.
     * 
     * \param key - a key which should be removed from the sequence.
     */
    void remove_all(const Key& key); 

    /**
     * \brief a function which removes the n-th element with a given key.
     * 
     * \param key - a key which should be removed from the sequence.
     * \param occ - the number specifying which occurence of the key should be removed from the sequence.
     */
    void remove(const Key& key, int occ); 

    /**
     * \brief a function which searches the sequence for an element with a given key.
     * 
     * \param key - a key which will be searched for in the sequence.
     * \return true if an element with the given key is found in the sequence, false if such an element is not found.
     */
    bool find_element(const Key& key);

    /**
     * \brief a function which returns the number of times a given key is contained withing the sequence.
     * 
     * \param key - a key which will be searched for in the sequence.
     * \return the number of times a given key is contained withtin the sequence.
     */
    int occurence(const Key& key); 

    /**
     * \brief a fucntion which inserts a new element into the middle of a sequence.
     * 
     * \param new_key - the Key of the newly created element.
     * \param new_info - the Info of the newly created element.
     * \param prev_key - the Key of the element after which we want to insert a new element.
     * \return true if an element is inserted successfully, false of an element cannot be created.
     */
    bool insert(Key new_key, Info new_info, const Key& prev_key);

    /**
     * \brief a function which prints all elements of a sequence.
     * 
     */
    void print() const;


    /**
     * \brief a getter which gets the Key parameter of the i-th element of a sequence.
     * 
     * \return the Key of the i-th element of a sequence.
     */
    Key get_key(int i) const; 

    /**
     * \brief a getter which gets the Info parameter of the i-th element of a sequence.
     * 
     * \return the Info of the i-th element of a sequence.
     */
    Info get_info(int i) const; 
};

//constructor
template<typename Key, typename Info>
Sequence<Key, Info>::Sequence() {
    this->head = nullptr;
    this->tail = nullptr;
};

//copy constructor
template<typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& other_object) {

    Node* current = this->head;
    Node* tail = this->tail;

    do {
        current = current->next;

        this->head;
        this->head = current;
    } while (current != tail->next);

    current = other_object.head;
    tail = other_object.tail;

    do {
        this->add(current->key, current->info);

        current = current->next;
    } while (current != tail->next);
};


//operators
template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& other_object) {

    if (this != other_object)
    {
        Node* current = this->head;
        Node* tail = this->tail;

        do {
            current = current->next;

            this->head;
            this->head = current;
        } while (current != tail->next);

        current = other_object.head;
        tail = other_object.tail;

        do {
            this->add(current->key, current->info);

            current = current->next;
        } while (current != tail->next);
    }
};

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator+(const Sequence<Key, Info>& other_object) {

    Node* current = other_object.head;
    Node* tail = other_object.tail;

    do {
        this->add(current->key, current->info);

        current = current->next;
    } while (current != tail->next);
};

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info>& rhs) {

    Node* current = this->head;
    Node* current_rhs = rhs.head;

    bool is_same = true;

    do {
        if (current->key != current_rhs->key || current->info != current_rhs->info)
        {
            is_same = false;
            break;
        }

        current = current->next;
        current_rhs = current_rhs->next;

    } while (current != this->tail->next);

    if (current != this->tail || current_rhs != rhs.tail)
    {
        is_same = false;
    }

    return is_same;
};

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator!=(const Sequence<Key, Info>& rhs) {

    if (this == rhs)
    {
        return true;
    }
    else
    {
        return false;
    }

};


//other methods
template<typename Key, typename Info>
void Sequence<Key, Info>::add(Key key, Info info) {

    if (this->head == nullptr)
    {
        this->head = allocate_node(key, info);
        this->head->next = this->head;
        this->tail = this->head;
    }
    else if (this->head == this->tail)
    {
        Node* new_node = allocate_node(key, info);
        this->head->next = new_node;
        new_node->next = this->head;
        this->tail = new_node;
    }
    else
    {
        Node* new_node = allocate_node(key, info);
        this->tail->next = new_node;
        new_node->next = this->head;
        this->tail = new_node;
    }
};

template<typename Key, typename Info>
void Sequence<Key, Info>::push_back(const Key& key, const Info& info) {

    Node* current = this->head;
    Node* tail = this->tail;
    Node* prev = this->tail;

    do {
        if (current->key == key && current->info == info)
        {
            prev->next = current->next;
            current->next = head;
            tail->next = current;
            this->tail = current;
            return;
        }

        current = current->next;
        prev = prev->next;
    } while (current != tail->next);
};

template<typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key& key, const Info& info) {

    Node* current = this->head;
    Node* tail = this->tail;
    Node* prev = this->tail;

    do {
        if (current->key == key && current->info == info)
        {
            if (current == this->head)
            {
            }
            else if (current == this->tail)
            {
                this->head = current;
                this->tail = prev;
            }
            else
            {
                prev->next = current->next;
                this->tail->next = current;
                current->next = this->head;
                this->head = current;
            }
            return;
        }

        current = current->next;
        prev = prev->next;
    } while (current != tail->next);
};

template<typename Key, typename Info>
void Sequence<Key, Info>::remove_all(const Key& key) {

    Node* current = this->head;
    Node* tail = this->tail;
    Node* prev = this->tail;

    do {
        if (current->key == key)
        {
            if (current == this->head)
            {
                prev->next = current->next;
                this->head = prev;
                delete current;
            }
            else if (current == this->tail)
            {
                prev->next = current->next;
                this->tail = prev;
                delete current;
            }
            else
            {
                prev->next = current->next;
                delete current;
            }
        }

        current = current->next;
        prev = prev->next;
    } while (current != tail->next);
};

template<typename Key, typename Info>
void Sequence<Key, Info>::remove(const Key& key, int occ) {

    if (occ <= 0)
    {
        cout << "occ number has to be greater than 0.\n";
        return;
    }

    Node* current = this->head;
    Node* tail = this->tail;
    Node* prev = this->tail;

    int occ_no = 0;

    do {
        if (current->key == key)
        {
            occ_no++;
            if (occ_no == occ)
            {
                if (current == this->head)
                {
                    prev->next = current->next;
                    this->head = prev;
                    delete current;
                    return;
                }
                else if (current == this->tail)
                {
                    prev->next = current->next;
                    this->tail = prev;
                    delete current;
                    return;
                }
                else
                {
                    prev->next = current->next;
                    delete current;
                    return;
                }
            }
        }

        current = current->next;
        prev = prev->next;
    } while (current != tail->next);
};

template<typename Key, typename Info>
bool Sequence<Key, Info>::find_element(const Key& key) {

    Node* current = this->head;
    Node* tail = this->tail;

    do {
        if (current->key == key)
        {
            return true;
        }
        
        current = current->next;
    } while (current != tail->next);

    return false;
};

template<typename Key, typename Info>
int Sequence<Key, Info>::occurence(const Key& key) {

    int occ = 0;

    Node* current = this->head;
    Node* tail = this->tail;

    do {
        if (current->key == key)
        {
            occ++;
        }

        current = current->next;
    } while (current != tail->next);

    return occ;
};

template<typename Key, typename Info>
bool Sequence<Key, Info>::insert(Key new_key, Info new_info, const Key& prev_key) {

    Node* current = this->head;
    Node* tail = this->tail;
    Node* prev = this->tail;

    if (this->head == nullptr)
    {
        this->head = allocate_node(new_key, new_info);
        this->head->next = this->head;
        this->tail = this->head;
        return true;
    }

    do {
        if (prev->key == prev_key)
        {
            if (prev == this->tail)
            {
                Node* new_node = allocate_node(new_key, new_info);
                prev->next = new_node;
                new_node->next = this->head;
                this->tail = new_node;
                return true;
            }
            else
            {
                Node* new_node = allocate_node(new_key, new_info);
                prev->next = new_node;
                new_node->next = current;
                return true;
            }
        }

        current = current->next;
        prev = prev->next;
    } while (current != tail->next);

    return false;
};

template<typename Key, typename Info>
void Sequence<Key, Info>::print() const {

    Node* current = this->head;

    if (this->head == nullptr)
    {
        return;
    }

    int i = 1;

    do {
        cout << "El. no. " << i << " Key: " << current->key << " Info: " << current->info << "\n";
        i++;
        current = current->next;
    } while (current != this->tail->next);
};


template<typename Key, typename Info>
Key Sequence<Key, Info>::get_key(int i) const {

    Node* current = this->head;
    int steps = 0;

    while (steps < i)
    {
        current = current->next;
        steps++;
    }

    return current->key;
};

template<typename Key, typename Info>
Info Sequence<Key, Info>::get_info(int i) const {

    Node* current = this->head;
    int steps = 0;

    while (steps < i)
    {
        current = current->next;
        steps++;
    }

    return current->info;
};


//external split function
/**
 * \brief a function which splits a sequence into two new ones using parameters provided by the user.
 * 
 * \param source - a reference to an object of the Sequence class which will be split.
 * \param result_1 - a reference to a result object of the Sequence class.
 * \param len_1 - the lenght of the first result object.
 * \param step_1 - the lenght of the splitting step for the first object.
 * \param result_2 - a reference to a result object of the Sequence class.
 * \param len_2 - the lenght of the second result object.
 * \param step_2 - the of the splitting step for the first object.
 */
template<typename Key, typename Info>
void split(const Sequence<Key, Info>& source,
    Sequence<Key, Info>& result_1, int len_1, int step_1,
    Sequence<Key, Info>& result_2, int len_2, int step_2) {

    if (len_1 <= 0 || len_2 <= 0 || step_1 <= 0 || step_2 <= 0)
    {
        cout << "desired sequence lengths and step lengths must be greater than 0.\n";
        return;
    }

    int iterator = 0;

    int curr_len_1 = 0, curr_len_2 = 0;

    cout << "begin split\n";

    while (curr_len_1 < len_1 || curr_len_2 < len_2)
    {   
        if (curr_len_1 < len_1)
        {
            for (int i = 0; i < step_1; i++)
            {   
                result_1.add(source.get_key(iterator), source.get_info(iterator));
                iterator++;
                curr_len_1++;
            }
        }

        if (curr_len_2 <= len_2)
        {
            for (int i = 0; i < step_2; i++)
            {
                result_2.add(source.get_key(iterator), source.get_info(iterator));
                iterator++;
                curr_len_2++;
            }
        }
    }
};

#endif // !_SEQUENCE_H_
