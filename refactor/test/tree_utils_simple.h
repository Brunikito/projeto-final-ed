// Versão simplificada para testes
#ifndef TREE_UTILS_SIMPLE_H
#define TREE_UTILS_SIMPLE_H

#include <string>
#include <vector>

struct RotationStats {
    int LL;
    int RR;  
    int LR;
    int RL;
};

struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node *parent;
    Node *left;
    Node *right;
    int height;
    int isRed;
};

struct BinaryTree {
    Node *root;
    Node *NIL;
};

struct InsertResult
{
    int numComparisons;
    double executionTime;
    // -- v3.0.0 -- 
    RotationStats numRotations;
    int numRecoloring;
    int insertDepth;
    int finalTreHeight;
};

struct SearchResult
{
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
    // -- v3.0.0 -- 
    int searchDepth;
};

#endif // TREE_UTILS_SIMPLE_H
