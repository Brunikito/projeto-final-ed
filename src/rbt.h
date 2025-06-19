// v1.2.6

#ifndef RBT_H
#define RBT_H

#include <vector>
#include <string>

#include "utils/tree_utils.h"

/**
 * @brief O namespace RBT encapsula toda a funcionalidade da Árvore Rubro-Negra.
 */
namespace RBT {
    
    /**
     * @brief Cria uma nova Árvore Rubro-Negra vazia.
     * * Inicializa a árvore com um nó sentinela (NIL) para simplificar
     * as operações de inserção e balanceamento.
     * * @return Ponteiro para a estrutura BinaryTree criada ou nullptr em caso de falha.
     */
    BinaryTree* create();

    /**
     * @brief Insere uma palavra na árvore. Se a palavra já existe, adiciona o ID do documento à lista.
     * * Após a inserção de um novo nó, a função invoca a lógica de correção
     * para garantir que as propriedades da Árvore Rubro-Negra sejam mantidas.
     * * @param tree Ponteiro para a Árvore Rubro-Negra.
     * @param word A palavra a ser inserida.
     * @param documentId O ID do documento onde a palavra foi encontrada.
     * @return Estrutura InsertResult contendo as estatísticas da operação de inserção.
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Busca uma palavra na árvore.
     * * @param tree Ponteiro para a Árvore Rubro-Negra.
     * @param word A palavra a ser buscada.
     * @return Estrutura SearchResult com o resultado (encontrado ou não), 
     * a lista de IDs de documentos e as estatísticas da busca.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief Libera toda a memória utilizada pela árvore.
     * * Percorre a árvore em pós-ordem para deletar todos os nós,
     * e por fim, libera o nó sentinela e a própria estrutura da árvore.
     * * @param tree Ponteiro para a Árvore Rubro-Negra a ser destruída.
     */
    void destroy(BinaryTree* tree);

} // namespace RBT

#endif // RBT_H
