#ifndef AVL_H
#define AVL_H
#include <vector>
#include <string>
#include "tree_utils.h"

namespace AVL {
    BinaryTree* create();
    int height(Node* node);
    void updateHeight(Node* node);
    void recursiveUpdateHeight(Node* node, int& numComparisons);
    int getBalance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* y);
    Node* rebalance(Node* node, int& numComparisons);
    Node* insertNode(Node* root, const std::string& word, int documentId, InsertResult& stats);
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void destroyNode(Node* node);
    void destroy(BinaryTree* tree);
} // namespace AVL

#endif // AVL_H