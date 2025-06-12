#include "../src/avl.h"
#include <iostream>
#include <string>

using namespace AVL;

// Função auxiliar para verificar se a árvore está balanceada (AVL)
int checkAVL(Node* node, bool& isBalanced) {
    if (!node) return -1;
    int lh = checkAVL(node->left, isBalanced);
    int rh = checkAVL(node->right, isBalanced);
    if (std::abs(rh - lh) > 1) isBalanced = false;
    return std::max(rh, lh) + 1;
}

int main() {
    std::cout << "Testando AVL..." << std::endl;
    
    // Teste básico de criação
    BinaryTree* tree = create();
    if (tree == nullptr) {
        std::cout << "ERRO: Falha na criação da árvore" << std::endl;
        return 1;
    }
    std::cout << "✓ Árvore criada com sucesso" << std::endl;
    
    // Teste de inserção básica
    InsertResult result1 = insert(tree, "b", 1);
    if (tree->root == nullptr || tree->root->word != "b") {
        std::cout << "ERRO: Falha na inserção do primeiro elemento" << std::endl;
        return 1;
    }
    std::cout << "✓ Primeira inserção realizada" << std::endl;
    
    // Teste de rotação à esquerda
    insert(tree, "a", 1);
    insert(tree, "c", 1);
    insert(tree, "d", 1); // Deve causar rotação
    
    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    if (!isBalanced) {
        std::cout << "ERRO: Árvore não está balanceada após inserções" << std::endl;
        return 1;
    }
    std::cout << "✓ Árvore permanece balanceada após inserções" << std::endl;
    
    // Teste de busca
    SearchResult searchResult = search(tree, "b");
    if (searchResult.found != 1) {
        std::cout << "ERRO: Falha na busca de elemento existente" << std::endl;
        return 1;
    }
    std::cout << "✓ Busca funcionando corretamente" << std::endl;
    
    destroy(tree);
    std::cout << "✓ Árvore destruída com sucesso" << std::endl;
    
    std::cout << "Todos os testes básicos passaram!" << std::endl;
    return 0;
}
