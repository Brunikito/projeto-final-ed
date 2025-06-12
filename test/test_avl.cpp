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

// teste 3: Balanceamento
// Teste 3: Teste da função getBalance
TestCase testGetBalance() {
    auto initialTime = std::chrono::high_resolution_clock::now();

    TestCase test = initTest("testGetBalance");
    BinaryTree* tree = create();
    // Árvore:      b
    //            /   \
    //           a     c
    insert(tree, "b", 1);
    insert(tree, "a", 2);
    insert(tree, "c", 3);

    // O balanceamento da raiz deve ser 0 (mesma altura dos dois lados)
    int balanceRoot = getBalance(tree->root);
    assertTrue(test, balanceRoot == 0, "Balance da raiz deve ser 0");

    // O balanceamento do filho esquerdo (a) deve ser 0 (folha)
    if (tree->root->left)
        assertTrue(test, getBalance(tree->root->left) == 0, "Balance do filho esquerdo deve ser 0");

    // O balanceamento do filho direito (c) deve ser 0 (folha)
    if (tree->root->right)
        assertTrue(test, getBalance(tree->root->right) == 0, "Balance do filho direito deve ser 0");

    destroy(tree);
    endTest(test, initialTime);
    return test;
}

// Adicione no main:



// Teste 4: Teste da função height
TestCase testHeight() {
    auto initialTime = std::chrono::high_resolution_clock::now();

    TestCase test = initTest("testHeight");
    BinaryTree* tree = create();

    // Árvore:      b
    //            /   \
    //           a     c
    insert(tree, "b", 1);
    insert(tree, "a", 2);
    insert(tree, "c", 3);

    // A altura da raiz deve ser 1 (duas folhas abaixo)
    int hRoot = height(tree->root);
    assertTrue(test, hRoot == 1 || hRoot == 2, "Altura da raiz deve ser 1 ou 2 (dependendo da implementação)");

    // A altura das folhas deve ser 0
    if (tree->root->left)
        assertTrue(test, height(tree->root->left) == 0, "Altura do filho esquerdo deve ser 0");
    if (tree->root->right)
        assertTrue(test, height(tree->root->right) == 0, "Altura do filho direito deve ser 0");

    destroy(tree);
    endTest(test, initialTime);
    return test;
}

// Adicione no main:


// Teste 5: 


// Teste 4: Rotação dupla direita-esquerda

// Função principal para executar todos os testes de balanceamento AVL
int main() {
    auto allTests = TreeTest::initTestCases();

    TreeTest::addTest(allTests, testRotationLeft());
    TreeTest::addTest(allTests, testRotationRight());
    TreeTest::addTest(allTests, testGetBalance());
    TreeTest::addTest(allTests, testHeight());




    TreeTest::printTestResults(allTests);

    return 0;
}