#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "bst.h"

namespace DATA {
    /**
     * @brief Ajuda o Heap‑Sort a manter a propriedade de max‑heap.
     *
     * Chamado recursivamente por ::sortFilesByName.
     *
     * @param files   Vetor de entradas retornadas por `std::filesystem`.
     * @param n       Tamanho efetivo do heap.
     * @param i       Índice do nó atual.
     */
    void heapifyFiles(std::vector<std::filesystem::directory_entry>& files, int n, int i);
    /**
     * @brief Ajuda o Heap‑Sort a manter a propriedade de max‑heap para palavras.
     *
     * Chamado recursivamente por ::sortWords.
     *
     * @param words   Vetor de palavras a ser ordenado.
     * @param n       Tamanho efetivo do heap.
     * @param i       Índice do nó atual.
     */
    void heapifyWords(std::vector<std::string>& words, int n, int i);
    /**
     * @brief Ordena `files` in‑place pelo nome do arquivo convertido em inteiro.
     * @param files Vetor de `directory_entry` que será reorganizado.
     */
    void sortFilesByName(std::vector<std::filesystem::directory_entry>& files);
    /**
     * @brief Ordena `words` in‑place pelo tamanho da palavra (maior para menor).
     * @param words Vetor de palavras que será reorganizado.
     */
    void sortWords(std::vector<std::string>& words);
    /**
     * @brief Lê até `numDocs` arquivos de `dataPath` e devolve um vetor de palavras.
     *
     * O algoritmo executa as seguintes etapas:
     * 1. **Varredura** – percorre o diretório e guarda apenas os arquivos cujo nome,
     *    interpretado como inteiro, seja menor que `numDocs`.
     * 2. **Ordenação** – chama ::sortFilesByName para garantir ordem ascendente.
     * 3. **Leitura** – abre cada arquivo, faz split por whitespace e guarda as
     *    palavras em `documentWords[i]`.
     *
     * @param dataPath Caminho do diretório que contém os documentos (apenas texto).
     * @param numDocs  Número máximo de arquivos (0 ≤ nome < numDocs).
     * @param verbose  Se `true`, imprime no `stdout` o nome de cada arquivo lido.
     * @return `std::vector` cujo tamanho é o número de arquivos efetivamente
     *         lidos; cada elemento é um vetor de palavras (`std::string`).
     */
    std::vector<std::vector<std::string>> readFiles(const std::string& dataPath, int numDocs, bool verbose = false);
} // namespace DATA
#endif // DATA_H