#ifndef SDIZO2_GRAPHLIST_H
#define SDIZO2_GRAPHLIST_H
#include "DoublyLinkedList.h"

class GraphList {
    public:
        int V, E;
        DoublyLinkedList * array;
        int ** edges;
        GraphList(bool, int, double, bool);
        ~GraphList();
        void printList();
        void readGraph(bool);
        void randomGraph(double, int, bool);
        int* algPrim();
        int* algKruskal();
};


#endif //SDIZO2_GRAPHLIST_H
