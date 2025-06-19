// v2.1.0

#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>

#include "utils/bench_utils.h"

namespace DATA {
    /**
     * @brief Lê arquivos de texto de um diretório e devolve as palavras ordenadas.
     *
     * Fluxo de trabalho (implementado em *data.cpp*):
     *   1. Lista arquivos em @p dataPath cujo nome numérico seja menor que @p numDocs.
     *   2. Ordena‐os numericamente ("2.txt", "10.txt" etc.).
     *   3. Para cada arquivo:
     *        - lê palavra a palavra,
     *        - ordena as palavras lexicograficamente,
     *        - adiciona ao vetor de documentos.
     *   4. Preenche @p readStats com tempo total de leitura (µs) e nº de docs.
     *
     * @param dataPath Diretório contendo os arquivos.
     * @param numDocs  Máx. de documentos a carregar.
     * @param readStats Estrutura a ser preenchida com estatísticas de I/O.
     * @param verbose  Se @c true, imprime o nome de cada arquivo lido.
     *
     * @return Vetor onde cada elemento é uma lista ordenada de palavras do doc.
     */
    std::vector<std::vector<std::string>> readFiles(const std::string& dataPath, int numDocs, ReadDataStats& readStats, bool verbose);
} // namespace DATA

#endif // DATA_Hss