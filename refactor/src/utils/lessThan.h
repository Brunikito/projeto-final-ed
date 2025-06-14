#ifndef LESS_THAN_H
#define LESS_THAN_H

#include <string>
#include <filesystem>


namespace LessThan {
    bool string(const std::string left, const std::string right);

    bool file(const std::filesystem::directory_entry& left, const std::filesystem::directory_entry& right);

    template<typename T>
    bool standart(const T& left, const T& right);
}

#endif // LESS_THAN_H