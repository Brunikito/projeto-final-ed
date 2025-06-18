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
    auto readData = DATA::readFiles("../data", 10'000, stats);
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
    // finished the benchmark for all Words.


    return 0;
}


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

int main() {
    int numWords = 10000;
    int numRuns = 5;

    std::vector<std::tuple<std::string, int, int, double>> results;

    benchmarkBSTInsert(numWords, numRuns, results);
    benchmarkBSTSearch(numWords, numRuns, results);

    saveResultsToCSV(results, "bst_benchmark_results.csv");

    std::cout << "Benchmark concluído! Resultados salvos em 'bst_benchmark_results.csv'.\n";

    return 0;
}
