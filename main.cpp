#include <iostream>
#include <random>
#include "GraphList.cpp"
#include "GraphMatrix.cpp"
using namespace std;

int main(){
//    GraphList graph(true, 5, 0.66, false);
//    int* final = graph.algPrim();
//    int minWeight = 0;
//    for(int i = 0; i < graph.V; i++){
//        cout << i << ":" << final[i] << ",  " << endl;
//        if(final[i] != -1) minWeight += graph.array[i].search(final[i]) -> weight;
//    }
//    cout << "Calkowita waga drzewa: " << minWeight;

//    GraphMatrix graph(true, 4, 0.66, false);
//    int* final = graph.algPrim();
//    int minWeight = 0;
//    for(int i = 0; i < graph.V; i++){
//        cout << i << ":" << final[i] << ",  " << endl;
//    }
//    for(int i = 0; i < graph.E; i++){
//        for(int j = 1; j < graph.V; j++){
//            if(graph.matrix[j][i].edge == graph.matrix[final[j]][i].edge){
//                minWeight += graph.matrix[j][i].weight;
//            }
//        }
//    }
//    cout << "Calkowita waga drzewa: " << minWeight;

    GraphMatrix graph(true, 5, 0.66, false);
    int* final = graph.algKruskal();

    return 0;
}