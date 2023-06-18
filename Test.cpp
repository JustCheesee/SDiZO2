#include <windows.h>
#include <iostream>
#include <fstream>
#include <fstream>
#include "Test.h"
#include "GraphMatrix.cpp"
#include <random>
#include "GraphList.cpp"

using namespace std;

void Test::StartCounter() {
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double Test::GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

int main(){
    Test test;
    std::ofstream ofs;
    ofs.open("results.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    int sr;
    int ver = 100;
    int times = 10;
    bool dir = true;
    for(int i = 0; i < times; i++) {  //how many times to perform test
        srand(time(nullptr));

        std::ofstream ofs;
        ofs.open("testnodes.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

//        GraphList* graph = new GraphList(false, ver, 0.25, dir);
        GraphMatrix* graph = new GraphMatrix(false, ver, 0.25, dir);       //tested structure

        test.StartCounter();
        graph->algDijstra(0);            //tested function
        int counter = test.GetCounter();


        sr += counter;
        std::ofstream outfile;
        outfile.open("results.txt", std::ios_base::app);
        outfile << counter << "\n";
    }
    sr = sr / times;
    cout << sr << endl;

    sr = 0;
    for(int i = 0; i < times; i++) {  //how many times to perform test
        srand(time(nullptr));

        std::ofstream ofs;
        ofs.open("testnodes.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

//        GraphList* graph = new GraphList(false, ver, 0.50, dir);        //tested structure
        GraphMatrix* graph = new GraphMatrix(false, ver, 0.5, dir);

        test.StartCounter();
        graph->algDijstra(0);            //tested function
        int counter = test.GetCounter();


        sr += counter;
        std::ofstream outfile;
        outfile.open("results.txt", std::ios_base::app);
        outfile << counter << "\n";
    }
    sr = sr / times;
    cout << sr << endl;

    sr = 0;
    for(int i = 0; i < times; i++) {  //how many times to perform test
        srand(time(nullptr));

        std::ofstream ofs;
        ofs.open("testnodes.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

//        GraphList* graph = new GraphList(false, ver, 0.75, dir);        //tested structure
        auto* graph = new GraphMatrix(false, ver, 0.75, dir);

        test.StartCounter();
        graph->algDijstra(0);            //tested function
        int counter = test.GetCounter();


        sr += counter;
        std::ofstream outfile;
        outfile.open("results.txt", std::ios_base::app);
        outfile << counter << "\n";
    }
    sr = sr / times;
    cout << sr << endl ;

    sr = 0;
    for(int i = 0; i < times; i++) {  //how many times to perform test
        srand(time(nullptr));

        std::ofstream ofs;
        ofs.open("testnodes.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

//        GraphList* graph = new GraphList(false, ver, 0.99, dir);        //tested structure
        GraphMatrix* graph = new GraphMatrix(false, ver, 0.99, dir);

        test.StartCounter();
        graph->algDijstra(0);            //tested function
        int counter = test.GetCounter();


        sr += counter;
        std::ofstream outfile;
        outfile.open("results.txt", std::ios_base::app);
        outfile << counter << "\n";
    }
    sr = sr / times;
    cout << sr << endl;
    return 0;
}