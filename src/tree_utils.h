#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <string>
#include <vector>
#include <iostream>

/** @struct Node
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
 * @brief Estrutura que contém a raiz da árvore binária.
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

/**
 * @brief Percorre a árvore em ordem e imprime no formato "1. palavra: id1, id2, ...".
 * @param node    Ponteiro para o nó atual (nenhuma ação se nullptr).
 * @param counter Contador incremental, inicializado tipicamente em 0, exibido antes de cada palavra.
 */
void recursivePrintIndex(Node* node, int& counter);
/**
 * @brief Desenha recursivamente um diagrama ASCII da árvore.
 *
 * O formato utiliza caracteres ├──, └── e │ para representação hierárquica.
 * @param node    Nó atual (nenhuma ação se nullptr).
 * @param prefix  Prefixo acumulado (espaços ou │) para alinhamento, tipicamente vazio para a raiz.
 * @param isLeft  True se o nó é filho esquerdo, false caso contrário.
 */
void recursivePrintTree(Node* node, const std::string& prefix, bool isLeft);
/**
 * @brief Imprime o índice completo da árvore em ordem, no formato "1. palavra: id1, id2, ...".
 * @param tree Árvore contendo as palavras; se nullptr ou vazia, nenhuma saída é gerada.
 */
void printIndex(BinaryTree* tree);
/**
 * @brief Desenha um diagrama ASCII da árvore usando caracteres ├──, └── e │.
 * @param tree Árvore de entrada; se nullptr ou com root == nullptr, nenhuma saída é gerada.
 */
void printTree(BinaryTree* tree);
/**
 * @brief Exibe no stdout o resultado da busca ou mensagens de erro.
 * @param result Estrutura contendo o resultado da busca; valores inválidos geram mensagens de erro.
 * @param word   Palavra buscada; se vazia, gera mensagem de erro.
 */
void printSearchResult(const SearchResult& result, const std::string& word);
/**
 * @brief Exibe no stdout as estatísticas de busca.
 * @param result Estrutura contendo o resultado da busca; valores inválidos geram mensagens de erro.
 * @note Imprime também o número de comparações realizadas.
 */
void printSearchStats(const SearchResult& result);

/**
 * @brief Calcula recursivamente a altura de uma árvore/subárvore.
 * @param node O nó raiz da árvore/subárvore.
 * @return A altura da árvore. Uma árvore com um único nó tem altura 0.
 */
int getHeight(Node* node);

/**
 * @struct TreeOperations
 * @brief Agrupa ponteiros para as funções de uma árvore específica.
 *
 * Isso permite que `searchTree` opere de forma genérica com BST, AVL ou RBT.
 */
struct TreeOperations {
    BinaryTree* (*create)();
    void (*destroy)(BinaryTree*);
    InsertResult (*insert)(BinaryTree*, const std::string&, int);
    SearchResult (*search)(BinaryTree*, const std::string&);
};

/**
 * @brief Executa o processo de indexação e busca interativa para uma árvore.
 * @param ops Estrutura com as funções (create, insert, etc.) da árvore específica.
 * @param arvore Nome do executável para exibição.
 * @param n_docs Número de documentos a serem indexados.
 * @param directoryFiles Caminho para o diretório dos arquivos de dados.
 */
void searchTree(const TreeOperations& ops, const std::string& arvore, const std::string& comand, int n_docs_inicial, const std::string& directoryFiles);


void runStats(const TreeOperations& ops, const std::string& arvore, const std::string& comand, int n_docs_inicial, const std::string& directoryFiles);

#endif // TREE_UTILS_H