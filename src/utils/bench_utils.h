// v1.1.0

#ifndef BENCH_UTILS_H
#define BENCH_UTILS_H

#include <vector>
#include <string>
#include <chrono>

/**
 * @struct GroupedStats
 * @brief Coletor de estatísticas básicas (min, máx, média, desvio‑padrão).
 *
 * Utilização típica:
 * @code
 *   GroupedStats g;
 *   g.add(3.5);
 *   g.add(2.1);
 *   double m   = g.mean();   // média
 *   double dev = g.stddev(); // desvio‑padrão
 * @endcode
 */
struct GroupedStats {
    long long count = 0;
    double sum = 0.0;
    double sum_sq = 0.0;
    double min;
    double max;

    void add(double stat);
    double mean() const;
    double stddev() const;
    void merge(GroupedStats stats);
};

/**
 * @struct RotationStats
 * @brief Contador de rotações executadas (árvores AVL/RBT).
 */
struct RotationStats {
    int LL;  // Left‑Left
    int RR; // Right‑Right
    int LR; // Left‑Right
    int RL; // Right‑Left
};

/**
 * @struct GroupedRotationStats
 * @brief Estatísticas agregadas de rotações (média, desv‑pad etc.).
 */
struct GroupedRotationStats{
    GroupedStats LL;
    GroupedStats RR;
    GroupedStats LR;
    GroupedStats RL;

    void add(RotationStats stat);
};

/**
 * @struct MemoryUsage
 * @brief Estimativa de uso de memória da estrutura indexada.
 *
 * - @p numBytes: total em bytes.
 * - @p scaleMultiplier: valor escalonado (KB, MB…)
 * - @p scale: unidade correspondente.
 */
struct MemoryUsage{
    long long numBytes;
    float scaleMultiplier;
    std::string scale;
};

/**
 * @struct ReadDataStats
 * @brief Métricas de leitura de documentos para indexação.
 */
struct ReadDataStats {
    double totalReadTime;
    long long numDocs;
};

/**
 * @struct IndexingStats
 * @brief Estatísticas globais do processo de indexação.
 */
struct IndexingStats {
    double totalIndexingTime; // tempo total
    GroupedStats depthStats; // profundidade dos nos
    GroupedStats comparisonStats; // comparações de chave
    GroupedStats recoloringStats; // recolorimentos
    GroupedRotationStats rotationStats; // rotacaoes executadas
    long long totalWordsProcessed; // n total de palavras
};

#endif // BENCH_UTILS_H