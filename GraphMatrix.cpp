#include "GraphMatrix.h"
#include "MatrixNode.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <synchapi.h>

using namespace std;
static int * parentM;

GraphMatrix::GraphMatrix(bool file, int vertexes, double density, bool directed) {    //Constructor creating list representation of graph.
    this -> V = 0;                                                                  //Its depending on bool file (read from file or random).
    this -> E = 0;
    this -> matrix = new MatrixNode*[0];
    if(file){
        readGraph(directed);
    }
    else {
        randomGraph(density, vertexes, directed);
    }
}

GraphMatrix::~GraphMatrix() = default;

void GraphMatrix::printMatrix() {
    if(V != 0){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < E; j++){
                cout << matrix[i][j].edge << ":" << matrix[i][j].weight << "|";
            }
            cout << "\n";
        }
    }
}

void GraphMatrix::readGraph(bool directed) {             //reading from file and creating list implementation of graph
    delete [] matrix;
    string myText;
    ifstream MyReadFile("graph.txt");
    bool first_line = true;
    int iterator = 0;
    int counter = 0;
    while (getline (MyReadFile, myText)) {
        istringstream iss(myText);
        vector<string> mySplitText;
        string word;

        while(getline(iss, word,' ')){
            mySplitText.push_back(word);
        }

        if(first_line){                                                     //get vertexes and edges from first line
            this -> V = stoi(mySplitText[1]);
            this -> E = stoi(mySplitText[0]);
            auto** matrix1 = new MatrixNode*[stoi(mySplitText[1])];
            this -> matrix = matrix1;
            for (int i = 0; i < V; i++) {
                matrix[i] = new MatrixNode[E];
            }
            first_line = false;
        }

        else{                                                               //set edges in graph
            matrix[stoi(mySplitText[0])][iterator].weight = stoi(mySplitText[2]);
            matrix[stoi(mySplitText[0])][iterator].edge = 1;
            matrix[stoi(mySplitText[1])][iterator].weight = stoi(mySplitText[2]);
            if(!directed)matrix[stoi(mySplitText[1])][iterator].edge = 1;
            else matrix[stoi(mySplitText[1])][iterator].edge = -1;
            counter++;
            iterator++;
        }
    }
    MyReadFile.close();
}

void GraphMatrix::randomGraph(double density, int vertexes, bool directed) {     //random graph generation
    delete [] matrix;
    if(!directed)this -> E = density * vertexes * (vertexes - 1) / 2;
    else this -> E = density * vertexes * (vertexes - 1);
    this -> V = vertexes;
    auto matrix1 = new MatrixNode*[V];
    for (int i = 0; i < V; i++) {
        matrix1[i] = new MatrixNode[E];
    }
    this -> matrix = matrix1;
    int edges = E;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(1, 9);
    int value;
    uniform_int_distribution<int> uni2(0, V - 1);
    int vertex;
    int destination;
    int currentColumn = 0;
    for(int i = 0, k = 0; i < V; i++, k++){                             //first connect each vertex
        while(true){
            vertex = uni2(rng);
            value = uni(rng);
            int isConnected = false;
            if(vertex != i){
                if(!directed){
                    for(int j = 0; j < E; j++){
                        if(matrix[vertex][j].edge == 1 && matrix[i][j].edge == 1){
                            isConnected = true;
                        }
                    }
                    if(!isConnected){
                        matrix[i][i].edge = 1;
                        matrix[i][i].weight = value;
                        matrix[vertex][i].edge = 1;
                        matrix[vertex][i].weight = value;
                        currentColumn++;
                        break;
                    }
                }
                else{
                    matrix[i][i].edge = 1;
                    matrix[i][i].weight = value;
                    if(i == V - 1){
                        matrix[0][i].edge = -1;
                        matrix[0][i].weight = value;
                    }
                    else{
                        matrix[i+1][i].edge = -1;
                        matrix[i+1][i].weight = value;
                    }
                    currentColumn++;
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
            int isConnected = false;
            if(vertex != destination){
                for(int j = 0; j < E; j++){
                    if(matrix[vertex][j].edge == 1 && matrix[destination][j].edge == 1) isConnected = true;
                }
                if(!isConnected){
                    matrix[destination][currentColumn].edge = 1;
                    matrix[destination][currentColumn].weight = value;
                    if(!directed)matrix[vertex][currentColumn].edge = 1;
                    else matrix[vertex][currentColumn].edge = -1;
                    matrix[vertex][currentColumn].weight = value;
                    currentColumn++;
                    break;
                }
            }
        }
    }
}

void GraphMatrix::matrixToFile(bool directed) {
    ofstream file;
    file.open("graphOutput.txt");
    file << E << " " << V << endl;
    for(int j = 0; j < E; j++){
        int first;
        int second;
        int value;
        bool sec = false;
        for(int i = 0; i < V; i++){
            if(directed){
                if(matrix[i][j].edge > 0){
                    first = i;
                    value = matrix[i][j].weight;
                }
                if(matrix[i][j].edge < 0) second = i;
            }
            else {
                if(matrix[i][j].edge > 0){
                    if(!sec){
                        first = i;
                        sec = true;
                    }
                    else second = i;
                    value = matrix[i][j].weight;
                }
            }
        }
        file << first << " " << second << " " << value << endl;
    }
    file.close();
}

int * GraphMatrix::algPrim() {
    BRTree queue;
    parentM = new int[V];
    for(int i = 0; i < V; i++){
        auto * node = new BRNode;
        if(i == 0) node -> key = 0;
        else  node -> key = numeric_limits<int>::max();
        node -> vertex = i;
        queue.BRinsert(node);
    }
    parentM[0] = -1;
    while(queue.root != nullptr){
        auto min = queue.treeMin(queue.root);
        for(int i = 0; i < E; i++){
            if(matrix[min -> vertex][i].edge == 0)continue;
            auto v = matrix[min -> vertex][i];
            int vertex;
            for(int j = 0; j < V; j++){
                if(j != min -> vertex && matrix[j][i].edge != 0) vertex = j;
            }
            auto vv = queue.find(queue.root, vertex);
            if(vv && v.weight < vv -> key){
                parentM[vv -> vertex] = min -> vertex;
                vv -> key = v.weight;
                auto * node = new BRNode;
                node -> key = vv -> key;
                node -> vertex = vv -> vertex;
                queue.BRremove(vv);
                queue.BRinsert(node);
            }
        }
        queue.BRremove(min);
    }
    return parentM;
}

int** GraphMatrix::algKruskal() {
    DSU dsu(V);
    int** parent = new int*[V];
    for(int i = 0; i < V; i++){
        parent[i] = new int[2];
    }
    int ** edges = getEdges();
    for(int i = 0; i < E - 1; i++){
        for(int j = 0; j < E - i - 1; j++){
            if(edges[j][2] > edges[j + 1][2]){
                int* tmp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = tmp;
            }
        }
    }

    int counter = 0;
    int minWeight = 0;
    for(int i = 0; i < E; i++){
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u, v);
            minWeight += w;
            parent[counter][0] = u;
            parent[counter][1] = v;
            counter++;
        }
    }
    return parent;
}

BRNode *GraphMatrix::algDijstra(int start) {
    BRTree queue;
    auto* solution = new BRNode[V];
    for(int i = 0; i < V; i++){
        auto * node = new BRNode;
        if(i == start) node -> key = 0;
        else  node -> key = numeric_limits<int>::max();
        node -> vertex = i;
        queue.BRinsert(node);
    }
    while(queue.root != nullptr){
        auto min = queue.treeMin(queue.root);
        for(int i = 0; i < E; i++){
            if(matrix[min -> vertex][i].edge != 1)continue;
            auto v = matrix[min -> vertex][i];
            int vertex;
            for(int j = 0; j < V; j++){
                if(j != min -> vertex && matrix[j][i].edge == -1) vertex = j;
            }
            auto vv = queue.find(queue.root, vertex);
            if(vv && vv -> key > min -> key + v.weight){
                vv -> key = min -> key + v.weight;
                auto * node = new BRNode;
                node -> key = vv -> key;
                node -> vertex = vv -> vertex;
                node -> before = new BRNode;
                node -> before -> vertex = min -> vertex;
                queue.BRremove(vv);
                queue.BRinsert(node);
            }
        }
        solution[min -> vertex] = *min;
        queue.BRremove(min);
    }
    return solution;
}

BRNode *GraphMatrix::algBelFord(int start) {
    BRTree queue;
    auto* solution = new BRNode[V];
    for(int i = 0; i < V; i++){
        auto * node = new BRNode;
        if(i == start) node -> key = 0;
        else  node -> key = numeric_limits<int>::max() - 2000;
        node -> vertex = i;
        queue.BRinsert(node);
    }
    solution[start].vertex = start;
    solution[start].key = 0;
    for(int i = 0; i <= V - 1; i++){
        for(int j = 0; j < E; j++){
            BRNode* vv;
            BRNode* vy;
            MatrixNode v;
            for(int k = 0; k < V; k++){
                if(matrix[k][j].edge == 0) continue;
                if(matrix[k][j].edge == -1){
                    vv = queue.find(queue.root, k);
                    v = matrix[k][j];
                }
                if(matrix[k][j].edge == 1) vy = queue.find(queue.root, k);
            }
            if(vv && vy && vv -> key > vy -> key + v.weight){
                vv -> key = vy -> key + v.weight;
                auto * node = new BRNode;
                node -> key = vv -> key;
                node -> vertex = vv -> vertex;
                node -> before = new BRNode;
                node -> before -> vertex = vy -> vertex;
                solution[node -> vertex] = *node;
                queue.BRremove(vv);
                queue.BRinsert(node);
            }
        }
    }
    return solution;
}

int **GraphMatrix::getEdges() {
    int ** edges = new int*[E];
    for(int i = 0; i < E; i++){
        edges[i] = new int[3];
    }

    for(int i = 0; i < E; i++){
        bool first = true;
        for(int j = 0; j < V; j++){
            if(matrix[j][i].edge == 1 && first){
                edges[i][0] = j;
                first = false;
                continue;
            }
            if(matrix[j][i].edge == 1){
                edges[i][1] = j;
                edges[i][2] = matrix[j][i].weight;
            }
        }
    }
    return edges;
}


