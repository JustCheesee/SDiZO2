#ifndef SDIZO2_SOLUTIONNODE_H
#define SDIZO2_SOLUTIONNODE_H


class SolutionNode {
    public:
        SolutionNode* parent;
        int weight;
        SolutionNode();
        ~SolutionNode();
};


#endif //SDIZO2_SOLUTIONNODE_H
