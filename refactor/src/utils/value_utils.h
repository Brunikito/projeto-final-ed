#ifndef VALUE_UTILS_H
#define VALUE_UTILS_H

#include <vector>

namespace ValueUtils {
    template<typename T> 
    double sqrt(const T value);

    template<typename T>
    double mean(const std::vector<T>& arr);
    template<typename Iterator>
    double mean(Iterator begin, Iterator end);

    template<typename T>
    double var(const std::vector<T>& arr);
    template<typename Iterator>
    double var(Iterator begin, Iterator end);

    template<typename T>
    double stddev(const std::vector<T>& arr);
    template<typename Iterator>
    double stddev(Iterator begin, Iterator end);

    template<typename T, typename compareLT>
    void heapSort(std::vector<T>& arr, compareLT lt, bool ascending = true);
    template<typename Iterator, typename compareLT>
    void heapSort(Iterator begin, Iterator end, compareLT lt, bool ascending = true);
}

#endif // VALUE_UTILS_H