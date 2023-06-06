#ifndef SDIZO2_GRAPHMATRIX_H
#define SDIZO2_GRAPHMATRIX_H
#include "MatrixNode.h"

class GraphMatrix {
    private:
        int V, E;
        MatrixNode ** matrix;

    public:
        GraphMatrix(bool, int, double, bool);
        ~GraphMatrix();
        void printMatrix();
        void readGraph(bool);
        void randomGraph(double, int, bool);
        void matrixToFile(bool);
        void algPrim();
};


#endif //SDIZO2_GRAPHMATRIX_H
