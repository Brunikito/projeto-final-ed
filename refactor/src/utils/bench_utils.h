// v1.1.1

#ifndef BENCH_UTILS_H
#define BENCH_UTILS_H

#include <vector>
#include <string>
#include <chrono>

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

struct RotationStats {
    int LL;
    int RR;
    int LR;
    int RL;
};

struct GroupedRotationStats{
    GroupedStats LL;
    GroupedStats RR;
    GroupedStats LR;
    GroupedStats RL;

    void add(RotationStats stat);
};

struct MemoryUsage{
    long long numBytes;
    float scaleMultiplier;
    std::string scale;
};

struct ReadDataStats {
    double totalReadTime;
    long long numDocs;
};

struct IndexingStats {
    double totalIndexingTime;
    GroupedStats depthStats;
    GroupedStats comparisonStats;
    GroupedStats recoloringStats;
    GroupedRotationStats rotationStats;
    long long totalWordsProcessed;
};

#endif // BENCH_UTILS_H