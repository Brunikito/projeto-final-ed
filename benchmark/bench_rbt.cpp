#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include "../src/rbt.h"
#include "../src/data.h"
#include "../src/utils/bench_utils.h"
#include "../src/utils/tree_utils.h"
#include "../src/utils/value_utils.h"

/**
 * @brief Percorre a árvore para extrair todas as palavras únicas.
 * @param tree A árvore RBT a ser percorrida.
 * @return Um vetor de strings contendo as palavras únicas.
 */
std::vector<std::string> get_unique_words(BinaryTree* tree) {
    if (!tree || !tree->root) {
        return {};
    }
    
    std::vector<std::string> words;
    std::vector<Node*> stack;
    Node* current = tree->root;

    // Travessia in-order para obter as palavras
    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push_back(current);
            current = current->left;
        }
        current = stack.back();
        stack.pop_back();
        words.push_back(current->word);
        current = current->right;
    }
    return words;
}

int main() {
    // 1. Definições do Benchmark
    const std::string data_path = "data";
    const std::string output_csv = "benchmark/results/rbt.csv";
    // Define o número máximo de documentos a processar.
    const int total_docs_to_process = 10000; 

    // 2. Leitura de todos os arquivos de uma vez para evitar I/O no loop
    std::cout << "Lendo arquivos de dados..." << std::endl;
    ReadDataStats read_stats;
    auto documents_words = DATA::readFiles(data_path, total_docs_to_process, read_stats, true);
    std::cout << read_stats.numDocs << " arquivos lidos com sucesso." << std::endl;

    // 3. Abrir arquivo CSV para escrita e inserir cabeçalho
    std::ofstream file(output_csv);
    if (!file.is_open()) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo para escrita: " << output_csv << std::endl;
        return 1;
    }

    file << "num_docs_processados,palavras_no_documento,"
         << "tempo_insercao_doc_ms,"
         << "comp_insercao_media,comp_insercao_desvpad,"
         << "prof_insercao_media,prof_insercao_desvpad,"
         << "altura_arvore,total_nos_arvore,"
         << "total_palavras_unicas_arvore,"
         << "tempo_busca_total_ms,"
         << "comp_busca_media,comp_busca_desvpad,"
         << "prof_busca_media,prof_busca_desvpad\n";

    // 4. Inicialização da árvore
    BinaryTree* tree = RBT::create();

    // 5. Loop de benchmark incremental
    std::cout << "Iniciando benchmark incremental..." << std::endl;
    for (int doc_id = 0; doc_id < (int)documents_words.size(); ++doc_id) {
        // Imprime o progresso na mesma linha
        std::cout << "Processando documento " << (doc_id + 1) << "/" << documents_words.size() << "...\r" << std::flush;
        
        const auto& current_doc_words = documents_words[doc_id];

        // Se o documento estiver vazio, pula para o próximo
        if (current_doc_words.empty()) {
            continue;
        }

        // --- A. Fase de Inserção (para o documento atual) ---
        GroupedStats insert_comps_step = {};
        GroupedStats insert_depth_step = {};
        double insert_time_step_us = 0.0;

        for (const auto& word : current_doc_words) {
            if (!word.empty()) {
                InsertResult i_res = RBT::insert(tree, word, doc_id);
                insert_comps_step.add(i_res.numComparisons);
                insert_depth_step.add(i_res.insertDepth);
                insert_time_step_us += i_res.executionTime;
            }
        }

        // --- B. Fase de Busca (para a árvore inteira) ---
        auto words_to_search = get_unique_words(tree);
        
        GroupedStats search_comps_stats = {};
        GroupedStats search_depth_stats = {};
        double search_total_time_us = 0.0;

        if (!words_to_search.empty()) {
             for (const auto& word : words_to_search) {
                SearchResult s_res = RBT::search(tree, word);
                search_total_time_us += s_res.executionTime;
                search_comps_stats.add(s_res.numComparisons);
                search_depth_stats.add(s_res.searchDepth);
            }
        }
       
        // --- C. Estatísticas gerais da árvore ---
        TreeStats tree_stats = getTreeStats(tree);

        // --- D. Escrever a linha de estatísticas no CSV ---
        std::string row_str = "";
        row_str += std::to_string(doc_id + 1) + ",";
        row_str += std::to_string(current_doc_words.size()) + ",";
        row_str += std::to_string(insert_time_step_us / 1000.0) + ",";
        row_str += std::to_string(insert_comps_step.mean()) + ",";
        row_str += std::to_string(insert_comps_step.stddev()) + ",";
        row_str += std::to_string(insert_depth_step.mean()) + ",";
        row_str += std::to_string(insert_depth_step.stddev()) + ",";
        row_str += std::to_string(tree_stats.height) + ",";
        row_str += std::to_string(tree_stats.totalNodes) + ",";
        row_str += std::to_string(words_to_search.size()) + ",";
        row_str += std::to_string(search_total_time_us / 1000.0) + ",";
        row_str += std::to_string(search_comps_stats.mean()) + ",";
        row_str += std::to_string(search_comps_stats.stddev()) + ",";
        row_str += std::to_string(search_depth_stats.mean()) + ",";
        row_str += std::to_string(search_depth_stats.stddev());

        file << row_str << "\n";
    }

    // 6. Finalização e Limpeza
    file.close();
    RBT::destroy(tree);
    std::cout << "\nBenchmark incremental concluido. Resultados salvos em " << output_csv << std::endl;

    return 0;
}