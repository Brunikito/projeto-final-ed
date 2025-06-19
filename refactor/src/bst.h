// v2.0.2

#ifndef BST_H
#define BST_H

#include <string>
#include <vector>
#include <chrono>

#include "utils/tree_utils.h"

namespace BST {

/**
 * @brief Aloca e inicializa uma BST vazia.
 * @return Ponteiro para @c BinaryTree ou @c nullptr em caso de falha.
 */
BinaryTree* create();

/** 
 *  @brief Insere uma palavra na árvore.
 *  @li Se a palavra existir, adiciona @p documentId.
 *  @li Atualiza alturas dos ancestrais.
 *  @return Estrutura ::InsertResult com tempo e métricas.
 */
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

/** 
 *  @brief Procura uma palavra na BST.
 *  @param tree Ponteiro **const** para a árvore.
 *  @param word Palavra alvo.
 *  @return ::SearchResult com ids encontrados e métricas.
 */
SearchResult search(BinaryTree* tree, const std::string& word);

/**
 * @brief Libera toda a memória alocada pela BST.
 * @param tree Ponteiro para a árvore.
 */
void destroy(BinaryTree *tree);

} // namespace BST

#endif // BST_H
