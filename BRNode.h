#ifndef SDIZO_BRNODE_H
#define SDIZO_BRNODE_H

class BRNode{
public:
    int vertex;
    int key;
    bool color;   //false - red, true - black
    BRNode* right;
    BRNode* left;
    BRNode* parent;
    BRNode* before;
    BRNode();
    ~BRNode();
};

#endif //SDIZO_BRNODE_H
