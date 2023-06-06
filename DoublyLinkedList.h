#ifndef SDIZO_DOUBLYLINKEDLIST_H
#define SDIZO_DOUBLYLINKEDLIST_H
#include "Node.h"

class DoublyLinkedList{
private:
    Node* head;
    Node* tail;

public:
    int size;
    void addBeginning(int);
    void addEnd(int, int);
    void addDesired(int, int);
    void deleteBeginning();
    void deleteEnd();
    void deleteDesired(int);
    Node* search(int);
    void printList();
    DoublyLinkedList();
    ~DoublyLinkedList();
};

#endif //SDIZO_DOUBLYLINKEDLIST_H
