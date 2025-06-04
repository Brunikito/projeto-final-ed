
// tests/unit/test_bst_index.cpp
// Compilar com: g++ -Wall -std=c++17 -o test_bst_index test_bst_index.cpp ../src/bst.cpp ../src/tree_utils.cpp
// Ambiente: Linux, g++ >= 7.3
// Pré-requisito: src/bst.cpp + headers adequados conforme projeto

#include <cassert>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include "../src/bst.h"
#include "../src/tree_utils.h"

// Utilitários para ordenação determinística nasserções
static std::vector<int> sorted(const std::vector<int>& v) {
    std::set<int> s(v.begin(), v.end());
    return std::vector<int>(s.begin(), s.end());
}

void setup(BinaryTree** tree) {
    *tree = BST_create();
}

void tearDown(BinaryTree** tree) {
    BST_destroy(*tree);
    *tree = nullptr;
}

// Testa criação de árvore vazia
void Teste_CriarArvoreVazia() {
    BinaryTree* tree = BST_create();
    assert(tree != nullptr);
    assert(tree->root == nullptr);
    BST_destroy(tree);
    std::cout << "Teste_CriarArvoreVazia: OK\n";
}

// Testa dupla inicialização e independência das árvores
void Teste_DuplaInicializacao() {
    BinaryTree* t1 = BST_create();
    BinaryTree* t2 = BST_create();
    BST_insert(t1, "laranja", 8);
    SearchResult r2 = BST_search(t2, "laranja");
    assert(!r2.found);
    BST_destroy(t1);
    BST_destroy(t2);
    std::cout << "Teste_DuplaInicializacao: OK\n";
}

void Teste_InsercaoPrimeiraPalavra() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "banana", 1);
    SearchResult r = BST_search(tree, "banana");
    assert(r.found && sorted(r.documentIds) == std::vector<int>({1}));
    BST_destroy(tree);
    std::cout << "Teste_InsercaoPrimeiraPalavra: OK\n";
}

void Teste_InsercaoPalavraNova() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "abacate", 2);
    SearchResult r = BST_search(tree, "abacate");
    assert(r.found && r.documentIds.size() == 1 && r.documentIds[0] == 2);
    BST_destroy(tree);
    std::cout << "Teste_InsercaoPalavraNova: OK\n";
}

void Teste_InsercaoRepetidaMesmoDoc() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "banana", 1);
    BST_insert(tree, "banana", 1);
    SearchResult r = BST_search(tree, "banana");
    assert(sorted(r.documentIds) == std::vector<int>({1})); // não duplica
    BST_destroy(tree);
    std::cout << "Teste_InsercaoRepetidaMesmoDoc: OK\n";
}

void Teste_InsercaoRepetidaOutroDoc() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "banana", 1);
    BST_insert(tree, "banana", 3);
    SearchResult r = BST_search(tree, "banana");
    assert(sorted(r.documentIds) == std::vector<int>({1,3}));
    BST_destroy(tree);
    std::cout << "Teste_InsercaoRepetidaOutroDoc: OK\n";
}

void Teste_InsercaoMultiplasPalavras() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "caju", 1);
    BST_insert(tree, "banana", 1);
    BST_insert(tree, "caju", 2);
    SearchResult r1 = BST_search(tree, "caju");
    SearchResult r2 = BST_search(tree, "banana");
    assert(sorted(r1.documentIds) == std::vector<int>({1,2}));
    assert(sorted(r2.documentIds) == std::vector<int>({1}));
    BST_destroy(tree);
    std::cout << "Teste_InsercaoMultiplasPalavras: OK\n";
}

void Teste_InsercaoCasoCaixaAltaPontuacao() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "Banana!", 2);
    SearchResult r = BST_search(tree, "banana");
    assert(r.found && sorted(r.documentIds) == std::vector<int>({2}));
    BST_destroy(tree);
    std::cout << "Teste_InsercaoCasoCaixaAltaPontuacao: OK\n";
}

void Teste_InsercaoBatchGrande() {
    BinaryTree* tree = BST_create();
    for(int i = 1; i <= 1000; ++i) {
        std::string s = "palavra_" + std::to_string(i);
        BST_insert(tree, s.c_str(), i);
    }
    int count = BST_count_nodes(tree);
    assert(count == 1000);
    BST_destroy(tree);
    std::cout << "Teste_InsercaoBatchGrande: OK\n";
}

void Teste_InsercaoVaziaOuNula() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "", 1); // deve ignorar/string vazia não indexada
    int count = BST_count_nodes(tree);
    assert(count == 0);
    BST_destroy(tree);
    std::cout << "Teste_InsercaoVaziaOuNula: OK\n";
}

void Teste_BuscaPalavraInserida() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "banana", 1);
    SearchResult r = BST_search(tree, "banana");
    assert(r.found && sorted(r.documentIds) == std::vector<int>({1}));
    BST_destroy(tree);
    std::cout << "Teste_BuscaPalavraInserida: OK\n";
}

void Teste_BuscaInexistente() {
    BinaryTree* tree = BST_create();
    SearchResult r = BST_search(tree, "tomate");
    assert(!r.found && r.documentIds.empty());
    BST_destroy(tree);
    std::cout << "Teste_BuscaInexistente: OK\n";
}

void Teste_BuscaPalavraTodosDocs() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "banana", 1);
    BST_insert(tree, "banana", 2);
    BST_insert(tree, "banana", 3);
    SearchResult r = BST_search(tree, "banana");
    assert(sorted(r.documentIds) == std::vector<int>({1,2,3}));
    BST_destroy(tree);
    std::cout << "Teste_BuscaPalavraTodosDocs: OK\n";
}

void Teste_BuscaArvoreVazia() {
    BinaryTree* tree = BST_create();
    SearchResult r = BST_search(tree, "qualquer");
    assert(!r.found && r.documentIds.size() == 0);
    BST_destroy(tree);
    std::cout << "Teste_BuscaArvoreVazia: OK\n";
}

void Teste_BuscaComVariacaoCasePontuacao() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "banana", 1);
    SearchResult r = BST_search(tree, "BaNaNA?");
    assert(r.found && r.documentIds[0] == 1);
    BST_destroy(tree);
    std::cout << "Teste_BuscaComVariacaoCasePontuacao: OK\n";
}

void Teste_PrintIndexArvorePopulada() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "banana",1);
    BST_insert(tree, "abacate",2);
    BST_insert(tree, "caju",3);
    std::cout << "== Teste_PrintIndexArvorePopulada (output esperado: ordem alfabetica com IDs)==\n";
    BST_printIndex(tree);
    BST_destroy(tree);
    std::cout << "Teste_PrintIndexArvorePopulada: OK\n";
}

void Teste_PrintIndexArvoreVazia() {
    BinaryTree* tree = BST_create();
    std::cout << "== Teste_PrintIndexArvoreVazia (nada ou aviso) ==\n";
    BST_printIndex(tree);
    BST_destroy(tree);
    std::cout << "Teste_PrintIndexArvoreVazia: OK\n";
}

void Teste_PrintTreePopulada() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "banana", 1);
    BST_insert(tree, "abacate", 2);
    BST_insert(tree, "caju", 3);
    std::cout << "== Teste_PrintTreePopulada (checar árbore BST printada) ==\n";
    BST_printTree(tree);
    BST_destroy(tree);
    std::cout << "Teste_PrintTreePopulada: OK\n";
}

void Teste_DestroyArvorePopulada() {
    BinaryTree* tree = BST_create();
    for(int i=0; i<10; i++) {
        std::string s = "pal_" + std::to_string(i);
        BST_insert(tree, s.c_str(), i);
    }
    BST_destroy(tree);
    assert(tree->root == nullptr || tree->root == NULL);
    std::cout << "Teste_DestroyArvorePopulada: OK\n";
}

void Teste_DestroyArvoreVazia() {
    BinaryTree* tree = BST_create();
    BST_destroy(tree);
    std::cout << "Teste_DestroyArvoreVazia: OK\n";
}

void Teste_Destroy2x() {
    BinaryTree* tree = BST_create();
    BST_destroy(tree);
    // Segunda chamada não deve crashar
    BST_destroy(tree);
    std::cout << "Teste_Destroy2x: OK\n";
}

void Teste_InsercaoPalavraRepetidaMultiplosDocs() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "alfa", 1);
    BST_insert(tree, "alfa", 2);
    BST_insert(tree, "alfa", 3);
    SearchResult r = BST_search(tree, "alfa");
    assert(sorted(r.documentIds) == std::vector<int>({1,2,3}));
    BST_destroy(tree);
    std::cout << "Teste_InsercaoPalavraRepetidaMultiplosDocs: OK\n";
}

void Teste_BuscaPalavraInexistente() {
    BinaryTree* tree = BST_create();
    SearchResult r = BST_search(tree, "palavraausente");
    assert(!r.found && r.documentIds.empty());
    BST_destroy(tree);
    std::cout << "Teste_BuscaPalavraInexistente: OK\n";
}

void Teste_BuscaPalavraEmUmDocApenas() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "unico", 29);
    SearchResult r = BST_search(tree, "unico");
    assert(r.found && r.documentIds.size()==1 && r.documentIds[0]==29);
    BST_destroy(tree);
    std::cout << "Teste_BuscaPalavraEmUmDocApenas: OK\n";
}

void Teste_BuscaPalavraEmVariosDocs() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "alfa", 1);
    BST_insert(tree, "alfa", 3);
    BST_insert(tree, "alfa", 5);
    SearchResult r = BST_search(tree, "alfa");
    assert(sorted(r.documentIds) == std::vector<int>({1,3,5}));
    BST_destroy(tree);
    std::cout << "Teste_BuscaPalavraEmVariosDocs: OK\n";
}

void Teste_BuscaArvoreDestruida() {
    BinaryTree* tree = BST_create();
    BST_insert(tree, "foo", 1);
    BST_destroy(tree);
    SearchResult r = BST_search(tree, "foo");
    assert(!r.found);
    std::cout << "Teste_BuscaArvoreDestruida: OK\n";
}

// =========================================================
// Função main para execução dos testes unitários BST
// =========================================================

int main() {
    Teste_CriarArvoreVazia();
    Teste_DuplaInicializacao();
    Teste_InsercaoPrimeiraPalavra();
    Teste_InsercaoPalavraNova();
    Teste_InsercaoRepetidaMesmoDoc();
    Teste_InsercaoRepetidaOutroDoc();
    Teste_InsercaoMultiplasPalavras();
    Teste_InsercaoCasoCaixaAltaPontuacao();
    Teste_InsercaoBatchGrande();
    Teste_InsercaoVaziaOuNula();
    Teste_BuscaPalavraInserida();
    Teste_BuscaInexistente();
    Teste_BuscaPalavraTodosDocs();
    Teste_BuscaArvoreVazia();
    Teste_BuscaComVariacaoCasePontuacao();
    Teste_PrintIndexArvorePopulada();
    Teste_PrintIndexArvoreVazia();
    Teste_PrintTreePopulada();
    Teste_DestroyArvorePopulada();
    Teste_DestroyArvoreVazia();
    Teste_Destroy2x();
    Teste_InsercaoPalavraRepetidaMultiplosDocs();
    Teste_BuscaPalavraInexistente();
    Teste_BuscaPalavraEmUmDocApenas();
    Teste_BuscaPalavraEmVariosDocs();
    Teste_BuscaArvoreDestruida();
    std::cout << "Todos os testes unitários de BST passaram!\n";
    return 0;
}
