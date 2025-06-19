// v3.4.78

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <string>
#include <vector>

#include "bench_utils.h"
#include "value_utils.h"
#include "less_than.h"

/**
 * @struct Node
 * @brief Nó genérico para árvores de busca (BST, AVL ou RBT).
 *
 * Cada nó armazena uma @p word (chave), o vetor de @p documentIds em que essa
 * palavra aparece e ponteiros para pai e filhos.  O campo @p height é usado
 * apenas por AVL, enquanto @p isRed identifica a cor nos algoritmos de Red–
 * Black Tree (0 = preto, 1 = vermelho). O ponteiro @p NIL corresponde ao nó
 * sentinela utilizado por RBT; para BST/AVL deve ser @c nullptr.
 */
struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node *parent;
    Node *left;
    Node *right;
    int height;
    int isRed;
};

/**
 * @struct BinaryTree
 * @brief Estrutura‑raiz que encapsula a árvore propriamente dita.
 *
 * O ponteiro @p root aponta para o nó raiz.  Em RBTs, @p NIL é a
 * sentinela preta; nos demais tipos ela pode ser @c nullptr.
 */
struct BinaryTree {
    Node *root;
    Node *NIL;
};

/**
 * @struct InsertResult
 * @brief Estatísticas retornadas por operações de inserção.
 * 
 */
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

/**
 * @struct SearchResult
 * @brief Estatísticas e resultado de uma busca.
 */
struct SearchResult
{
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
    // -- v3.0.0 -- 
    int searchDepth;
};

/**
 * @brief Imprime recursivamente o índice em ordem alfabética.
 *
 * Para cada palavra são listados os ids de documento únicos, seguidos do
 * multiplicador (xN) quando houver repetições.
 * @param node     nó atual (sub‑raiz)
 * @param counter  contador incremental para enumerar as palavras
 */
void recursivePrintIndex(Node* node, int& counter);
/**
 * @brief Desenha a árvore em ASCII, estilo diagrama de diretórios.
 *
 * @param node    nó atual
 * @param prefix  prefixo aplicado a cada nível (|   ou «espaços»)
 * @param isLeft  @c true se o nó está à esquerda do pai
 */
void recursivePrintTree(Node* node, const std::string& prefix, bool isLeft);
/**
 * @brief Versão utilitária que imprime o índice inteiro a partir da raiz.
 */
void printIndex(BinaryTree* tree);
/**
 * @brief Versão utilitária que imprime a árvore inteira a partir da raiz.
 */
void printTree(BinaryTree* tree);


// -- Funções e structs não obrigatórias --

/**
 * @struct TreeOperations
 * @brief Ponteiros de função para desacoplar implementação concreta.
 */
struct TreeOperations {
    BinaryTree* (*create)();
    void (*destroy)(BinaryTree*);
    InsertResult (*insert)(BinaryTree*, const std::string&, int);
    SearchResult (*search)(BinaryTree*, const std::string&);
};

/** @struct WordOcurrences  @brief Contador de ocorrências por palavra. */
struct WordOcurrences {
    std::string word;
    int numOcurrences;
};

/**
 * @struct WordsStats
 * @brief Estatísticas agregadas de frequência de palavras.
 *
 * - @p wordOcurrences: lista (palavra, contagem)
 * - @p ocurrenceStats: distribuição estatística (mín., máx., mediana, …)
 */
struct WordsStats {
    std::vector<WordOcurrences> wordOcurrences;
    GroupedStats ocurrenceStats;
};

/** Enumerador do tipo de árvore representada. */
enum TreeType {
    BSTTree,
    AVLTree,
    RBTTree
};

/**
 * @struct TreeFlags
 * @brief Propriedades estruturais clássicas.
 *
 * - @b Balanced: diferenças de altura ≤ 1 em todos os nós.
 * - @b Perfect: todos os níveis completamente preenchidos.
 * - @b Full: cada nó tem 0 ou 2 filhos.
 * - @b Complete: preenchida da esquerda para a direita.
 */
struct TreeFlags{
    bool isBalanced;
    bool isPerfect;
    bool isFull;
    bool isComplete;
};

/**
 * @struct TreeStats
 * @brief Conjunto de métricas da árvore.
 */
struct TreeStats {
    TreeType type; // tipo da árvore
    int height; // alturas
    int totalNodes; // número total de nós
    int maxWidth; // número máximo de nós em um mesmo nível
    GroupedStats leavesDepth; // distribuição da profundidade das folhas
    TreeFlags flags; // propriedades estruturais
    MemoryUsage memoryUsage; // memória ocupada
};

/**
 * @struct IndexStats
 * @brief Estatísticas globais que combinam tempo de indexação e estrutura.
 */
struct IndexStats {
    IndexingStats indexingStats; // métricas de construção (tempo, comparações…)
    TreeStats treeStats; // métricas estruturais
    WordsStats wordStats; // métricas de frequência
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

/** Coleta métricas estruturais (@ref TreeStats) da árvore. */
TreeStats getTreeStats(BinaryTree* tree);

/**
 * Reúne estatísticas completas do índice.
 * @param tree          ponteiro para a árvore indexada
 * @param indexingStats métricas de construção já coletadas
 */
IndexStats getIndexStats(BinaryTree* tree, IndexingStats& indexingStats);

#endif // TREE_UTILS_H