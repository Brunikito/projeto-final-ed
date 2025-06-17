// v2.0.0

#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>

#include "utils/bench_utils.h"

namespace DATA {
    std::vector<std::vector<std::string>> readFiles(const std::string& dataPath, int numDocs, ReadDataStats& readStats, bool verbose = false);
} // namespace DATA
#endif // DATA_H