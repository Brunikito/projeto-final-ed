// v2.1.0

#ifndef AVL_H
#define AVL_H
#include <vector>
#include <string>
#include "utils/tree_utils.h"

namespace AVL {
    BinaryTree* create();
    int height(Node* node, InsertResult& stats);
    void updateHeight(Node* node, InsertResult& stats);
    void recursiveUpdateHeight(Node* node, InsertResult& stats);
    int getBalance(Node* node, InsertResult& stats);
    Node* rightRotate(Node* y, InsertResult& stats);
    Node* leftRotate(Node* y, InsertResult& stats);
    Node* rebalance(Node* node, InsertResult& stats);
    Node* insertNode(Node* root, const std::string& word, int documentId, InsertResult& stats);
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void destroyNode(Node* node);
    void destroy(BinaryTree* tree);
} // namespace AVL

#endif // AVL_H