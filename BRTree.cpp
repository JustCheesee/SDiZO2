#include "BRTree.h"
#include <iostream>
#include <string>
using namespace std;

BRTree::BRTree() {
    this -> root = nullptr;
    this -> watcher = new BRNode;
    this -> watcher -> color = true;
    this -> watcher -> key = -1;
}

BRTree::~BRTree() = default;

void BRTree::treeInsert(BRNode* node) {
    BRNode* y = nullptr;
    BRNode* x = root;
    while(x != nullptr){                          //insertion at nullptr in tree | while checking if child is lower/greater and moving accordingly
        y = x;
        if(node -> key < x -> key) x = x -> left;
        else x = x -> right;
    }
    node -> parent = y;                           //fixing pointers
    if(y == nullptr) root = node;
    else if(node -> key < y -> key) y -> left = node;
    else y -> right = node;
}

void BRTree::leftRotate(BRNode* node) {                //left rotation for RB - tree | fixing pointers
    BRNode* y = node -> right;
    node -> right = y -> left;
    if(y -> left != nullptr) y -> left -> parent = node;
    y -> parent = node -> parent;
    if(node -> parent == nullptr) root = y;
    else if(node == node -> parent -> left) node -> parent -> left = y;
    else node -> parent -> right = y;
    y -> left = node;
    node -> parent = y;
}

void BRTree::rightRotate(BRNode* node) {            //right rotation for RB - tree | fixing pointers
    BRNode* y = node -> parent;
    y -> left = node -> right;
    if(node -> right != nullptr) node -> right -> parent = y;
    node -> parent = y -> parent;
    if(y -> parent == nullptr) root = node;
    else if(y == y -> parent -> left) y -> parent -> left = node;
    else y -> parent -> right = node;
    node -> right = y;
    y -> parent = node;
}

void BRTree::BRinsert(BRNode* node) {
    treeInsert(node);
    node -> color = false;
    while(node != root && node -> parent -> color == false){   //fixing until parent color is other than child color
        if(node -> parent == node -> parent -> parent -> left){
            BRNode* uncle;
            if(node -> parent -> parent -> right != nullptr) uncle = node -> parent -> parent -> right; //check if uncle is a leaf
            else{
                uncle = new BRNode;
                uncle -> color = true;
            }
            if(uncle -> color == false){                    //case 1 uncle is red
                node -> parent -> color = true;
                uncle -> color = true;
                node -> parent -> parent -> color = false;
                node = node -> parent -> parent;
            }
            else if( node == node -> parent -> right){      //case 2 uncle is black | right side
                node = node -> parent;
                leftRotate(node);
                node -> parent -> color = true;
                node -> parent -> parent -> color = false;
                rightRotate(node -> parent);
            }
            else{                                           //case 3 uncle is black | left side
                node -> parent -> color = true;
                node -> parent -> parent -> color = false;
                rightRotate(node -> parent);
            }
        }
        else{
            BRNode* uncle;
            if(node -> parent -> parent -> left != nullptr) uncle = node -> parent -> parent -> left; //check if uncle is a leaf
            else{
                uncle = new BRNode;
                uncle -> color = true;
            }
            if(uncle -> color == false){                    //case 1 uncle is red
                node -> parent -> color = true;
                uncle -> color = true;
                node -> parent -> parent -> color = false;
                node = node -> parent -> parent;
            }
            else if( node == node -> parent -> left){       //case 2 uncle is black | left side
                rightRotate(node);
                node = node -> right;
                node -> parent -> color = true;
                node -> parent -> parent -> color = false;
                leftRotate(node -> parent -> parent);
            }
            else{                                           //case 3 uncle is black | right side
                node -> parent -> color = true;
                node -> parent -> parent -> color = false;
                leftRotate(node -> parent -> parent);
            }
        }
    }
    root -> color = true;
}

void BRTree::BRremove(BRNode* node) {
    BRNode* y;  //actually deleted node
    BRNode* x;  //son of y
    if(node -> left == nullptr || node -> right == nullptr)y = node;    //check if node has one or more sons
    else y = successor(node);                                           //set y to successor of node if node has > 1 sons

    if(y -> left != nullptr) x = y -> left;                             //setting x pointers
    else if(y -> right != nullptr) x = y -> right;
    else x = watcher;
    x -> parent = y -> parent;
    if(y -> parent == nullptr) root = x;
    else if(y == y -> parent -> left) y -> parent -> left = x;
    else y -> parent -> right = x;

    if(y != node){
        node -> key = y -> key;                               //case if y and node are not same pointer
        node -> vertex = y -> vertex;
    }
    if(y -> color == true) BRfixup(x);
    delete y;
    if(x == watcher && x != root){                                                  //deleting watcher pointers because project works on nullptr
        if(watcher -> parent -> right == x) watcher -> parent -> right = nullptr;
        if(watcher -> parent -> left == x) watcher -> parent -> left = nullptr;
    }
    if(x == watcher && x == root)root = nullptr;
}

void BRTree::BRfixup(BRNode* node) {
    while(node != root && node -> color == true){
        if(node == node -> parent -> left){                                    //case node is left son of his parent
            BRNode* w = node -> parent -> right;
            if(w -> color == false){                                            //case 1. brother of node is red
                w -> color = true;
                w -> parent -> color = false;
                leftRotate(node -> parent);
                w = node -> parent -> right;
            }
            if((w -> left == nullptr || w -> left -> color == true) && (w -> right == nullptr || w -> right -> color == true)){      //case 2. both children of brother of node are black
                w -> color = false;
                node = node -> parent;
            }
            else if(w -> right == nullptr || w -> right -> color == true){                               //case 3. one child of brother of node is black
                if(w -> left != nullptr)w -> left -> color = true;
                w -> color = false;
                rightRotate(w -> left);
                w = node -> parent -> right;
                w -> color = node -> parent -> color;
                node -> parent -> color = true;
                if(w -> right != nullptr) w -> right -> color = true;
                leftRotate(node -> parent);
                node = root;
            }
            else{                                                               //case 4. both children of brother of node are red
                w -> color = node -> parent -> color;
                node -> parent -> color = true;
                if(w -> right != nullptr) w -> right -> color = true;
                leftRotate(node -> parent);
                node = root;
            }
        }
        else{                                                                  //case node is right son of his parent
            BRNode* w = node -> parent -> left;
            if(w -> color == false){                                           //case 1. brother of node is red
                w -> color = true;
                w -> parent -> color = false;
                rightRotate(w);
                w = node -> parent -> left;
            }
            if((w -> left == nullptr || w -> left -> color == true) && (w -> right == nullptr || w -> right -> color == true)){    //case 2. both children of brother of node are black
                w -> color = false;
                node = node -> parent;
            }
            else if(w -> left == nullptr || w -> left -> color == true){                              //case 3. one child of brother of node is black
                if(w -> right != nullptr)w -> right -> color = true;
                w -> color = false;
                leftRotate(w);
                w = node -> parent -> left;
                w -> color = node -> parent -> color;
                node -> parent -> color = true;
                if(w -> left != nullptr)w -> left -> color = true;
                rightRotate(w);
                node = root;
            }
            else{                                                            //case 4. both children of brother of node are red
                w -> color = node -> parent -> color;
                node -> parent -> color = true;
                if(w -> left != nullptr)w -> left -> color = true;
                rightRotate(w);
                node = root;
            }
        }
    }
    node -> color = true;
}

BRNode* BRTree::BRsearch(BRNode* x, int value) {
    if(x == nullptr || value == x -> key) return x;
    if(value < x -> key) return BRsearch(x -> left, value);
    else return BRsearch(x -> right, value);
}

BRNode* BRTree::successor(BRNode* node) {
    if(node -> right != nullptr) return treeMin(node -> right);   //case 1. successor is right descendant of node
    BRNode* y = node -> parent;                                         //case 2. successor is left descendant of node
    while(y != nullptr && node == y -> right){
        node = y;
        y = node -> parent;
    }
    return y;
}

BRNode* BRTree::treeMin(BRNode* node){
    while(node -> left != nullptr){
        node = node -> left;
    }
    return node;
}

BRNode* BRTree::find(BRNode * node, int vertex) {
    if (node == nullptr) return nullptr;

    BRNode* leftResult = find(node -> left, vertex);
    if (leftResult != nullptr) return leftResult;
    if (node -> vertex == vertex) return node;
    BRNode* rightResult = find(node->right, vertex);
    if (rightResult != nullptr) return rightResult;

    return nullptr;
}

void BRTree::printTree(BRNode* node,string indent, bool last) {
    if (node != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }
        string color = node -> color ? "BLACK" : "RED";     // false = red , true = black color
        cout << node -> key << "(" << color << ")" << endl;
        printTree(node -> left, indent, false);
        printTree(node -> right, indent, true);
    }
}