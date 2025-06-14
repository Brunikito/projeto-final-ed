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

// Teste 7: Inserção de palavra duplicada
TestCase testInsertDuplicateWord() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testInsertDuplicateWord");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        insert(tree, "word", 1);
        InsertResult result = insert(tree, "word", 2);
        
        assertTrue(test, result.numComparisons >= 1, "Deve ter pelo menos 1 comparação para encontrar palavra existente");
        assertNotNull(test, tree->root, "Raiz não deve ser nula");
        
        if (tree->root != nullptr) {
            assertTrue(test, tree->root->documentIds.size() == 2, "Deve ter dois documentos IDs");
            assertTrue(test, tree->root->documentIds[0] == 1, "Primeiro documento deve ser 1");
            assertTrue(test, tree->root->documentIds[1] == 2, "Segundo documento deve ser 2");
        }
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 8: Busca em árvore vazia
TestCase testSearchEmptyTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testSearchEmptyTree");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        SearchResult result = search(tree, "nonexistent");
        
        assertTrue(test, result.found == 0, "Não deve encontrar elemento em árvore vazia");
        assertTrue(test, result.documentIds.size() == 0, "Lista de documentos deve estar vazia");
        assertTrue(test, result.numComparisons == 0, "Não deve ter comparações em árvore vazia");
        assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 9: Busca encontrando elemento
TestCase testSearchFoundElement() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testSearchFoundElement");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        insert(tree, "apple", 1);
        insert(tree, "apple", 3);
        insert(tree, "banana", 2);
        
        SearchResult result = search(tree, "apple");
        
        assertTrue(test, result.found == 1, "Deve encontrar elemento existente");
        assertTrue(test, result.documentIds.size() == 2, "Deve retornar dois documentos");
        assertTrue(test, result.documentIds[0] == 1, "Primeiro documento deve ser 1");
        assertTrue(test, result.documentIds[1] == 3, "Segundo documento deve ser 3");
        assertTrue(test, result.numComparisons >= 1, "Deve ter pelo menos uma comparação");
        assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 10: Busca não encontrando elemento
TestCase testSearchNotFoundElement() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testSearchNotFoundElement");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        insert(tree, "dog", 1);
        insert(tree, "cat", 2);
        insert(tree, "elephant", 3);
        
        SearchResult result = search(tree, "zebra");
        
        assertTrue(test, result.found == 0, "Não deve encontrar elemento inexistente");
        assertTrue(test, result.documentIds.size() == 0, "Lista de documentos deve estar vazia");
        assertTrue(test, result.numComparisons > 0, "Deve ter pelo menos uma comparação");
        assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 11: Inserção múltipla criando estrutura de árvore
TestCase testMultipleInserts() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testMultipleInserts");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        // Inserir palavras que devem manter o balanceamento
        insert(tree, "dog", 1);
        insert(tree, "cat", 2);
        insert(tree, "elephant", 3);
        insert(tree, "ant", 4);
        insert(tree, "fish", 5);
        
        assertNotNull(test, tree->root, "Root não deve ser NULL");
        
        // Verificar se a árvore está balanceada
        bool isBalanced = true;
        checkAVL(tree->root, isBalanced);
        assertTrue(test, isBalanced, "Árvore deve estar balanceada após múltiplas inserções");
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 12: Teste de inserção com árvore NULL
TestCase testInsertNullTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testInsertNullTree");
    
    BinaryTree* tree = nullptr;
    InsertResult result = insert(tree, "test", 1);
    
    assertTrue(test, result.numComparisons >= 1, "Deve ter pelo menos uma comparação para detectar árvore NULL");
    assertTrue(test, result.executionTime >= 0, "Tempo deve ser não negativo");
    
    endTest(test, initialTime);
    return test;
}

// Teste 13: Teste de busca com árvore NULL
TestCase testSearchNullTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testSearchNullTree");
    
    BinaryTree* tree = nullptr;
    SearchResult result = search(tree, "test");
    
    assertTrue(test, result.found == 0, "Não deve encontrar em árvore NULL");
    assertTrue(test, result.documentIds.size() == 0, "Lista deve estar vazia");
    assertTrue(test, result.numComparisons == 0, "Não deve ter comparações");
    assertTrue(test, result.executionTime >= 0, "Tempo deve ser não negativo");
    
    endTest(test, initialTime);
    return test;
}

// Teste 14: Teste de desempenho com muitos elementos
TestCase testPerformanceWithManyElements() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testPerformanceWithManyElements");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        // Inserir muitos elementos para testar o balanceamento
        std::vector<std::string> words = {
            "word01", "word02", "word03", "word04", "word05",
            "word06", "word07", "word08", "word09", "word10",
            "word11", "word12", "word13", "word14", "word15",
            "word16", "word17", "word18", "word19", "word20"
        };
        
        for (int i = 0; i < words.size(); i++) {
            InsertResult result = insert(tree, words[i], i + 1);
            assertTrue(test, result.executionTime >= 0, "Tempo de inserção deve ser não negativo");
        }
        
        // Verificar se a árvore ainda está balanceada
        bool isBalanced = true;
        int height = checkAVL(tree->root, isBalanced);
        assertTrue(test, isBalanced, "Árvore deve permanecer balanceada com muitos elementos");
        
        // Altura de uma AVL com 20 elementos deve ser aproximadamente log2(20) ≈ 4-5
        assertTrue(test, height <= 6, "Altura da árvore deve ser logarítmica");
        
        // Buscar alguns elementos
        SearchResult result1 = search(tree, "word01");
        assertTrue(test, result1.found == 1, "Deve encontrar word01");
        
        SearchResult result2 = search(tree, "word15");
        assertTrue(test, result2.found == 1, "Deve encontrar word15");
        
        SearchResult result3 = search(tree, "nonexistent");
        assertTrue(test, result3.found == 0, "Não deve encontrar palavra inexistente");
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 15: Teste de balanceamento em sequência ordenada
TestCase testBalancingOrderedSequence() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testBalancingOrderedSequence");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        // Inserir elementos em ordem para forçar rebalanceamentos
        insert(tree, "item1", 1);
        insert(tree, "item2", 2);
        insert(tree, "item3", 3);
        insert(tree, "item4", 4);
        insert(tree, "item5", 5);
        
        // Verificar balanceamento final
        bool isBalanced = true;
        checkAVL(tree->root, isBalanced);
        assertTrue(test, isBalanced, "Árvore deve estar balanceada após inserção em sequência ordenada");
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 16: Teste de destruição de árvore
TestCase testDestroyTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testDestroyTree");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        // Adicionar alguns elementos
        insert(tree, "test1", 1);
        insert(tree, "test2", 2);
        insert(tree, "test3", 3);
        
        // A função destroy deve ser chamada sem causar crash
        // Não há muito o que testar aqui além de não travar
        destroy(tree);
        assertTrue(test, true, "Destruição da árvore deve ser bem-sucedida");
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 17: Teste específico de todas as rotações AVL
TestCase testAllRotationTypes() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testAllRotationTypes");
    
    // Teste de rotação simples à esquerda (caso LL)
    BinaryTree* tree1 = create();
    insert(tree1, "1", 1);
    insert(tree1, "2", 2);
    insert(tree1, "3", 3);
    bool isBalanced1 = true;
    checkAVL(tree1->root, isBalanced1);
    assertTrue(test, isBalanced1, "Rotação LL deve manter árvore balanceada");
    destroy(tree1);
    
    // Teste de rotação simples à direita (caso RR)
    BinaryTree* tree2 = create();
    insert(tree2, "3", 1);
    insert(tree2, "2", 2);
    insert(tree2, "1", 3);
    bool isBalanced2 = true;
    checkAVL(tree2->root, isBalanced2);
    assertTrue(test, isBalanced2, "Rotação RR deve manter árvore balanceada");
    destroy(tree2);
    
    // Teste de rotação dupla esquerda-direita (caso LR)
    BinaryTree* tree3 = create();
    insert(tree3, "3", 1);
    insert(tree3, "1", 2);
    insert(tree3, "2", 3);
    bool isBalanced3 = true;
    checkAVL(tree3->root, isBalanced3);
    assertTrue(test, isBalanced3, "Rotação LR deve manter árvore balanceada");
    destroy(tree3);
    
    // Teste de rotação dupla direita-esquerda (caso RL)
    BinaryTree* tree4 = create();
    insert(tree4, "1", 1);
    insert(tree4, "3", 2);
    insert(tree4, "2", 3);
    bool isBalanced4 = true;
    checkAVL(tree4->root, isBalanced4);
    assertTrue(test, isBalanced4, "Rotação RL deve manter árvore balanceada");
    destroy(tree4);
    
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
    TreeTest::addTest(allTests, testInsertDuplicateWord());
    TreeTest::addTest(allTests, testSearchEmptyTree());
    TreeTest::addTest(allTests, testSearchFoundElement());
    TreeTest::addTest(allTests, testSearchNotFoundElement());
    TreeTest::addTest(allTests, testMultipleInserts());
    TreeTest::addTest(allTests, testInsertNullTree());
    TreeTest::addTest(allTests, testSearchNullTree());
    TreeTest::addTest(allTests, testPerformanceWithManyElements());
    TreeTest::addTest(allTests, testBalancingOrderedSequence());
    TreeTest::addTest(allTests, testDestroyTree());
    TreeTest::addTest(allTests, testAllRotationTypes());

    TreeTest::printTestResults(allTests);

    return 0;
}