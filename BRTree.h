#ifndef SDIZO_BRTREE_H
#define SDIZO_BRTREE_H
#include <string>
#include "BRNode.h"

class BRTree{
    public:
        BRNode* root;
        BRNode* watcher;
        void leftRotate(BRNode*);
        void rightRotate(BRNode*);
        void treeInsert(BRNode*);
        void BRinsert(BRNode*);
        void BRremove(BRNode*);
        BRNode* BRsearch(BRNode*, int);
        BRNode* treeMin(BRNode*);
        BRNode* successor(BRNode*);
        void BRfixup(BRNode*);
        void printTree(BRNode*, std::string, bool);
        BRNode* find(BRNode*, int);
        BRTree();
        ~BRTree();
};

#endif //SDIZO_BRTREE_H
