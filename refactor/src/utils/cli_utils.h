// v1.0.1

#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <vector>

#include "tree_utils.h"
#include "bench_utils.h"
#include "value_utils.h"

void searchTree(BinaryTree* tree, const TreeOperations& ops, const std::string& arvore, const std::string& command, int n_docs, const std::string& filesDir);
void runStats(BinaryTree* tree, const TreeOperations& ops, const std::string& arvore, const std::string& comand, int n_docs_inicial, const std::string& filesDir);
#endif // CLI_UTILS_H