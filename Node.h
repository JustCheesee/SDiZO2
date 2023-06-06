#ifndef SDIZO2_NODE_H
#define SDIZO2_NODE_H

class Node{
    public:
        int weight;
        int value;
        Node* next;
        Node* prev;
        Node();
        ~Node();
};

#endif //SDIZO2_NODE_H
