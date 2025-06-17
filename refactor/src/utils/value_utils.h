// v1.0.0

#ifndef VALUE_UTILS_H
#define VALUE_UTILS_H

#include <vector>

namespace ValueUtils {
    template<typename T>
    T abs(const T value);

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
    void heapify(std::vector<T>& arr, size_t n, size_t i, compareLT lt, bool ascending = true);
    template<typename Iterator, typename compareLT>
    void heapify(Iterator begin, Iterator end, size_t n, size_t i, compareLT lt, bool ascending = true);

    template<typename T, typename compareLT>
    void heapSort(std::vector<T>& arr, compareLT lt, bool ascending = true);
    template<typename Iterator, typename compareLT>
    void heapSort(Iterator begin, Iterator end, compareLT lt, bool ascending = true);
}

#endif // VALUE_UTILS_H