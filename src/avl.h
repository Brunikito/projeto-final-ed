#ifndef AVL_H
#define AVL_H
#include <vector>
#include <string>
#include "tree_utils.h"

namespace AVL {
    /**
     * @brief Cria uma arvore AVL vazia.
     * @return Ponteiro para BinaryTree ou nullptr em caso de erro.
     */
    BinaryTree* create();
    /**
     * @brief Retorna a altura de um no.
     * @param node  No alvo ou nullptr.
     * @return Altura (0 se node == nullptr).
     */
    int height(Node* node);
    /**
     * @brief Atualiza o campo height de um no com base nos filhos.
     * @param node  No cujo campo height deve ser ajustado.
     */
    void updateHeight(Node* node);
    /**
     * @brief Atualiza alturas subindo recursivamente ate a raiz.
     *
     * Incrementa numComparisons a cada comparacao interna.
     * @param node            No inicial.
     * @param numComparisons  Referencia ao contador de comparacoes.
     */
    void recursiveUpdateHeight(Node* node, int& numComparisons);
    /**
     * @brief Calcula o fator de balanceamento de um no.
     *
     * fator = altura(dir) menos altura(esq)
     * @param node  No alvo ou nullptr.
     * @return Valor do fator (0 se node == nullptr).
     */
    int getBalance(Node* node);
    /**
     * @brief Rotacao simples a direita.
     * @param y  Sub-raiz desequilibrada.
     * @return Nova sub-raiz apos a rotacao.
     */
    Node* rightRotate(Node* y);
    /**
     * @brief Rotacao simples a esquerda.
     * @param y  Sub-raiz desequilibrada.
     * @return Nova sub-raiz apos a rotacao.
     */
    Node* leftRotate(Node* y);
    /**
     * @brief Re-equilibra a sub-arvore enraizada em node, se necessario.
     *
     * Detecta casos LL, LR, RL e RR, aplicando rotacoes apropriadas.
     * Incrementa numComparisons a cada comparacao feita.
     *
     * @param node            Sub-raiz potencialmente desequilibrada.
     * @param numComparisons  Referencia ao contador de comparacoes.
     * @return Nova sub-raiz equilibrada.
     */
    Node* rebalance(Node* node, int& numComparisons);
    /**
     * @brief Insere uma palavra na sub-arvore root (chamada recursiva).
     *
     * Caso a palavra ja exista, apenas adiciona documentId ao vetor
     * correspondente (sem duplicatas).  Atualiza estatisticas em stats.
     *
     * @param root        Sub-arvore onde a insercao comeca.
     * @param word        Palavra a ser inserida.
     * @param documentId  ID do documento associado.
     * @param stats       Estrutura de saida com contagem de comparacoes.
     * @return Raiz (possivelmente nova) da sub-arvore.
     */
    Node* insertNode(Node* root, const std::string& word, int documentId, InsertResult& stats);
    /**
     * @brief Insere word na arvore AVL completa.
     *
     * Mede tempo e comparacoes, devolvendo um InsertResult preenchido.
     *
     * @param tree        Ponteiro para a arvore.
     * @param word        Palavra a ser inserida.
     * @param documentId  ID do documento associado.
     * @return Estrutura InsertResult com metricas da operacao.
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    /**
     * @brief Procura word na arvore AVL.
     *
     * Preenche SearchResult indicando se encontrou, quais documentIds
     * estao associados, o tempo gasto e o numero de comparacoes.
     *
     * @param tree  Ponteiro para a arvore.
     * @param word  Palavra buscada.
     * @return Estrutura SearchResult com o resultado.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);
    /**
     * @brief Desaloca recursivamente todos os nos da sub-arvore.
     * @param node  Raiz da sub-arvore (pode ser nullptr).
     */
    void destroyNode(Node* node);
    /**
     * @brief Libera toda a memoria usada pela arvore.
     * @param tree  Ponteiro para a arvore (pode ser nullptr).
     *
     * Depois da chamada o ponteiro original torna-se invalido.
     */
    void destroy(BinaryTree* tree);
} // namespace AVL

#endif // AVL_H