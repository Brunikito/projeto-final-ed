    #ifndef BST_H
    #define BST_H

    #include <string>
    #include <vector>
    #include <chrono>

    namespace BST {

    struct Node {
        std::string word;
        std::vector<int> documentIds;
        Node* parent;
        Node* left;
        Node* right;
        int height;    // não usado na BST
        int isRed;     // não usado na BST
    };

    struct BinaryTree {
        Node* root;
        Node* NIL; // não usado na BST
    };

    struct InsertResult {
        int numComparisons;
        double executionTime;
    };

    struct SearchResult {
        int found;
        std::vector<int> documentIds;
        double executionTime;
        int numComparisons;
    };

        BinaryTree* create();
        InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
        SearchResult search(BinaryTree* tree, const std::string& word);
        void destroy(BinaryTree* tree);

    } // namespace BST

    #endif // BST_H
