#ifndef SDIZO2_GRAPHLIST_H
#define SDIZO2_GRAPHLIST_H
#include "DoublyLinkedList.h"

class GraphList {
    private:
        int V, E;
        DoublyLinkedList * array;

    public:
        GraphList(bool, int, double, bool);
        ~GraphList();
        void printList();
        void readGraph(bool);
        void randomGraph(double, int, bool);
        void algPrim();
};


#endif //SDIZO2_GRAPHLIST_H
