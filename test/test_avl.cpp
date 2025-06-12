#include "treetest.h"
#include "../src/avl.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace TreeTest;
using namespace AVL;

// Função auxiliar para verificar se a árvore está balanceada (AVL)
int checkAVL(Node* node, bool& isBalanced) {
    if (!node) return -1;
    int lh = checkAVL(node->left, isBalanced);
    int rh = checkAVL(node->right, isBalanced);
    if (std::abs(rh - lh) > 1) isBalanced = false;
    return std::max(rh, lh) + 1;
}

// Teste 1: Rotação simples à esquerda
TestCase testRotationLeft() {
    auto initialTime = std::chrono::high_resolution_clock::now();

    TestCase test = initTest("testSingleRotationLeft");
    BinaryTree* tree = create();
    insert(tree, "a", 1);
    insert(tree, "b", 2);
    insert(tree, "c", 3); // Deve causar rotação à esquerda

    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    assertTrue(test, isBalanced, "A árvore deve estar balanceada após rotação à esquerda");
    assertNotNull(test, tree->root, "Raiz não deve ser nula");
    if (tree->root) {
        assertTrue(test, tree->root->word == "b", "Raiz deve ser 'b'");
        assertNotNull(test, tree->root->left, "Filho esquerdo não deve ser nulo");
        assertNotNull(test, tree->root->right, "Filho direito não deve ser nulo");
        if (tree->root->left) assertTrue(test, tree->root->left->word == "a", "Filho esquerdo deve ser 'a'");
        if (tree->root->right) assertTrue(test, tree->root->right->word == "c", "Filho direito deve ser 'c'");
    }
    destroy(tree);
    endTest(test, initialTime);
    return test;
}

// Teste 2: Rotação simples à direita
TestCase testRotationRight() {
    auto initialTime = std::chrono::high_resolution_clock::now();

    TestCase test = initTest("testSingleRotationRight");
    BinaryTree* tree = create();
    insert(tree, "c", 1);
    insert(tree, "b", 2);
    insert(tree, "a", 3); // Deve causar rotação à direita

    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    assertTrue(test, isBalanced, "A árvore deve estar balanceada após rotação à direita");
    assertNotNull(test, tree->root, "Raiz não deve ser nula");
    if (tree->root) {
        assertTrue(test, tree->root->word == "b", "Raiz deve ser 'b'");
        if (tree->root->left) assertTrue(test, tree->root->left->word == "a", "Filho esquerdo deve ser 'a'");
        if (tree->root->right) assertTrue(test, tree->root->right->word == "c", "Filho direito deve ser 'c'");
    }
    destroy(tree);
    endTest(test, initialTime);
    return test;
}



// Teste 3: Rotação dupla esquerda-direita
TestCase testDoubleRotationLeftRight() {
    auto initialTime = std::chrono::high_resolution_clock::now();

    TestCase test = initTest("testDoubleRotationLeftRight");
    BinaryTree* tree = create();
    insert(tree, "c", 1);
    insert(tree, "a", 2);
    insert(tree, "b", 3); // Deve causar rotação dupla esquerda-direita

    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    assertTrue(test, isBalanced, "A árvore deve estar balanceada após rotação dupla esquerda-direita");
    assertNotNull(test, tree->root, "Raiz não deve ser nula");
    if (tree->root) {
        assertTrue(test, tree->root->word == "b", "Raiz deve ser 'b'");
        if (tree->root->left) assertTrue(test, tree->root->left->word == "a", "Filho esquerdo deve ser 'a'");
        if (tree->root->right) assertTrue(test, tree->root->right->word == "c", "Filho direito deve ser 'c'");
    }
    destroy(tree);
    endTest(test, initialTime);
    return test;
}

// Teste 4: Rotação dupla direita-esquerda
TestCase testDoubleRotationRightLeft() {
    auto initialTime = std::chrono::high_resolution_clock::now();

    TestCase test = initTest("testDoubleRotationRightLeft");
    BinaryTree* tree = create();
    insert(tree, "a", 1);
    insert(tree, "c", 2);
    insert(tree, "b", 3); // Deve causar rotação dupla direita-esquerda

    bool isBalanced = true;
    checkAVL(tree->root, isBalanced);
    assertTrue(test, isBalanced, "A árvore deve estar balanceada após rotação dupla direita-esquerda");
    assertNotNull(test, tree->root, "Raiz não deve ser nula");
    if (tree->root) {
        assertTrue(test, tree->root->word == "b", "Raiz deve ser 'b'");
        if (tree->root->left) assertTrue(test, tree->root->left->word == "a", "Filho esquerdo deve ser 'a'");
        if (tree->root->right) assertTrue(test, tree->root->right->word == "c", "Filho direito deve ser 'c'");
    }
    destroy(tree);
    endTest(test, initialTime);
    return test;
}

// Teste 5: Criação da árvore
TestCase testCreateTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testCreateTree");
    
    BinaryTree* tree = create();
    
    assertNotNull(test, tree, "Árvore deve ser criada com sucesso");
    if (tree != nullptr) {
        assertNull(test, tree->root, "Root deve ser NULL em uma árvore vazia");
        assertNull(test, tree->NIL, "NIL deve ser NULL na AVL");
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 6: Inserção em árvore vazia
TestCase testInsertFirstElement() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testInsertFirstElement");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        InsertResult result = insert(tree, "hello", 1);
        
        assertTrue(test, result.numComparisons >= 0, "Número de comparações deve ser não negativo");
        assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        assertNotNull(test, tree->root, "Root não deve ser NULL após inserção");
        
        if (tree->root != nullptr) {
            assertTrue(test, tree->root->word == "hello", "Palavra inserida deve estar na raiz");
            assertTrue(test, tree->root->documentIds.size() == 1, "Deve ter um documento ID");
            assertTrue(test, tree->root->documentIds[0] == 1, "Documento ID deve ser 1");
            assertNull(test, tree->root->left, "Filho esquerdo deve ser NULL");
            assertNull(test, tree->root->right, "Filho direito deve ser NULL");
            assertNull(test, tree->root->parent, "Pai da raiz deve ser NULL");
            assertTrue(test, tree->root->height == 1, "Altura deve ser 1");
        }
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Função principal para executar todos os testes de balanceamento AVL
int main() {
    auto allTests = TreeTest::initTestCases();

    TreeTest::addTest(allTests, testRotationLeft());
    TreeTest::addTest(allTests, testRotationRight());
    TreeTest::addTest(allTests, testDoubleRotationLeftRight());
    TreeTest::addTest(allTests, testDoubleRotationRightLeft());
    TreeTest::addTest(allTests, testCreateTree());
    TreeTest::addTest(allTests, testInsertFirstElement());

    TreeTest::printTestResults(allTests);

    return 0;
}