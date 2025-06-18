#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <chrono>

#include "data.h"
#include "utils/bench_utils.h"
#include "utils/value_utils.h"
#include "utils/less_than.h"

namespace DATA {
    std::vector<std::vector<std::string>> readFiles(const std::string& dataPath, int numDocs, ReadDataStats& readStats, bool verbose = false){
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::filesystem::directory_entry> files;

        // 1. Listar os arquivos no diretório
        for (const auto& entry : std::filesystem::directory_iterator(dataPath)) {
            if (entry.is_regular_file()) {
                if (std::stoi(entry.path().filename().string()) < numDocs) {
                    files.push_back(entry);
                }
            }
        }

        // 2. Ordenar os arquivos pelo nome convertido para inteiro
        ValueUtils::heapSort(files, LessThan::intFile);

        // 3. Ler os arquivos na ordem correta
        std::vector<std::vector<std::string>> documentWords;
        for (const auto& entry : files) {
            if (verbose) std::cout << "Lendo arquivo: " << entry.path().string() << std::endl;
            std::ifstream file(entry.path());
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir o arquivo: " << entry.path().string() << std::endl;
                continue;
            }
            std::vector<std::string> words;
            std::string word;
            while (file >> word) {
                words.push_back(word);
            }
            ValueUtils::heapSort(words, LessThan::str);
            
            documentWords.push_back(words);
            file.close();
        }
        auto end = std::chrono::high_resolution_clock::now();
        readStats.totalReadTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        readStats.numDocs = numDocs;

        return documentWords;
    }
} // namespace DATA