// v1.1.0

#ifndef LESS_THAN_H
#define LESS_THAN_H

#include <string>
// #include <filesystem> // Compatibilidade GCC 6.3.0


namespace LessThan {
    bool str(const std::string& left, const std::string& right);
    // bool intFile(const std::filesystem::directory_entry& left, const std::filesystem::directory_entry& right); // Comentado
    template<typename T>
    bool standard(const T& left, const T& right);
}

#endif // LESS_THAN_H