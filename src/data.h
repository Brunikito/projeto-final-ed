#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "bst.h"

namespace DATA {
    void heapifyFiles(std::vector<std::filesystem::directory_entry>& files, int n, int i);
    void sortFilesByName(std::vector<std::filesystem::directory_entry>& files);
    std::vector<std::vector<std::string>> readFiles(const std::string& dataPath, int numDocs, bool verbose = false);
} // namespace DATA
#endif // DATA_H