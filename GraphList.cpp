#include "GraphList.h"
#include "Node.cpp"
#include "DoublyLinkedList.h"
#include "DoublyLinkedList.cpp"
#include "BRTree.cpp"
#include "BRNode.cpp"
#include "DSU.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
static int * parent;

GraphList::GraphList(bool file, int vertexes, double density, bool directed) {    //Constructor creating list representation of graph.
    this -> V = 0;                                                               //Its depending on bool file (read from file or random).
    this -> E = 0;
    this -> array = new DoublyLinkedList[0];
    if(file){
        readGraph(directed);
    }
    else {
        randomGraph(density, vertexes, directed);
    }
}

GraphList::~GraphList() = default;

void GraphList::printList() {
    if(array != nullptr){
        for(int i = 0; i < V; i++){
            array[i].printList();
        }
    }
}

void GraphList::readGraph(bool directed) {             //reading from file and creating list implementation of graph
    delete [] array;
    delete [] edges;
    string myText;
    ifstream MyReadFile("graph.txt");
    bool first_line = true;

    int counter = 0;
    while (getline (MyReadFile, myText)) {
        istringstream iss(myText);
        vector<string> mySplitText;
        string word;

        while(getline(iss, word,' ')){
            mySplitText.push_back(word);
        }

        if(first_line){                                                     //get vertexes and edges from first line
            auto* array1 = new DoublyLinkedList[stoi(mySplitText[1])];
            this -> array = array1;
            this -> V = stoi(mySplitText[1]);
            this -> E = stoi(mySplitText[0]);
            this -> edges = new int*[E];
            for(int i = 0; i < E; i++){
                edges[i] = new int[3];
            }
            for(int i = 0; i < V; i++){
                DoublyLinkedList list;
                array[i] = list;
            }
            first_line = false;
        }
        else{                                                               //set edges in graph
            array[stoi(mySplitText[0])].addEnd(stoi(mySplitText[1]), stoi(mySplitText[2]));
            if(!directed)array[stoi(mySplitText[1])].addEnd(stoi(mySplitText[0]), stoi(mySplitText[2]));
            edges[counter][0] = stoi(mySplitText[0]);
            edges[counter][1] = stoi(mySplitText[1]);
            edges[counter][2] = stoi(mySplitText[2]);
            counter++;
        }
    }
    MyReadFile.close();
}

void GraphList::randomGraph(double density, int vertexes, bool directed) {     //random graph generation
    delete [] array;
    if(!directed)this -> E = density * vertexes * (vertexes - 1) / 2;
    else this -> E = density * vertexes * (vertexes - 1);
    this -> V = vertexes;
    auto* array1 = new DoublyLinkedList[V];
    this -> array = array1;
    int edges = E;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(1, 9);
    int value;
    uniform_int_distribution<int> uni2(0, V - 1);
    int vertex;
    int destination;
    for(int i = 0; i < V; i++){                             //first connect each vertex
        while(true){
            vertex = uni2(rng);
            value = uni(rng);
            if(array[i].search(vertex) == nullptr && vertex != i){
                if(directed){
                    array[i].addEnd(vertex, value);
                    break;
                }
                if(!directed && array[vertex].search(i) == nullptr){
                    array[i].addEnd(vertex, value);
                    array[vertex].addEnd(i, value);
                    break;
                }
            }
        }
        edges--;
    }
    for(int i = edges; i > 0; i--){                         //random connections
        while(true){
            vertex = uni2(rng);
            destination = uni2(rng);
            value = uni(rng);
            if(array[destination].search(vertex) == nullptr && vertex != destination){
                if(directed){
                    array[destination].addEnd(vertex, value);
                    break;
                }
                if(array[vertex].search(destination) == nullptr && !directed){
                    array[destination].addEnd(vertex, value);
                    array[vertex].addEnd(destination, value);
                    break;
                }
            }
        }
    }
}

int* GraphList::algPrim() {
    BRTree queue;
    parent = new int[V];
    for(int i = 0; i < V; i++){
        auto * node = new BRNode;
        if(i == 0) node -> key = 0;
        else  node -> key = numeric_limits<int>::max();
        node -> vertex = i;
        queue.BRinsert(node);
    }
    parent[0] = -1;
    while(queue.root != nullptr){
        auto min = queue.treeMin(queue.root);
        auto v = array[min -> vertex].head;
        for(int i = 0; i < array[min -> vertex].size; i++){
            auto vv = queue.find(queue.root, v->value);
            if(vv && v -> weight < vv -> key){
                parent[vv -> vertex] = min -> vertex;
                vv -> key = v -> weight;
                auto * node = new BRNode;
                node -> key = vv -> key;
                node -> vertex = vv -> vertex;
                queue.BRremove(vv);
                queue.BRinsert(node);
            }
            v = v -> next;
        }
        queue.BRremove(min);
    }
    return parent;
}

int* GraphList::algKruskal() {
    DSU dsu(V);
    for(int i = 0; i < E - 1; i++){
        for(int j = 0; j < E - i - 1; j++){
            if(edges[j][2] > edges[j + 1][2]){
                int* tmp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = tmp;
            }
        }
    }

    int minWeight = 0;
    for(int i = 0; i < E; i++){
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u, v);
            minWeight += w;
        }
    }
    return nullptr;
}
