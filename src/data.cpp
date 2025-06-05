#include "data.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

namespace DATA {
    // Função para ordenar os arquivos por nome usando o algoritmo Heap Sort
    void heapifyFiles(std::vector<std::filesystem::directory_entry>& files, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && std::stoi(files[left].path().filename().string()) > std::stoi(files[largest].path().filename().string()))
            largest = left;
        if (right < n && std::stoi(files[right].path().filename().string()) > std::stoi(files[largest].path().filename().string()))
            largest = right;
        if (largest != i) {
            std::swap(files[i], files[largest]);
            heapifyFiles(files, n, largest);
        }
    }
    void heapifyWords(std::vector<std::string>& words, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && words[left].size() > words[largest].size())
            largest = left;
        if (right < n && words[right].size() > words[largest].size())
            largest = right;
        if (largest != i) {
            std::swap(words[i], words[largest]);
            heapifyWords(words, n, largest);
        }
    }
    void sortWords(std::vector<std::string>& words) {
        int n = words.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyWords(words, n, i);
        for (int i = n - 1; i > 0; i--) {
            std::swap(words[0], words[i]);
            heapifyWords(words, i, 0);
        }
    }
    // Função para ordenar os arquivos por nome usando o algoritmo Heap Sort
    void sortFilesByName(std::vector<std::filesystem::directory_entry>& files) {
        int n = files.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyFiles(files, n, i);
        for (int i = n - 1; i > 0; i--) {
            std::swap(files[0], files[i]);
            heapifyFiles(files, i, 0);
        }

    }
    // Função para ler os arquivos de um diretório e retornar o conteúdo em um vetor de vetores de strings
    std::vector<std::vector<std::string>> readFiles(const std::string& dataPath, int numDocs, bool verbose){
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
        sortFilesByName(files);

        // 3. Ler os arquivos na ordem correta
        std::vector<std::vector<std::string>> documentWords(files.size());
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
            sortWords(words);
            for (int i = 1; i < words.size(); ++i) {
                // Remove palavras duplicadas
                // (mantém apenas a primeira ocorrência)
                if (words[i] == words[i - 1]) {
                    words.erase(words.begin() + i);
                    --i;
                }
            }
            documentWords.push_back(words);
            file.close();
        }

        return documentWords;
    }
} // namespace DATA