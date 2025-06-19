// v1.1.0

#ifndef LESS_THAN_H
#define LESS_THAN_H

#include <string>
#include <filesystem>


namespace LessThan {
    /**
     * @brief Comparação lexicográfica de @c std::string.
     * @return @c true se @p left é lexicograficamente menor que @p right.
     */
    bool str(const std::string& left, const std::string& right);
    
    /**
     * @brief Compara entradas de diretório pela parte numérica do nome do arquivo.
     *
     * Converte o @c stem (nome sem extensão) de cada @p directory_entry para um
     * inteiro via @c std::stoi antes da comparação. Exemplo prático: garantir que
     * «10.txt» venha depois de «2.txt» quando ordenado.
     */
    bool intFile(const std::filesystem::directory_entry& left, const std::filesystem::directory_entry& right);
    template<typename T>

    /**
     * @brief Comparador genérico que delega ao operador < do tipo.
     *
     * Útil como predicado padrão quando não é necessário tratamento especial.
     */
    bool standard(const T& left, const T& right);
} // namespace LessThan

#endif // LESS_THAN_H