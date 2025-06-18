// v1.2.5

#ifndef RBT_H
#define RBT_H

#include <vector>
#include <string>

#include "utils/tree_utils.h"

namespace RBT {
    BinaryTree* create();
    int height(Node* node, Node* NIL, InsertResult& stats);
    void updateHeight(Node* node, Node* NIL, InsertResult& stats);
    void recursiveUpdateHeight(Node* node, Node* NIL, InsertResult& stats);
    Node* rightRotate(Node* y, Node* NIL, InsertResult& stats);
    Node* leftRotate(Node* y, Node* NIL, InsertResult& stats);
    Node* insertNode(BinaryTree* tree, const std::string& word, int documentId);
    void fixInsert(BinaryTree* tree, Node* insertedNode, InsertResult& stats);
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void destroyNode(Node* node, Node* NIL);
    void destroy(BinaryTree* tree);
}

#endif // RBT_H