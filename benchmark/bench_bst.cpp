#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include "../src/bst.h"
#include "../src/utils/bench_utils.h"
#include "../src/utils/value_utils.h"
#include "../src/utils/tree_utils.h"
#include "../src/utils/less_than.h"
#include "../src/data.h"

int main() {
    return 0;
}
/*
std::vector<std::string> uniqueWords(BinaryTree* treeAllWords){
    if (treeAllWords == nullptr) return {};
    if (treeAllWords->root = treeAllWords->NIL) return {};
    std::vector<std::string> uniqueWords;
    Node* actualNode;
    std::vector<Node*> nodesToSearch = {treeAllWords->root};
    while (!nodesToSearch.empty()) {
        actualNode = nodesToSearch.back();
        nodesToSearch.pop_back();
        uniqueWords.push_back(actualNode->word);
        if (actualNode->left != treeAllWords->NIL) nodesToSearch.push_back(actualNode->left);
        if (actualNode->right != treeAllWords->NIL) nodesToSearch.push_back(actualNode->right);
    }
    ValueUtils::heapSort(uniqueWords, LessThan::str, true);
    return uniqueWords;
}

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
    std::vector<std::string> allWords = uniqueWords(treeAllWords);
    BST::destroy(treeAllWords);

    // Testando agora para todos os diferentes tamanhos
    std::vector<IndexingStats*> allIndexing;
    std::vector<TreeStats*> allTree;
    std::vector<GroupedStats*> allExecutionTime;
    std::vector<GroupedStats*> allComparisons;
    std::vector<GroupedStats*> allSearchDepth;
    IndexingStats actualIndexing;
    actualIndexing.totalIndexingTime = 0;
    GroupedStats actualExecutionTime;
    GroupedStats actualComparisons;
    GroupedStats actualSearchDepth;
    BinaryTree* actualTree = BST::create();
    for (int documentId = 0; documentId < readData.size(); documentId++) {
        auto start = std::chrono::high_resolution_clock::now();
        for (std::string word : readData[documentId]) {
            InsertResult result = BST::insert(treeAllWords, word, documentId);
            actualIndexing.comparisonStats.add(result.numComparisons);
            actualIndexing.depthStats.add(result.insertDepth);
            actualIndexing.recoloringStats.add(result.numRecoloring);
            actualIndexing.rotationStats.add(result.numRotations);
            actualIndexing.totalWordsProcessed++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        actualIndexing.totalIndexingTime += std::chrono::duration<double, std::micro>(end - start).count();
        IndexingStats* tempIndex = new IndexingStats;
        if (tempIndex == nullptr) return 0;
        tempIndex->comparisonStats = actualIndexing.comparisonStats;
        tempIndex->depthStats = actualIndexing.depthStats;
        tempIndex->recoloringStats = actualIndexing.recoloringStats;
        tempIndex->rotationStats.LL = actualIndexing.rotationStats.LL;
        tempIndex->rotationStats.RL = actualIndexing.rotationStats.RL;
        tempIndex->rotationStats.RR = actualIndexing.rotationStats.RR;
        tempIndex->rotationStats.LR = actualIndexing.rotationStats.LR;
        tempIndex->totalIndexingTime = actualIndexing.totalIndexingTime;
        tempIndex->totalWordsProcessed = actualIndexing.totalWordsProcessed;
        allIndexing.push_back(tempIndex);
        TreeStats* tempTree = new TreeStats;
        if (tempTree == nullptr) return 0;
        *tempTree = getTreeStats(actualTree);
        tempTree->type = BSTTree;
        allTree.push_back(tempTree);
        for (std::string word : allWords){
            SearchResult tempSR = BST::search(actualTree, word);
            actualExecutionTime.add(tempSR.executionTime);
            actualComparisons.add(tempSR.numComparisons);
            actualSearchDepth.add(tempSR.searchDepth);
        }
        GroupedStats* tempExecutionTime = new GroupedStats(actualExecutionTime);
        if (tempExecutionTime == nullptr) return 0;
        GroupedStats* tempComparisons = new GroupedStats(actualComparisons);
        if (tempComparisons == nullptr) return 0;
        GroupedStats* tempSearchDepth = new GroupedStats(actualSearchDepth);
        if (tempSearchDepth == nullptr) return 0;
        allExecutionTime.push_back(tempExecutionTime);
        allComparisons.push_back(tempComparisons);
        allSearchDepth.push_back(tempSearchDepth);
    }
    
    BST::destroy(actualTree);
    return 0;
}
*/
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