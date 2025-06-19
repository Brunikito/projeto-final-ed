#include "less_than.h"
#include <string>
#include <filesystem>

namespace LessThan {
    // comparação lexicográfica de strings
    bool str(const std::string& left, const std::string& right) {
        return left < right;
    }

    // compara arquivos pelo valor numérico do stem
    bool intFile(const std::filesystem::directory_entry& left, const std::filesystem::directory_entry& right){
        return std::stoi(left.path().stem().string()) < std::stoi(right.path().stem().string());
    }

    // delega ao operador < do tipo T
    template<typename T>
    bool standard(const T& left, const T& right) {
        return left < right;
    }
} // namespace LessThan