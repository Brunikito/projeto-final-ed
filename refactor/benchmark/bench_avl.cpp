#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include "../src/avl.h" 
#include "../src/utils/bench_utils.h"

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
void benchmarkAVLInsert(int numWords, int numRuns, std::vector<std::tuple<std::string, int, int, double>>& results) {
    auto words = generateWords(numWords);

    for (int run = 1; run <= numRuns; ++run) {
        BinaryTree* tree = AVL::create();
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numWords; ++i) {
            AVL::insert(tree, words[i], i);
        }

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();

        results.emplace_back("insert", run, numWords, duration);

        AVL::destroy(tree);
    }
}

// Benchmark: Busca
void benchmarkAVLSearch(int numWords, int numRuns, std::vector<std::tuple<std::string, int, int, double>>& results) {
    auto words = generateWords(numWords);

    for (int run = 1; run <= numRuns; ++run) {
        BinaryTree* tree = AVL::create();
        for (int i = 0; i < numWords; ++i) {
            AVL::insert(tree, words[i], i);
        }

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numWords; ++i) {
            AVL::search(tree, words[i]);
        }

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();

        results.emplace_back("search", run, numWords, duration);

        AVL::destroy(tree);
    }
}

int main() {
    int numWords = 10000;
    int numRuns = 5;

    std::vector<std::tuple<std::string, int, int, double>> results;

    benchmarkAVLInsert(numWords, numRuns, results);
    benchmarkAVLSearch(numWords, numRuns, results);

    saveResultsToCSV(results, "avl_benchmark_results.csv");

    std::cout << "Benchmark concluído! Resultados salvos em 'avl_benchmark_results.csv'.\n";

    return 0;
}
