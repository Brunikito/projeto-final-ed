// v3.1.0

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
    BSTTree,
    AVLTree,
    RBTTree
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
int calculateTotalNodes(Node* node, Node* NIL);
int calculateMaxWidth(BinaryTree* tree);
GroupedStats calculateLeavesDepth(Node* node, Node* NIL, int currentDepth = 0);
MemoryUsage calculateMemoryUsage(BinaryTree* tree);

bool isBalanced(Node* node, Node* NIL);
bool isPerfect(Node* node, Node* NIL, int depth, int level = 0);
bool isFull(Node* node, Node* NIL);
bool isComplete(Node* node, Node* NIL, int index, int totalNodes);
TreeFlags calculateTreeFlags(BinaryTree* tree);
WordsStats getWordsStats(BinaryTree* tree);

// Funções principais
TreeStats getTreeStats(BinaryTree* tree);
IndexStats getIndexStats(BinaryTree* tree, IndexingStats& indexingStats);

#endif // TREE_UTILS_H