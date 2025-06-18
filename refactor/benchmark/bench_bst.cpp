#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include "../src/bst.h"
#include "../src/utils/bench_utils.h"
#include "../src/data.h"

int main() {
    ReadDataStats stats;
    auto readData = DATA::readFiles("../data", 10'000, stats, false);
    IndexingStats indexAllWordsStats;
    auto start = std::chrono::high_resolution_clock::now();
    BinaryTree* treeAllWords = BST::create();
    for (int documentId = 0; documentId < readData.size(); documentId++) {
        for (std::string word : readData[documentId]) {
            InsertResult result = BST::insert(treeAllWords, word, documentId);
            indexAllWordsStats.comparisonStats.add(result.numComparisons);
            indexAllWordsStats.depthStats.add(result.insertDepth);
            indexAllWordsStats.recoloringStats.add(result.numRecoloring);
            indexAllWordsStats.rotationStats.add(result.numRotations);
            indexAllWordsStats.totalWordsProcessed++;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    indexAllWordsStats.totalIndexingTime = std::chrono::duration<double, std::micro>(end - start).count();
    // Exibe estatísticas de indexação
    std::cout << "==== Estatisticas de Indexacao (Todas as Palavras) ====\n";
    std::cout << "Total de palavras processadas: " << indexAllWordsStats.totalWordsProcessed << "\n";
    std::cout << "Tempo total de indexacao (microssegundos): " << indexAllWordsStats.totalIndexingTime << "\n";

    std::cout << "\nComparacoes:\n";
    std::cout << "  Total: " << indexAllWordsStats.comparisonStats.sum << "\n";
    std::cout << "  Media: " << indexAllWordsStats.comparisonStats.mean() << "\n";
    std::cout << "  Desvio padrao: " << indexAllWordsStats.comparisonStats.stddev() << "\n";

    std::cout << "\nProfundidade de insercao:\n";
    std::cout << "  Media: " << indexAllWordsStats.depthStats.mean() << "\n";
    std::cout << "  Desvio padrao: " << indexAllWordsStats.depthStats.stddev() << "\n";

    std::cout << "\nRecolorimentos:\n";
    std::cout << "  Total: " << indexAllWordsStats.recoloringStats.sum << "\n";
    std::cout << "  Media: " << indexAllWordsStats.recoloringStats.mean() << "\n";
    std::cout << "  Desvio padrao: " << indexAllWordsStats.recoloringStats.stddev() << "\n";

    std::cout << "\nRotacoes LL:\n";
    std::cout << "  Total: " << indexAllWordsStats.rotationStats.LL.sum << "\n";
    std::cout << "  Media: " << indexAllWordsStats.rotationStats.LL.mean() << "\n";
    std::cout << "  Desvio padrao: " << indexAllWordsStats.rotationStats.LL.stddev() << "\n";

    std::cout << "\nRotacoes RR:\n";
    std::cout << "  Total: " << indexAllWordsStats.rotationStats.RR.sum << "\n";
    std::cout << "  Media: " << indexAllWordsStats.rotationStats.RR.mean() << "\n";
    std::cout << "  Desvio padrao: " << indexAllWordsStats.rotationStats.RR.stddev() << "\n";

    std::cout << "\nRotacoes LR:\n";
    std::cout << "  Total: " << indexAllWordsStats.rotationStats.LR.sum << "\n";
    std::cout << "  Media: " << indexAllWordsStats.rotationStats.LR.mean() << "\n";
    std::cout << "  Desvio padrao: " << indexAllWordsStats.rotationStats.LR.stddev() << "\n";

    std::cout << "\nRotacoes RL:\n";
    std::cout << "  Total: " << indexAllWordsStats.rotationStats.RL.sum << "\n";
    std::cout << "  Media: " << indexAllWordsStats.rotationStats.RL.mean() << "\n";
    std::cout << "  Desvio padrao: " << indexAllWordsStats.rotationStats.RL.stddev() << "\n";

    BST::destroy(treeAllWords);
    return 0;
}

/*
// Função para gerar palavras de teste
std::vector<std::string> generateWords(int n) {
    std::vector<std::string> words;
    for (int i = 0; i < n; ++i) {
        words.push_back("word" + std::to_string(i));
    }
    return words;
}

// Salva os resultados no CSV
void saveResultsToCSV(const std::vector<std::tuple<std::string, int, int, double>>& results, const std::string& filename) {
    std::ofstream file(filename);

    // Cabeçalho
    file << "Benchmark,Run,NumWords,Duration_ms\n";

    for (const auto& row : results) {
        file << std::get<0>(row) << "," << std::get<1>(row) << "," << std::get<2>(row) << "," << std::get<3>(row) << "\n";
    }

    file.close();
}

// Benchmark: Inserção
void benchmarkBSTInsert(int numWords, int numRuns, std::vector<std::tuple<std::string, int, int, double>>& results) {
    auto words = generateWords(numWords);

    for (int run = 1; run <= numRuns; ++run) {
        BinaryTree* tree = BST::create();
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numWords; ++i) {
            BST::insert(tree, words[i], i);
        }

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();

        results.emplace_back("insert", run, numWords, duration);

        BST::destroy(tree);
    }
}

// Benchmark: Busca
void benchmarkBSTSearch(int numWords, int numRuns, std::vector<std::tuple<std::string, int, int, double>>& results) {
    auto words = generateWords(numWords);

    for (int run = 1; run <= numRuns; ++run) {
        BinaryTree* tree = BST::create();
        for (int i = 0; i < numWords; ++i) {
            BST::insert(tree, words[i], i);
        }

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numWords; ++i) {
            BST::search(tree, words[i]);
        }

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();

        results.emplace_back("search", run, numWords, duration);

        BST::destroy(tree);
    }
}
*/