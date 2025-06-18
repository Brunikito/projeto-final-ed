// v2.0.1

#ifndef BST_H
#define BST_H

#include <string>
#include <vector>
#include <chrono>

#include "utils/tree_utils.h"

namespace BST {

BinaryTree* create();
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
SearchResult search(BinaryTree* tree, const std::string& word);
void destroy(BinaryTree *tree);

} // namespace BST

#endif // BST_H
