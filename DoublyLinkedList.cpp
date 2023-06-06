#include "DoublyLinkedList.h"
#include "Node.h"
#include <iostream>
using namespace std;
DoublyLinkedList::DoublyLinkedList() {
    this -> head = nullptr;
    this -> tail = nullptr;
    this -> size = 0;
}

DoublyLinkedList::~DoublyLinkedList() = default;

void DoublyLinkedList::addBeginning(int value) {    //adds given value to the head of list
    Node* node = new Node();
    node -> value = value;
    node -> next = head;
    if(head != nullptr) head -> prev = node;
    if(tail == nullptr) tail = node;
    head = node;
    node -> prev = nullptr;
    size++;
}

void DoublyLinkedList::addEnd(int value, int weight) {        //adds given value to tail of list
    Node* node = new Node();
    node -> value = value;
    node -> weight = weight;
    node -> next = nullptr;
    if(tail != nullptr) {
        tail -> next = node;
        node -> prev = tail;
    }
    if(tail == nullptr) head = node;
    tail = node;
    size++;
}

void DoublyLinkedList::addDesired(int value, int position) {    //adds given value at desired position in list
    if(position <= size && position >= 0){
        Node* node = new Node();
        node -> value = value;
        Node* searching = head;
        for(int i = 0; i < position - 1; i++){
            searching = searching -> next;
        }
        if(position == 0){              //case if value added on beginning of list
            if(head != nullptr){
                head -> prev = node;
                node -> next = head;
            } else tail = node;
            head = node;
        }
        else{                           //other cases
            node -> prev = searching;
            node -> next = searching -> next;
            if(position < size) searching -> next -> prev = node;
            else tail = node;
            searching -> next = node;
        }
        size++;
    }
}

void DoublyLinkedList::deleteBeginning() {  //deletes value at beginning of list
    if(size == 0) return;
    if(head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
    }else{
        head = head -> next;
        delete head -> prev;
        head -> prev = nullptr;
    }
    size--;
}

void DoublyLinkedList::deleteEnd() {   //deletes value at end of list
    if(size == 0) return;
    if(head == tail){
        delete tail;
        head = nullptr;
        tail = nullptr;
    }else{
        tail = tail -> prev;
        delete tail -> next;
        tail -> next = nullptr;
    }
    size--;
}

void DoublyLinkedList::deleteDesired(int value) {    //deletes desired value from list if value exists
    Node* searching = head;
    for(int i = 0; i < size; i++){
        if(searching == nullptr) return;
        if(searching -> value == value) break;
        searching = searching -> next;
    }
    if(searching == nullptr) return;
    if(searching -> prev != nullptr) searching -> prev -> next = searching -> next;
    else head = searching -> next;                                                  //edge case if given value is head of list
    if(searching -> next != nullptr) searching -> next -> prev = searching -> prev;
    else tail = searching -> prev;                                                  //edge case if given value is tail of list
    delete searching;
    size--;
}

Node* DoublyLinkedList::search(int number) {    //searches given value of list object in list and returns the object
    Node* searching = head;
    for(int i = 0; i < size; i++){
        if(searching -> value == number) return searching;
        searching = searching -> next;
    }
    return nullptr;
}

void DoublyLinkedList::printList() {    //prints list in console
    if(size > 0){
        Node* printing = head;
        while(printing != nullptr){
            cout << printing -> value << ":" << printing -> weight<< "|";
            printing = printing -> next;
        }
        cout << "\nHead: " << head -> value << "\nTail: "<< tail -> value << "\nSize: " << size << "\n";
    }
}