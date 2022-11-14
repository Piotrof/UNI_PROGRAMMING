#include <iostream>
#include <cstring>

using namespace std;


struct Node{
    char* name;
    double cgpe;
    struct Node* next;
};

struct Node* head = new Node();

bool insert(char* name, double cgpe);
bool remove(char* name);
void print();

int main(){
    
    insert("John Smith", 3.89);
    insert("Sam Johnson", 4.59);
    print();
    remove("John Smith");
    print();

    return 0;
}

bool insert(char* name, double cgpe){

    if(head->name == NULL)
    {
        head->name = name;
        head->cgpe = cgpe;
        return true;
    }

    struct Node* new_node = new Node();

    struct Node* current = new Node();

    current = head;

    new_node->name = name;
    new_node->cgpe = cgpe;

    while(current->next != NULL)
    {
        if(strcmp(name, current->name) == 0)
        {
            cout << "This person is already in the list\n";
            delete current;
            return false;
        }

        current = current->next;
    }

    if(strcmp(name, current->name) == 0)
    {
        cout << "This person is already in the list\n";
        return false;
    }

    current = head;
    struct Node* previous = new Node();

    while(current->next != NULL)
    {
        if(strcmp(name, current->name) < 0)
        {
            if(previous->next == NULL)
            {
                new_node->next = head;
                return true;
            }
            else
            {
                previous->next = new_node;
                new_node->next = current;
                return true;
            }
        }

        previous = current;
        current = current->next;
    }

    if(current->next == NULL)
    {
        current->next = new_node;
        new_node->next = NULL;
    }
    return true;
}

bool remove(char* name){

    struct Node* current = head;
    struct Node* previous = new Node();

    while(current->next != NULL)
    {
        if(strcmp(name, current->name) == 0)
        {   
            if(current->next == NULL)
            {
                previous->next = NULL;
                delete current;
                return true;
            }
            else
            {
                previous->next = current->next;
                delete current;
                return true; 
            }
        }

        previous = current;
        current = current->next;
    }

    return true;
}

void print(){

    struct Node* current = head;

    while(current->next != NULL)
    {
        cout << "Student's name: " << current->name << ", student's CGPE: " << current->cgpe << "\n";

        current = current->next;
    }

    if(current->name != NULL)
    {
        cout << "Student's name: " << current->name << ", student's CGPE: " << current->cgpe << "\n";
    }

    delete current;
}   