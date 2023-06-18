#include "DSU.h"

DSU::DSU(int number){
    parent = new int[number];
    rank = new int[number];

    for (int i = 0; i < number; i++) {
        parent[i] = -1;
        rank[i] = 1;
    }
}

DSU::~DSU() = default;

int DSU::find(int vertex){                                  //find vertex in dsu
    if (parent[vertex] == -1) return vertex;
    return parent[vertex] = find(parent[vertex]);
}

void DSU::unite(int first, int second){                     //connect the trees
    int u = find(first);
    int v = find(second);

    if (u != v) {
        if (rank[u] < rank[v]) {
            parent[u] = v;
        }
        else if (rank[u] > rank[v]) {
            parent[v] = u;
        }
        else {
            parent[v] = u;
            rank[u] += 1;
        }
    }
}