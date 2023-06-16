#ifndef SDIZO2_DSU_H
#define SDIZO2_DSU_H


class DSU {
    public:
        int* parent;
        int* rank;
        int find(int);
        void unite(int, int);
        DSU(int);
        ~DSU();
};


#endif //SDIZO2_DSU_H
