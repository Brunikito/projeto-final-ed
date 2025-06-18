#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "../src/bst.h"
#include "../src/utils/bench_utils.h"

// Funcao para gerar palavras de teste
std::vector<std::string> generateWords(int n) {
    std::vector<std::string> words;
    for (int i = 0; i < n; ++i) {
        words.push_back("word" + std::to_string(i));
    }
    return words;
}

// Benchmark: Insercao
void benchmarkBSTInsert(int numWords, int numRuns) {
    GroupedStats stats;
    auto words = generateWords(numWords);

    for (int run = 0; run < numRuns; ++run) {
        BinaryTree* tree = BST::create();
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numWords; ++i) {
            BST::insert(tree, words[i], i);
        }

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        stats.add(duration);
        BST::destroy(tree);
    }

    std::cout << "\n[Benchmark] BST Insert (" << numWords << " words, " << numRuns << " runs):\n";
    std::cout << "Media: " << stats.mean() << " ms | Desvio: " << stats.stddev() << " ms | Min: " << stats.min << " ms | Max: " << stats.max << " ms\n";
}

// Benchmark: Busca
void benchmarkBSTSearch(int numWords, int numRuns) {
    GroupedStats stats;
    auto words = generateWords(numWords);

    for (int run = 0; run < numRuns; ++run) {
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
        stats.add(duration);
        BST::destroy(tree);
    }

    std::cout << "\n[Benchmark] BST Search (" << numWords << " words, " << numRuns << " runs):\n";
    std::cout << "Media: " << stats.mean() << " ms | Desvio: " << stats.stddev() << " ms | Min: " << stats.min << " ms | Max: " << stats.max << " ms\n";
}

int main() {
    int numWords = 10000;
    int numRuns = 5;

    benchmarkBSTInsert(numWords, numRuns);
    benchmarkBSTSearch(numWords, numRuns);

    return 0;
}
