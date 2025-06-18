// Versão simplificada para testes
#ifndef BST_SIMPLE_H
#define BST_SIMPLE_H

#include <string>
#include <vector>
#include <chrono>

#include "tree_utils_simple.h"

namespace BST {

BinaryTree* create();
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
SearchResult search(BinaryTree* tree, const std::string& word);
void destroy(BinaryTree *tree);

} // namespace BST

#endif // BST_SIMPLE_H
