// v1.0.2

#ifndef LESS_THAN_H
#define LESS_THAN_H

#include <string>
#include <filesystem>


namespace LessThan {
    bool str(const std::string& left, const std::string& right);
    bool intFile(const std::filesystem::directory_entry& left, const std::filesystem::directory_entry& right);
    template<typename T>
    bool standard(const T& left, const T& right);
}

#endif // LESS_THAN_H