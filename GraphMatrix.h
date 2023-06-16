#ifndef SDIZO2_GRAPHMATRIX_H
#define SDIZO2_GRAPHMATRIX_H
#include "MatrixNode.h"

class GraphMatrix {
    public:
        int V, E;
        MatrixNode ** matrix;
        int** edges;
        GraphMatrix(bool, int, double, bool);
        ~GraphMatrix();
        void printMatrix();
        void readGraph(bool);
        void randomGraph(double, int, bool);
        void matrixToFile(bool);
        int* algPrim();
        int* algKruskal();
};


#endif //SDIZO2_GRAPHMATRIX_H
