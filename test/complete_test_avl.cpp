#include "simple_treetest.h"
#include "../src/avl.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace AVL;

SimpleTestFramework framework;

// Função auxiliar para verificar se a árvore está balanceada (AVL)
int checkAVL(Node* node, bool& isBalanced) {
    if (!node) return -1;
    int lh = checkAVL(node->left, isBalanced);
    int rh = checkAVL(node->right, isBalanced);
    if (std::abs(rh - lh) > 1) isBalanced = false;
    return std::max(rh, lh) + 1;
}

// Teste 1: Criação da árvore
TestCase testCreateTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testCreateTree");
    
    BinaryTree* tree = create();
    
    framework.assertNotNull(test, tree, "Árvore deve ser criada com sucesso");
    if (tree != nullptr) {
        framework.assertNull(test, tree->root, "Root deve ser NULL em uma árvore vazia");
        framework.assertNull(test, tree->NIL, "NIL deve ser NULL na AVL");
        destroy(tree);
    }
    
    framework.endTest(test, initialTime);
    return test;
}

// Teste 2: Inserção em árvore vazia
TestCase testInsertFirstElement() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testInsertFirstElement");
    
    BinaryTree* tree = create();
    framework.assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        InsertResult result = insert(tree, "hello", 1);
        
        framework.assertTrue(test, result.numComparisons >= 0, "Número de comparações deve ser não negativo");
        framework.assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        framework.assertNotNull(test, tree->root, "Root não deve ser NULL após inserção");
        
        if (tree->root != nullptr) {
            framework.assertTrue(test, tree->root->word == "hello", "Palavra inserida deve estar na raiz");
            framework.assertTrue(test, tree->root->documentIds.size() == 1, "Deve ter um documento ID");
            framework.assertTrue(test, tree->root->documentIds[0] == 1, "Documento ID deve ser 1");
            framework.assertNull(test, tree->root->left, "Filho esquerdo deve ser NULL");
            framework.assertNull(test, tree->root->right, "Filho direito deve ser NULL");
            framework.assertNull(test, tree->root->parent, "Pai da raiz deve ser NULL");
            framework.assertTrue(test, tree->root->height == 1, "Altura deve ser 1");
        }
        
        destroy(tree);
    }
    
    framework.endTest(test, initialTime);
    return test;
}

// Teste 3: Rotação simples à esquerda
TestCase testRotationLeft() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testSingleRotationLeft");
    
    BinaryTree* tree = create();
    insert(tree, "a", 1);
    insert(tree, "b", 2);
    insert(tree, "c", 3); // Deve causar rotação à esquerda

    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    framework.assertTrue(test, isBalanced, "A árvore deve estar balanceada após rotação à esquerda");
    framework.assertNotNull(test, tree->root, "Raiz não deve ser nula");
    if (tree->root) {
        framework.assertTrue(test, tree->root->word == "b", "Raiz deve ser 'b'");
        framework.assertNotNull(test, tree->root->left, "Filho esquerdo não deve ser nulo");
        framework.assertNotNull(test, tree->root->right, "Filho direito não deve ser nulo");
        if (tree->root->left) framework.assertTrue(test, tree->root->left->word == "a", "Filho esquerdo deve ser 'a'");
        if (tree->root->right) framework.assertTrue(test, tree->root->right->word == "c", "Filho direito deve ser 'c'");
    }
    destroy(tree);
    framework.endTest(test, initialTime);
    return test;
}

// Teste 4: Rotação simples à direita
TestCase testRotationRight() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testSingleRotationRight");
    
    BinaryTree* tree = create();
    insert(tree, "c", 1);
    insert(tree, "b", 2);
    insert(tree, "a", 3); // Deve causar rotação à direita

    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    framework.assertTrue(test, isBalanced, "A árvore deve estar balanceada após rotação à direita");
    framework.assertNotNull(test, tree->root, "Raiz não deve ser nula");
    if (tree->root) {
        framework.assertTrue(test, tree->root->word == "b", "Raiz deve ser 'b'");
        if (tree->root->left) framework.assertTrue(test, tree->root->left->word == "a", "Filho esquerdo deve ser 'a'");
        if (tree->root->right) framework.assertTrue(test, tree->root->right->word == "c", "Filho direito deve ser 'c'");
    }
    destroy(tree);
    framework.endTest(test, initialTime);
    return test;
}

// Teste 5: Rotação dupla esquerda-direita
TestCase testDoubleRotationLeftRight() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testDoubleRotationLeftRight");
    
    BinaryTree* tree = create();
    insert(tree, "c", 1);
    insert(tree, "a", 2);
    insert(tree, "b", 3); // Deve causar rotação dupla esquerda-direita

    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    framework.assertTrue(test, isBalanced, "A árvore deve estar balanceada após rotação dupla esquerda-direita");
    framework.assertNotNull(test, tree->root, "Raiz não deve ser nula");
    if (tree->root) {
        framework.assertTrue(test, tree->root->word == "b", "Raiz deve ser 'b'");
        if (tree->root->left) framework.assertTrue(test, tree->root->left->word == "a", "Filho esquerdo deve ser 'a'");
        if (tree->root->right) framework.assertTrue(test, tree->root->right->word == "c", "Filho direito deve ser 'c'");
    }
    destroy(tree);
    framework.endTest(test, initialTime);
    return test;
}

// Teste 6: Rotação dupla direita-esquerda
TestCase testDoubleRotationRightLeft() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testDoubleRotationRightLeft");
    
    BinaryTree* tree = create();
    insert(tree, "a", 1);
    insert(tree, "c", 2);
    insert(tree, "b", 3); // Deve causar rotação dupla direita-esquerda

    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    framework.assertTrue(test, isBalanced, "A árvore deve estar balanceada após rotação dupla direita-esquerda");
    framework.assertNotNull(test, tree->root, "Raiz não deve ser nula");
    if (tree->root) {
        framework.assertTrue(test, tree->root->word == "b", "Raiz deve ser 'b'");
        if (tree->root->left) framework.assertTrue(test, tree->root->left->word == "a", "Filho esquerdo deve ser 'a'");
        if (tree->root->right) framework.assertTrue(test, tree->root->right->word == "c", "Filho direito deve ser 'c'");
    }
    destroy(tree);
    framework.endTest(test, initialTime);
    return test;
}

// Teste 7: Inserção de palavra duplicada
TestCase testInsertDuplicateWord() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testInsertDuplicateWord");
    
    BinaryTree* tree = create();
    framework.assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        insert(tree, "word", 1);
        InsertResult result = insert(tree, "word", 2);
        
        framework.assertTrue(test, result.numComparisons >= 1, "Deve ter pelo menos 1 comparação para encontrar palavra existente");
        framework.assertNotNull(test, tree->root, "Root não deve ser NULL");
        
        if (tree->root != nullptr) {
            framework.assertTrue(test, tree->root->documentIds.size() == 2, "Deve ter dois documentos IDs");
            framework.assertTrue(test, tree->root->documentIds[0] == 1, "Primeiro documento deve ser 1");
            framework.assertTrue(test, tree->root->documentIds[1] == 2, "Segundo documento deve ser 2");
        }
        
        destroy(tree);
    }
    
    framework.endTest(test, initialTime);
    return test;
}

// Teste 8: Busca em árvore vazia
TestCase testSearchEmptyTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testSearchEmptyTree");
    
    BinaryTree* tree = create();
    framework.assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        SearchResult result = search(tree, "nonexistent");
        
        framework.assertTrue(test, result.found == 0, "Não deve encontrar elemento em árvore vazia");
        framework.assertTrue(test, result.documentIds.size() == 0, "Lista de documentos deve estar vazia");
        framework.assertTrue(test, result.numComparisons == 0, "Não deve ter comparações em árvore vazia");
        framework.assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        
        destroy(tree);
    }
    
    framework.endTest(test, initialTime);
    return test;
}

// Teste 9: Busca encontrando elemento
TestCase testSearchFoundElement() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testSearchFoundElement");
    
    BinaryTree* tree = create();
    framework.assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        insert(tree, "apple", 1);
        insert(tree, "apple", 3);
        insert(tree, "banana", 2);
        
        SearchResult result = search(tree, "apple");
        
        framework.assertTrue(test, result.found == 1, "Deve encontrar elemento existente");
        framework.assertTrue(test, result.documentIds.size() == 2, "Deve retornar dois documentos");
        framework.assertTrue(test, result.documentIds[0] == 1, "Primeiro documento deve ser 1");
        framework.assertTrue(test, result.documentIds[1] == 3, "Segundo documento deve ser 3");
        framework.assertTrue(test, result.numComparisons >= 1, "Deve ter pelo menos uma comparação");
        framework.assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        
        destroy(tree);
    }
    
    framework.endTest(test, initialTime);
    return test;
}

// Teste 10: Busca não encontrando elemento
TestCase testSearchNotFoundElement() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testSearchNotFoundElement");
    
    BinaryTree* tree = create();
    framework.assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        insert(tree, "dog", 1);
        insert(tree, "cat", 2);
        insert(tree, "elephant", 3);
        
        SearchResult result = search(tree, "zebra");
        
        framework.assertTrue(test, result.found == 0, "Não deve encontrar elemento inexistente");
        framework.assertTrue(test, result.documentIds.size() == 0, "Lista de documentos deve estar vazia");
        framework.assertTrue(test, result.numComparisons > 0, "Deve ter pelo menos uma comparação");
        framework.assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        
        destroy(tree);
    }
    
    framework.endTest(test, initialTime);
    return test;
}

// Teste 11: Inserção múltipla criando estrutura de árvore
TestCase testMultipleInserts() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testMultipleInserts");
    
    BinaryTree* tree = create();
    framework.assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        // Inserir palavras que devem manter o balanceamento
        insert(tree, "dog", 1);
        insert(tree, "cat", 2);
        insert(tree, "elephant", 3);
        insert(tree, "ant", 4);
        insert(tree, "fish", 5);
        
        framework.assertNotNull(test, tree->root, "Root não deve ser NULL");
        
        // Verificar se a árvore está balanceada
        bool isBalanced = true;
        checkAVL(tree->root, isBalanced);
        framework.assertTrue(test, isBalanced, "Árvore deve estar balanceada após múltiplas inserções");
        
        destroy(tree);
    }
    
    framework.endTest(test, initialTime);
    return test;
}

// Teste 12: Teste de inserção com árvore NULL
TestCase testInsertNullTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testInsertNullTree");
    
    BinaryTree* tree = nullptr;
    InsertResult result = insert(tree, "test", 1);
    
    framework.assertTrue(test, result.numComparisons >= 1, "Deve ter pelo menos uma comparação para detectar árvore NULL");
    framework.assertTrue(test, result.executionTime >= 0, "Tempo deve ser não negativo");
    
    framework.endTest(test, initialTime);
    return test;
}

// Teste 13: Teste de busca com árvore NULL
TestCase testSearchNullTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = framework.initTest("testSearchNullTree");
    
    BinaryTree* tree = nullptr;
    SearchResult result = search(tree, "test");
    
    framework.assertTrue(test, result.found == 0, "Não deve encontrar em árvore NULL");
    framework.assertTrue(test, result.documentIds.size() == 0, "Lista deve estar vazia");
    framework.assertTrue(test, result.numComparisons == 0, "Não deve ter comparações");
    framework.assertTrue(test, result.executionTime >= 0, "Tempo deve ser não negativo");
    
    framework.endTest(test, initialTime);
    return test;
}

int main() {
    std::cout << "=== TESTES DA ARVORE AVL ===" << std::endl;
    
    // Executar todos os testes
    framework.runTest(testCreateTree());
    framework.runTest(testInsertFirstElement());
    framework.runTest(testRotationLeft());
    framework.runTest(testRotationRight());
    framework.runTest(testDoubleRotationLeftRight());
    framework.runTest(testDoubleRotationRightLeft());
    framework.runTest(testInsertDuplicateWord());
    framework.runTest(testSearchEmptyTree());
    framework.runTest(testSearchFoundElement());
    framework.runTest(testSearchNotFoundElement());
    framework.runTest(testMultipleInserts());
    framework.runTest(testInsertNullTree());
    framework.runTest(testSearchNullTree());
    
    framework.printSummary();
    
    return 0;
}
