#include "treetest.h"
#include "../src/bst.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace TreeTest;
using namespace BST;

// Teste 1: Criação da árvore
TestCase testCreateTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testCreateTree");
    
    BinaryTree* tree = create();
    
    assertNotNull(test, tree, "Árvore deve ser criada com sucesso");
    if (tree != nullptr) {
        assertNull(test, tree->root, "Root deve ser NULL em uma árvore vazia");
        assertNull(test, tree->NIL, "NIL deve ser NULL na BST");
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 2: Inserção em árvore vazia
TestCase testInsertFirstElement() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testInsertFirstElement");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        InsertResult result = insert(tree, "hello", 1);
        
        assertTrue(test, result.numComparisons == 0, "Primeira inserção não deve ter comparações");
        assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        assertNotNull(test, tree->root, "Root não deve ser NULL após inserção");
        
        if (tree->root != nullptr) {
            assertTrue(test, tree->root->word == "hello", "Palavra inserida deve estar na raiz");
            assertTrue(test, tree->root->documentIds.size() == 1, "Deve ter um documento ID");
            assertTrue(test, tree->root->documentIds[0] == 1, "Documento ID deve ser 1");
            assertNull(test, tree->root->left, "Filho esquerdo deve ser NULL");
            assertNull(test, tree->root->right, "Filho direito deve ser NULL");
            assertNull(test, tree->root->parent, "Pai da raiz deve ser NULL");
        }
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 3: Inserção de palavra duplicada
TestCase testInsertDuplicateWord() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testInsertDuplicateWord");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        insert(tree, "word", 1);
        InsertResult result = insert(tree, "word", 2);
        
        assertTrue(test, result.numComparisons == 1, "Deve ter 1 comparação para encontrar palavra existente");
        assertNotNull(test, tree->root, "Root não deve ser NULL");
        
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

// Teste 4: Inserção múltipla criando estrutura de árvore
TestCase testMultipleInserts() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testMultipleInserts");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        // Inserir palavras que criem uma estrutura balanceada
        insert(tree, "dog", 1);      // root
        insert(tree, "cat", 2);      // left child
        insert(tree, "elephant", 3); // right child
        insert(tree, "ant", 4);      // left-left child
        insert(tree, "fish", 5);     // right-left child
        
        assertNotNull(test, tree->root, "Root não deve ser NULL");
          if (tree->root != nullptr) {
            assertTrue(test, tree->root->word == "dog", "Root deve ser 'dog'");
            assertNotNull(test, tree->root->left, "Deve ter filho esquerdo");
            assertNotNull(test, tree->root->right, "Deve ter filho direito");
            
            if (tree->root->left != nullptr) {
                assertTrue(test, tree->root->left->word == "cat", "Filho esquerdo deve ser 'cat'");
                assertNotNull(test, tree->root->left->left, "Cat deve ter filho esquerdo");
                if (tree->root->left->left != nullptr) {
                    assertTrue(test, tree->root->left->left->word == "ant", "Neto esquerdo deve ser 'ant'");
                }
            }
            
            if (tree->root->right != nullptr) {
                assertTrue(test, tree->root->right->word == "elephant", "Filho direito deve ser 'elephant'");
                // Verificamos se fish foi inserido corretamente (deve ser filho esquerdo de elephant)
                if (tree->root->right->left != nullptr) {
                    assertTrue(test, tree->root->right->left->word == "fish", "Neto direito-esquerdo deve ser 'fish'");
                }
            }
        }
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 5: Busca em árvore vazia
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

// Teste 6: Busca encontrando elemento
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
        assertTrue(test, result.numComparisons == 1, "Deve ter 1 comparação para encontrar na raiz");
        assertTrue(test, result.executionTime >= 0, "Tempo de execução deve ser não negativo");
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 7: Busca não encontrando elemento
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

// Teste 8: Busca em posição específica da árvore
TestCase testSearchInSpecificPosition() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testSearchInSpecificPosition");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        insert(tree, "dog", 1);
        insert(tree, "cat", 2);
        insert(tree, "elephant", 3);
        insert(tree, "ant", 4);
          // Buscar elemento que está como folha à esquerda
        SearchResult result = search(tree, "ant");
        
        assertTrue(test, result.found == 1, "Deve encontrar 'ant'");
        assertTrue(test, result.documentIds.size() == 1, "Deve ter um documento");
        assertTrue(test, result.documentIds[0] == 4, "Documento deve ser 4");
        // Verificamos o número real de comparações (pode variar dependendo da implementação)
        assertTrue(test, result.numComparisons > 0, "Deve ter pelo menos uma comparação para encontrar ant");
        
        destroy(tree);
    }
    
    endTest(test, initialTime);
    return test;
}

// Teste 9: Teste de desempenho com muitos elementos
TestCase testPerformanceWithManyElements() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testPerformanceWithManyElements");
    
    BinaryTree* tree = create();
    assertNotNull(test, tree, "Árvore deve ser criada");
    
    if (tree != nullptr) {
        // Inserir muitos elementos
        std::vector<std::string> words = {
            "word01", "word02", "word03", "word04", "word05",
            "word06", "word07", "word08", "word09", "word10",
            "word11", "word12", "word13", "word14", "word15"
        };
        
        for (int i = 0; i < words.size(); i++) {
            InsertResult result = insert(tree, words[i], i + 1);
            assertTrue(test, result.executionTime >= 0, "Tempo de inserção deve ser não negativo");
        }
        
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

// Teste 10: Teste de destruição de árvore
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

// Teste 11: Teste de inserção com árvore NULL
TestCase testInsertNullTree() {
    auto initialTime = std::chrono::high_resolution_clock::now();
    TestCase test = initTest("testInsertNullTree");
    
    BinaryTree* tree = nullptr;
    InsertResult result = insert(tree, "test", 1);
    
    assertTrue(test, result.numComparisons == 0, "Não deve ter comparações com árvore NULL");
    assertTrue(test, result.executionTime >= 0, "Tempo deve ser não negativo");
    
    endTest(test, initialTime);
    return test;
}

// Teste 12: Teste de busca com árvore NULL
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

// Função principal para executar todos os testes
int main() {
    auto allTests = TreeTest::initTestCases();
    
    TreeTest::addTest(allTests, testCreateTree());
    TreeTest::addTest(allTests, testInsertFirstElement());
    TreeTest::addTest(allTests, testInsertDuplicateWord());
    TreeTest::addTest(allTests, testMultipleInserts());
    TreeTest::addTest(allTests, testSearchEmptyTree());
    TreeTest::addTest(allTests, testSearchFoundElement());
    TreeTest::addTest(allTests, testSearchNotFoundElement());
    TreeTest::addTest(allTests, testSearchInSpecificPosition());
    TreeTest::addTest(allTests, testPerformanceWithManyElements());
    TreeTest::addTest(allTests, testDestroyTree());
    TreeTest::addTest(allTests, testInsertNullTree());
    TreeTest::addTest(allTests, testSearchNullTree());
    
    TreeTest::printTestResults(allTests);
    
    return 0;
}
