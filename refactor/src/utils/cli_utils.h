#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <vector>

#include "tree_utils.h"
#include "bench_utils.h"
#include "value_utils.h"

/*
 * ## TODO ##
 * -> Melhorar a experiência do usuário (UX)
 * -> Implementar as novas métricas de benchmark
 * 
 * Obs.1: se implementadas, as funções
 * printSearchResult() e printSearchStats()
 * devem ser implementadas aqui.
 * Se tiverem dúvidas quanto a isso, eu ainda 
 * não removi a implementação antiga. 
 * Basta compreender os utils novos e corrigir.
 * Além disso, podem entrar em contato comigo.
 * 
 * Obs.2: aqui eu coloquei apenas um exemplo do
 * código anterior. Sinta-se livre para refatorá-lo.
 * Não é necessário implementar exatamente essas funções.
 * 
 * Boa Sorte!
 * Ass.: Brunikito
*/
void printSearchResult(const SearchResult& result, const std::string& word);
void printSearchStats(const SearchResult& result);
void searchTree(const TreeOperations& ops, const std::string& arvore, const std::string& command, int n_docs, const std::string& directoryFiles);
void runStats(const TreeOperations& ops, const std::string& arvore, const std::string& comand, int n_docs_inicial, const std::string& directoryFiles);
#endif // CLI_UTILS_H