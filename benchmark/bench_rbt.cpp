#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include "../src/rbt.h"
#include "../src/data.h"
#include "../src/utils/bench_utils.h"
#include "../src/utils/tree_utils.h"

/**
 * @brief Percorre a árvore para extrair todas as palavras únicas de forma eficiente.
 * @param tree A árvore RBT a ser percorrida.
 * @return Um vetor de strings contendo as palavras únicas.
 */
std::vector<std::string> get_unique_words(BinaryTree* tree) {
    if (tree == nullptr || tree->root == tree->NIL) {
        return {};
    }
    
    std::vector<std::string> words;
    std::vector<Node*> stack;
    Node* current = tree->root;

    // Travessia in-order iterativa, segura com o nó sentinela NIL.
    while (current != tree->NIL || !stack.empty()) {
        while (current != tree->NIL) {
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
    const std::string data_path = "./data"; // Ajuste o caminho se necessário
    const std::string output_csv = "rbt_benchmark_results.csv";
    // Define o número máximo de documentos a processar.
    const int total_docs_to_process = 3000; 
    // Define o passo para o benchmark incremental (processa 1, depois mais 9, etc.)
    const int step_size = 10;

    // 2. Leitura de todos os arquivos de uma vez para evitar I/O no loop
    std::cout << "Lendo arquivos de dados..." << std::endl;
    ReadDataStats read_stats;
    auto documents_words = DATA::readFiles(data_path, total_docs_to_process, read_stats, true);
    std::cout << read_stats.numDocs << " arquivos lidos com sucesso." << std::endl;

    if (documents_words.empty()) {
        std::cerr << "ERRO: Nenhum documento foi lido. Verifique o caminho '" << data_path << "'" << std::endl;
        return 1;
    }

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
    for (int doc_id = 0; doc_id < (int)documents_words.size(); doc_id++) {
        // Imprime o progresso na mesma linha
        std::cout << "Processando documento " << (doc_id + 1) << "/" << documents_words.size() << "...\r" << std::flush;
        
        const auto& current_doc_words = documents_words[doc_id];

        // --- A. Fase de Inserção (para o documento atual) ---
        GroupedStats insert_comps_step;
        GroupedStats insert_depth_step;
        double insert_time_step_us = 0.0;

        for (const auto& word : current_doc_words) {
            if (!word.empty()) {
                InsertResult i_res = RBT::insert(tree, word, doc_id);
                insert_comps_step.add(i_res.numComparisons);
                insert_depth_step.add(i_res.insertDepth);
                insert_time_step_us += i_res.executionTime;
            }
        }

        // --- B. Realizar a fase de busca apenas em intervalos definidos pelo step_size ---
        if ((doc_id + 1) % step_size == 0 || (doc_id + 1) == documents_words.size()) {
            
            // --- B1. Fase de Busca (para a árvore inteira) ---
            auto words_to_search = get_unique_words(tree);
            
            GroupedStats search_comps_stats;
            GroupedStats search_depth_stats;
            double search_total_time_us = 0.0;

            if (!words_to_search.empty()) {
                 for (const auto& word : words_to_search) {
                    // Usa a função de busca padrão para benchmark
                    SearchResult s_res = RBT::search(tree, word);
                    search_total_time_us += s_res.executionTime;
                    search_comps_stats.add(s_res.numComparisons);
                    search_depth_stats.add(s_res.searchDepth);
                 }
            }
            
            // --- B2. Estatísticas gerais da árvore ---
            TreeStats tree_stats = getTreeStats(tree);

            // --- B3. Escrever a linha de estatísticas no CSV ---
            file << (doc_id + 1) << ",";
            file << current_doc_words.size() << ",";
            file << (insert_time_step_us / 1000.0) << ","; // convertendo para ms
            file << insert_comps_step.mean() << ",";
            file << insert_comps_step.stddev() << ",";
            file << insert_depth_step.mean() << ",";
            file << insert_depth_step.stddev() << ",";
            file << tree_stats.height << ",";
            file << tree_stats.totalNodes << ",";
            file << words_to_search.size() << ",";
            file << (search_total_time_us / 1000.0) << ","; // convertendo para ms
            file << search_comps_stats.mean() << ",";
            file << search_comps_stats.stddev() << ",";
            file << search_depth_stats.mean() << ",";
            file << search_depth_stats.stddev() << "\n";
        }
    }

    // 6. Finalização e Limpeza
    file.close();
    RBT::destroy(tree);
    std::cout << "\nBenchmark incremental concluido. Resultados salvos em " << output_csv << std::endl;

    return 0;
}
