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



// Teste 4: Rotação dupla direita-esquerda

// Função principal para executar todos os testes de balanceamento AVL
int main() {
    auto allTests = TreeTest::initTestCases();

    TreeTest::addTest(allTests, testRotationLeft());
    TreeTest::addTest(allTests, testRotationRight());


    TreeTest::printTestResults(allTests);

    return 0;
}