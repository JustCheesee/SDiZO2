#ifndef SDIZO2_GRAPHMATRIX_H
#define SDIZO2_GRAPHMATRIX_H
#include "MatrixNode.h"
#include "BRNode.h"

class GraphMatrix {
    public:
        int V, E;
        MatrixNode ** matrix;
        GraphMatrix(bool, int, double, bool);
        ~GraphMatrix();
        void printMatrix();
        void readGraph(bool);
        void randomGraph(double, int, bool);
        int ** getEdges();
        void matrixToFile(bool);
        int* algPrim();
        int** algKruskal();
        BRNode* algDijstra(int);
        BRNode* algBelFord(int);
};


#endif //SDIZO2_GRAPHMATRIX_H
