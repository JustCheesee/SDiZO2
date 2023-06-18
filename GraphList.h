#ifndef SDIZO2_GRAPHLIST_H
#define SDIZO2_GRAPHLIST_H
#include "DoublyLinkedList.h"
#include "BRNode.cpp"

class GraphList {
    public:
        int V, E;
        DoublyLinkedList * array;
        GraphList(bool, int, double, bool);
        ~GraphList();
        void printList();
        void readGraph(bool);
        void randomGraph(double, int, bool);
        int ** getEdges();
        void addEdge(int, int, int);
        int* algPrim();
        int** algKruskal();
        BRNode* algDijstra(int);
        BRNode* algBelFord(int);
};


#endif //SDIZO2_GRAPHLIST_H
