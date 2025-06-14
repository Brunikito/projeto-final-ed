#include "lessThan.h"
#include <string>
#include <filesystem>

namespace LessThan {
    bool str(const std::string& left, const std::string& right) {
        return left < right;
    }

    bool intFile(const std::filesystem::directory_entry& left, const std::filesystem::directory_entry& right){
        return std::stoi(left.path().filename().string()) < std::stoi(right.path().filename().string());
    }

    template<typename T>
    bool standard(const T& left, const T& right) {
        return left < right;
    }
}