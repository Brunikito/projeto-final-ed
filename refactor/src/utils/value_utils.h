// v2.0.0

#ifndef VALUE_UTILS_H
#define VALUE_UTILS_H

#include <vector>
#include <iostream>
#include <filesystem>

/**
/**
 * @namespace ValueUtils
 * @brief Funções utilitárias para manipulação de valores, estatísticas e ordenação.
 *
 * Este namespace fornece uma coleção de funções utilitárias com templates para:
 *   - Operações matemáticas básicas (max, abs, sqrt)
 *   - Cálculos estatísticos (mean, variance, standard deviation)
 *   - Algoritmos de ordenação baseados em heap (heapify, heapSort)
 *
 * Funções:
 * 
 * @tparam T Tipo dos valores de entrada ou elementos do container.
 * @tparam Iterator Tipo de iterador para intervalos genéricos.
 * @tparam compareLT Functor de comparação (ex.: std::less, std::greater).
 *
 * -------------------------------------------
 * @function max
 * @brief Retorna o maior entre dois valores.
 * @param value1 Primeiro valor.
 * @param value2 Segundo valor.
 * @return O maior dos dois valores.
 *
 * -------------------------------------------
 * @function abs
 * @brief Retorna o valor absoluto.
 * @param value Valor de entrada.
 * @return Valor absoluto da entrada.
 *
 * -------------------------------------------
 * @function sqrt
 * @brief Calcula a raiz quadrada usando o método de Newton-Raphson.
 * @param value Valor de entrada (deve ser não negativo).
 * @return Raiz quadrada da entrada. Retorna -1 e imprime uma mensagem de erro se o valor for negativo.
 *
 * -------------------------------------------
 * @function mean (versão com vetor)
 * @brief Calcula a média (média aritmética) de um vetor.
 * @param arr Vetor de entrada.
 * @return Média dos elementos.
 *
 * @function mean (versão com iteradores)
 * @brief Calcula a média (média aritmética) de um intervalo genérico.
 * @param begin Iterador para o início do intervalo.
 * @param end Iterador para o fim do intervalo.
 * @return Média dos elementos no intervalo.
 *
 * -------------------------------------------
 * @function var
 * @brief Calcula a variância de um vetor ou intervalo de iteradores.
 * @param arr Vetor de elementos. (Para a primeira sobrecarga)
 * @param begin Iterador para o início. (Para a segunda sobrecarga)
 * @param end Iterador para o fim.
 * @return Variância dos elementos.
 *
 * -------------------------------------------
 * @function stddev
 * @brief Calcula o desvio padrão.
 * @param arr Vetor de elementos. (Para a primeira sobrecarga)
 * @param begin Iterador para o início. (Para a segunda sobrecarga)
 * @param end Iterador para o fim.
 * @return Desvio padrão dos elementos.
 *
 * -------------------------------------------
 * @function heapify
 * @brief Mantém a propriedade de heap em um índice específico.
 * @param arr Vetor (para a primeira sobrecarga) ou intervalo de iteradores (para a segunda sobrecarga).
 * @param n Número de elementos no heap.
 * @param i Índice atual onde será aplicado o heapify.
 * @param lt Functor de comparação (define a regra de prioridade).
 * @param ascending Se verdadeiro, constrói um max-heap (ordem crescente); se falso, constrói um min-heap (ordem decrescente).
 *
 * -------------------------------------------
 * @function heapSort
 * @brief Ordena os elementos usando o algoritmo de heap sort.
 * @param arr Vetor (para a primeira sobrecarga) ou intervalo de iteradores (para a segunda sobrecarga).
 * @param lt Functor de comparação.
 * @param ascending Direção da ordenação: true = ordem crescente, false = ordem decrescente.
 */


namespace ValueUtils {

    template<typename T>
    T max(const T& value1, const T& value2) { return value1 > value2 ? value1 : value2; }

    template<typename T>
    T abs(const T& value) { return max(value, -value); }

    template<typename T> 
    double sqrt(const T& value) {
        if (value < 0) {
            std::cerr << "Value must be non-negative." << std::endl;
            return -1;
        }
        if (value == 0) return 0;
        
        double x = static_cast<double>(value);
        double guess = x;
        double tolerance = 1e-16;
        double diff = 1.0;
        double new_guess;

        while (diff > tolerance) {
            new_guess = (guess + x / guess) / 2.0;
            diff = abs(guess - new_guess);
            guess = new_guess;
        }

        return guess;
    }

    template<typename T>
    double mean(const std::vector<T>& arr) {
        double total = 0;
        size_t num_elements = arr.size();
        if (num_elements == 0) return 0;
        
        for (const T& element : arr) {
            total += static_cast<double>(element);
        }
        
        return total / num_elements;
    }

    template<typename Iterator>
    double mean(Iterator begin, Iterator end) {
        double total = 0;
        size_t num_elements = std::distance(begin, end);
        if (num_elements == 0) return 0;
        
        for (Iterator iter = begin; iter != end; ++iter) {
            total += static_cast<double>(*iter);
        }
        
        return total / num_elements;
    }

    template<typename T>
    double var(const std::vector<T>& arr){
        size_t num_elements = arr.size();
        if (num_elements == 0) return 0;
        double mean_value = mean(arr);
        double sum_squares = 0;
        for (const T& element : arr){
            sum_squares += static_cast<double>(element*element);
        }
        return (sum_squares/num_elements) - (mean_value*mean_value);
    }

    template<typename Iterator>
    double var(Iterator begin, Iterator end) {
        size_t num_elements = std::distance(begin, end);
        if (num_elements == 0) return 0;
        double mean_value = mean(begin, end);
        double sum_squares = 0;
        for (Iterator it = begin; it != end; ++it) {
            sum_squares += static_cast<double>((*it) * (*it));
        }
        return (sum_squares / num_elements) - (mean_value * mean_value);
    }

    template<typename T>
    double stddev(const std::vector<T>& arr) { return sqrt(var(arr)); }

    template<typename Iterator>
    double stddev(Iterator begin, Iterator end) { return sqrt(var(begin, end)); }

    template<typename T, typename compareLT>
    void heapify(std::vector<T>& arr, size_t n, size_t i, compareLT lt, bool ascending){
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (ascending) { // max-heap
            if (left < n && lt(arr[largest], arr[left])) {
                largest = left;
            }
            if (right < n && lt(arr[largest], arr[right])) {
                largest = right;
            }
        } else { // min-heap
            if (left < n && !lt(arr[largest], arr[left])) {
                largest = left;
            }
            if (right < n && !lt(arr[largest], arr[right])) {
                largest = right;
            }
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest, lt, ascending);
        }
    }

    template<typename Iterator, typename compareLT>
    void heapify(Iterator begin, Iterator end, size_t n, size_t i, compareLT lt, bool ascending){
        Iterator left = begin + 2 * i + 1;
        Iterator right = begin + 2 * i + 2;
        Iterator largest = begin + i;

        if (ascending) { // max-heap
            if (left < end && lt(*largest, *left)) {
                largest = left;
            }
            if (right < end && lt(*largest, *right)) {
                largest = right;
            }
        } else { // min-heap
            if (left < end && !lt(*largest, *left)) {
                largest = left;
            }
            if (right < end && !lt(*largest, *right)) {
                largest = right;
            }
        }

        if (largest != begin + i) {
            std::swap(*largest, *(begin + i));
            heapify(begin, end, n, largest - begin, lt, ascending);
        }
    }

    template<typename T, typename compareLT>
    void heapSort(std::vector<T>& arr, compareLT lt, bool ascending = true){
        size_t num_elements = arr.size();
        for (size_t i = num_elements / 2 - 1; i >= 0; i--) {
            heapify(arr, num_elements, i, lt, ascending);
        }
        for (size_t i = num_elements - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0, lt, ascending);
        }
    }

    template<typename Iterator, typename compareLT>
    void heapSort(Iterator begin, Iterator end, compareLT lt, bool ascending = true) {
        size_t num_elements = std::distance(begin, end);
        for (size_t i = num_elements / 2 - 1; i >= 0; i--) {
            heapify(begin, end, num_elements, i, lt, ascending);
        }
        for (size_t i = num_elements - 1; i > 0; i--) {
            std::swap(*begin, *(begin + i));
            heapify(begin, end, i, 0, lt, ascending);
        }
    }
}

#endif // VALUE_UTILS_H
