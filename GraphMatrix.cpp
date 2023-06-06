#include "GraphMatrix.h"
#include "MatrixNode.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <synchapi.h>

using namespace std;

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
    auto** matrix1 = new MatrixNode*[V];
    for (int i = 0; i < V; i++) {
        matrix[i] = new MatrixNode[E];
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
                for(int j = 0; j < E; j++){
                    if(matrix[vertex][j].edge == 1 && matrix[i][j].edge == 1){
                        isConnected = true;
                    }
                }
                if(!isConnected){
                    matrix[i][i].edge = 1;
                    matrix[i][i].weight = value;
                    if(!directed)matrix[vertex][i].edge = 1;
                    else matrix[vertex][i].edge = -1;
                    matrix[vertex][i].weight = value;
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

void GraphMatrix::algPrim() {

}


