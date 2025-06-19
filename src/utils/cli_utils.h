// v1.0.1

#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <vector>

#include "tree_utils.h"
#include "bench_utils.h"
#include "value_utils.h"

/**
 * @brief Exibe o menu de opções para o modo de estatísticas.
 */
void displayStatsMenu(const std::string& arvore, int n_docs);

/**
 * @brief Imprime um relatório formatado com as estatísticas coletadas.
 */
void printStatsReport(const IndexStats& stats, const ReadDataStats& readStats);

/**
 * @brief Executa o modo de busca interativa.
 *
 * Esta função primeiro lê os arquivos, indexa as palavras na árvore fornecida
 * e, em seguida, permite que o usuário busque palavras interativamente.
 */
void searchTree(BinaryTree* tree, const TreeOperations& ops, const std::string& arvore, const std::string& command, int n_docs, const std::string& filesDir);

/**
 * @brief Executa o modo de estatísticas com um menu interativo.
 *
 * Permite ao usuário carregar dados, executar a indexação, ver um relatório
 * de desempenho detalhado e visualizar a árvore.
 */
void runStats(BinaryTree* tree, const TreeOperations& ops, const std::string& arvore, const std::string& comand, int n_docs_inicial, const std::string& filesDir);
#endif // CLI_UTILS_H