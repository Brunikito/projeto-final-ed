#define AVL_H
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "tree_utils.h"

namespace AVL {


    BinaryTree* create();

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    SearchResult search(BinaryTree* tree, const std::string& word);

    void destroy(BinaryTree* tree);

}