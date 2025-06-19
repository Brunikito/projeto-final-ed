// v1.2.5

#ifndef RBT_H
#define RBT_H

#include <vector>
#include <string>

#include "utils/tree_utils.h"

namespace RBT {
    
    /**
     * @brief Cria uma nova Árvore Rubro-Negra vazia.
     * @return Ponteiro para a árvore criada ou nullptr em caso de falha na alocação.
     */
    BinaryTree* create();

    /**
     * @brief Calcula a altura de um nó na árvore.
     * @param node Nó cuja altura será calculada.
     * @param NIL Nó sentinela da árvore.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Altura do no.
     */
    int height(Node* node, Node* NIL, InsertResult& stats);

    /**
     * @brief Atualiza a altura de um nó com base em seus filhos.
     * @param node Nó cuja altura será atualizada.
     * @param NIL Nó sentinela da árvore.
     * @param stats Estrutura para rastrear estatísticas da operação.
     */
    void updateHeight(Node* node, Node* NIL, InsertResult& stats);

    /**
     * @brief Atualiza recursivamente a altura de um nó e seu pai.
     * @param node Nó inicial para atualização.
     * @param NIL Nó sentinela da árvore.
     * @param stats Estrutura para rastrear estatísticas da operação.
     */
    void recursiveUpdateHeight(Node* node, Node* NIL, InsertResult& stats);

    /**
     * @brief Realiza uma rotação à direita em um nó.
     * @param y Nó pivô da rotação.
     * @param NIL Nó sentinela da árvore.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Novo nó raiz da subárvore após a rotação.
     */
    Node* rightRotate(Node* y, Node* NIL, InsertResult& stats);

    /**
     * @brief Realiza uma rotação à esquerda em um nó.
     * @param y Nó pivô da rotação.
     * @param NIL Nó sentinela da árvore.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Novo nó raiz da subárvore após a rotação.
     */
    Node* leftRotate(Node* y, Node* NIL, InsertResult& stats);

    /**
     * @brief Insere um novo nó na árvore.
     * @param tree Árvore Rubro-Negra.
     * @param word Palavra a ser inserida.
     * @param documentId Identificador do documento associado.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Ponteiro para o novo nó inserido ou nullptr se a palavra já existe.
     */
    Node* insertNode(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Corrige as propriedades da Árvore Rubro-Negra após uma inserção.
     * @param tree Árvore Rubro-Negra.
     * @param insertedNode Nó recém-inserido.
     * @param stats Estrutura para rastrear estatísticas da operação.
     */
    void fixInsert(BinaryTree* tree, Node* insertedNode, InsertResult& stats);

    /**
     * @brief Insere uma palavra na árvore ou adiciona um documentId a um nó existente.
     * @param tree Árvore Rubro-Negra.
     * @param word Palavra a ser inserida.
     * @param documentId Identificador do documento associado.
     * @return Estrutura InsertResult com estatísticas da operação.
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Busca uma palavra na árvore e retorna os documentos associados.
     * @param tree Árvore Rubro-Negra.
     * @param word Palavra a ser buscada.
     * @return Estrutura SearchResult com resultados e estatísticas da busca.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief Libera recursivamente a memória de um nó e seus filhos.
     * @param node Nó a ser liberado.
     * @param NIL Nó sentinela da árvore.
     */
    void destroyNode(Node* node, Node* NIL);

    /**
     * @brief Libera toda a memória da árvore.
     * @param tree Árvore Rubro-Negra a ser liberada.
     */
    void destroy(BinaryTree* tree);
}

#endif // RBT_H