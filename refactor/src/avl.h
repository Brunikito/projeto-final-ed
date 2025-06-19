// v2.1.0

#ifndef AVL_H
#define AVL_H
#include <vector>
#include <string>
#include "utils/tree_utils.h"

namespace AVL {
    /**
     * @brief Cria uma nova Árvore AVL vazia.
     * @return Ponteiro para a árvore criada ou nullptr em caso de falha na alocação.
     */
    BinaryTree* create();

    /**
     * @brief Calcula a altura de um nó na árvore.
     * @param node Nó cuja altura será calculada.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Altura do nó ou 0 se o nó for nullptr.
     */
    int height(Node* node, InsertResult& stats);

    /**
     * @brief Atualiza a altura de um nó com base em seus filhos.
     * @param node Nó cuja altura será atualizada.
     * @param stats Estrutura para rastrear estatísticas da operação.
     */
    void updateHeight(Node* node, InsertResult& stats);

    /**
     * @brief Atualiza recursivamente a altura de um nó e seu pai.
     * @param node Nó inicial para atualização.
     * @param stats Estrutura para rastrear estatísticas da operação.
     */
    void recursiveUpdateHeight(Node* node, InsertResult& stats);

    /**
     * @brief Calcula o fator de balanceamento de um nó.
     * @param node Nó cujo balanceamento será calculado.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Diferença entre as alturas da subárvore direita e esquerda.
     */
    int getBalance(Node* node, InsertResult& stats);

    /**
     * @brief Realiza uma rotação à direita em um nó para balancear a árvore.
     * @param y Nó pivô da rotação.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Novo nó raiz da subárvore após a rotação.
     */
    Node* rightRotate(Node* y, InsertResult& stats);

    /**
     * @brief Realiza uma rotação à esquerda em um nó para balancear a árvore.
     * @param y Nó pivô da rotação.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Novo nó raiz da subárvore após a rotação.
     */
    Node* leftRotate(Node* y, InsertResult& stats);

    /**
     * @brief Rebalanceia a árvore após uma inserção.
     * @param node Nó a ser rebalanceado.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Nó raiz da subárvore após o rebalanceamento.
     */
    Node* rebalance(Node* node, InsertResult& stats);

    /**
     * @brief Insere um novo nó na árvore ou atualiza um nó existente.
     * @param root Raiz da subárvore onde a inserção será realizada.
     * @param word Palavra a ser inserida.
     * @param documentId Identificador do documento associado.
     * @param stats Estrutura para rastrear estatísticas da operação.
     * @return Nó raiz da subárvore após a inserção.
     */
    Node* insertNode(Node* root, const std::string& word, int documentId, InsertResult& stats);

    /**
     * @brief Insere uma palavra na árvore ou adiciona um documentId a um nó existente.
     * @param tree Árvore AVL.
     * @param word Palavra a ser inserida.
     * @param documentId Identificador do documento associado.
     * @return Estrutura InsertResult com estatísticas da operação.
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Busca uma palavra na árvore e retorna os documentos associados.
     * @param tree Árvore AVL.
     * @param word Palavra a ser buscada.
     * @return Estrutura SearchResult com resultados e estatísticas da busca.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief Libera recursivamente a memória de um nó e seus filhos.
     * @param node Nó a ser liberado.
     */
    void destroyNode(Node* node);

    /**
     * @brief Libera toda a memória alocada para a árvore.
     * @param tree Árvore AVL a ser liberada.
     */
    void destroy(BinaryTree* tree);
    
} // namespace AVL

#endif // AVL_H