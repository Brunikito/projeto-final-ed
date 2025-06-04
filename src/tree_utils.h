#ifndef TREE_UTILS_H
#define TREE_UTILS_H
#include <string>
#include <vector>

// Structs e Funções auxiliares, como Criar Nó, Computar altura, Busca, Exibir Árvore, etc/**

/* @struct Node
* @brief Nó da Árvore Binária de Busca.
*/
struct Node
{
    std::string word;
    std::vector<int> documentIds;
    Node *parent;
    Node *left;
    Node *right;
    int height; // não usado na BST (usado na AVL)
    int isRed;	// não usado na BST (usado na RBT)
};

/**
 * @struct BinaryTree
 * @brief Estrutura raiz que contém a árvore.
 */
struct BinaryTree
{
    Node *root;
    Node *NIL; // não usado na BST
};

/**
 * @struct InsertResult
 * @brief Estatisticas retornadas pela função ::BST::insert.
 */
struct InsertResult
{
    int numComparisons; // Conta tanto comparações de igualdade quanto de ordenação
    double executionTime; // Duração da operação em microssegundos
};

/**
 * @struct SearchResult
 * @brief Resultado detalhado da função ::BST::search.
 */
struct SearchResult
{
    int found; // 1 = palavra encontrada, 0 = não encontrada
    std::vector<int> documentIds; // IDs dos documentos onde a palavra ocorre
    double executionTime;
    int numComparisons;
};

#endif // TREE_UTILS_H