// v3.0.1

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <string>
#include <vector>

#include "bench_utils.h"
#include "value_utils.h"
#include "less_than.h"

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

void recursivePrintIndex(Node* node, int& counter);
void recursivePrintTree(Node* node, const std::string& prefix, bool isLeft);
void printIndex(BinaryTree* tree);
void printTree(BinaryTree* tree);


// -- Funções e structs não obrigatórias --

struct TreeOperations {
    BinaryTree* (*create)();
    void (*destroy)(BinaryTree*);
    InsertResult (*insert)(BinaryTree*, const std::string&, int);
    SearchResult (*search)(BinaryTree*, const std::string&);
};

struct WordOcurrences {
    std::string word;
    int numOcurrences;
};

struct WordsStats {
    std::vector<WordOcurrences> wordOcurrences;
    GroupedStats ocurrenceStats;
};

enum TreeType {
    BST,
    AVL,
    RBT
};

struct TreeFlags{
    bool isBalanced;
    bool isPerfect;
    bool isFull;
    bool isComplete;
};

struct TreeStats {
    TreeType type;
    int height;
    int totalNodes;
    int maxWidth; // Número máximo de nós em um mesmo nível
    GroupedStats leavesDepth;
    TreeFlags flags;
    MemoryUsage memoryUsage;
};

struct IndexStats {
    IndexingStats indexingStats;
    TreeStats treeStats;
    WordsStats wordStats;
};

// Funções auxiliares para calcular as estatísticas da árvore (onde node é passado, a função é recursiva)
int calculateTreeHeight(BinaryTree* tree);
int calculateTotalNodes(Node* tree);
int calculateMaxWidth(BinaryTree* tree);
GroupedStats calculateLeavesDepth(Node* node, int currentDepth = 0);
MemoryUsage calculateMemoryUsage(BinaryTree* tree);

bool isBalanced(Node* node);
bool isPerfect(Node* node, int depth, int level = 0);
bool isFull(Node* node);
bool isComplete(Node* node, int index, int totalNodes);
TreeFlags calculateTreeFlags(BinaryTree* tree);

// Funções principais
TreeStats getTreeStats(BinaryTree* tree);
IndexStats getIndexStats(BinaryTree* tree, IndexingStats& indexingStats);

#endif // TREE_UTILS_H