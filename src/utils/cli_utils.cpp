#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "cli_utils.h"
#include "tree_utils.h"
#include "bench_utils.h"
#include "../data.h"

void displayStatsMenu(const std::string& arvore, int n_docs) {
    std::cout << "\n--- Menu Interativo de Estatisticas (" << arvore << ") ---" << std::endl;
    std::cout << "Documentos carregados: " << n_docs << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "[1] Executar Indexacao e Gerar Estatisticas" << std::endl;
    std::cout << "[2] Exibir Relatorio de Estatisticas" << std::endl;
    std::cout << "[3] Imprimir Arvore Atual" << std::endl;
    std::cout << "[4] Alterar No. de Documentos e Recarregar" << std::endl;
    std::cout << "[0] Sair" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Escolha uma opcao: ";
}

void printStatsReport(const IndexStats& stats, const ReadDataStats& readStats) {
    const auto& idxStats = stats.indexingStats;
    const auto& treeStats = stats.treeStats;

    std::cout << "\n--- Relatorio de Desempenho e Estatisticas ---" << std::endl;
    
    std::cout << "\n[ Leitura e Indexacao ]" << std::endl;
    std::cout.precision(4);
    std::cout << " - Tempo de Leitura dos Arquivos: " << std::fixed << readStats.totalReadTime / 1000.0 << " ms" << std::endl;
    std::cout << " - Tempo Total de Indexacao: " << std::fixed << idxStats.totalIndexingTime / 1000.0 << " ms" << std::endl;
    std::cout << " - Total de Palavras Processadas: " << idxStats.totalWordsProcessed << std::endl;
    
    std::cout << "\n[ Comparacoes por Insercao ]" << std::endl;
    std::cout << " - Media: " << std::fixed << idxStats.comparisonStats.mean() << std::endl;
    std::cout << " - Min: " << std::fixed << idxStats.comparisonStats.min << " | Max: " << std::fixed << idxStats.comparisonStats.max << std::endl;
    
    if (idxStats.rotationStats.LL.count > 0 || idxStats.rotationStats.RR.count > 0 || idxStats.rotationStats.LR.count > 0 || idxStats.rotationStats.RL.count > 0) {
        std::cout << "\n[ Rotacoes (AVL/RBT) ]" << std::endl;
        std::cout << " - Simples a Direita (RR): " << idxStats.rotationStats.RR.count << std::endl;
        std::cout << " - Simples a Esquerda (LL): " << idxStats.rotationStats.LL.count << std::endl;
        std::cout << " - Dupla Esquerda-Direita (LR): " << idxStats.rotationStats.LR.count << std::endl;
        std::cout << " - Dupla Direita-Esquerda (RL): " << idxStats.rotationStats.RL.count << std::endl;
    }
    
    std::cout << "\n[ Caracteristicas da Arvore Final ]" << std::endl;
    std::cout << " - Altura da Arvore: " << treeStats.height << std::endl;
    std::cout << " - Total de Nos (palavras unicas): " << treeStats.totalNodes << std::endl;
    std::cout << " - Memoria Utilizada: ~" << std::fixed << treeStats.memoryUsage.scaleMultiplier << " " << treeStats.memoryUsage.scale << std::endl;
    std::cout << " - Balanceamento (AVL): " << (treeStats.flags.isBalanced ? "Balanceada" : "Nao Balanceada") << std::endl;

    std::cout << "\n------------------------------------------------" << std::endl;
}

void searchTree(BinaryTree* tree, const TreeOperations& ops, const std::string& arvore, const std::string& command, int n_docs, const std::string& filesDir) {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Executando: " << arvore << std::endl;
    std::cout << "Operacao: " << command << std::endl;
    std::cout << "Documentos a indexar: " << n_docs << std::endl;
    std::cout << "Diretorio de dados: " << filesDir << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    if (!tree) {
        std::cerr << "Erro: Falha ao receber a arvore." << std::endl;
        return;
    }

    // 1. Ler os arquivos e medir o tempo
    std::cout << "Lendo " << n_docs << " documento(s) de '" << filesDir << "'..." << std::endl;
    ReadDataStats readStats;
    std::vector<std::vector<std::string>> documents_words;
    try {
        documents_words = DATA::readFiles(filesDir, n_docs, readStats, false);
        std::cout << "Leitura concluida em " << readStats.totalReadTime / 1000.0 << " ms." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao ler ou processar arquivos: " << e.what() << std::endl;
        ops.destroy(tree);
        return;
    }

    // 2. Indexar as palavras na árvore
    std::cout << "Iniciando indexacao das palavras na arvore " << arvore << "..." << std::endl;
    double total_insertion_time_ms = 0;
    
    for (int doc_id = 0; doc_id < (int)documents_words.size(); ++doc_id) {
        for (const std::string& word : documents_words[doc_id]) {
            if (!word.empty()) {
                InsertResult i_res = ops.insert(tree, word, doc_id + 1); // doc_id + 1 para começar do doc 1
                total_insertion_time_ms += i_res.executionTime;
            }
        }
    }

    std::cout << "Indexacao concluida em " << total_insertion_time_ms / 1000.0 << " ms." << std::endl;

    // 3. Modo de busca interativa
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Modo de busca interativa." << std::endl;
    std::string word_to_search;
    
    while (true) {
        std::cout << "\nDigite a palavra a buscar (ou '/q' para sair): ";
        std::cin >> word_to_search;

        if (std::cin.eof() || word_to_search == "/q") {
            std::cout << "Encerrando modo de busca..." << std::endl;
            break;
        }

        SearchResult s_res = ops.search(tree, word_to_search);
        if (s_res.found) {
            std::cout << "Palavra '" << word_to_search << "' encontrada." << std::endl;

            // Estrutura para contar ocorrências por ID de documento
            std::vector<int> uniqueIds;
            std::vector<int> counts;

            for (int id : s_res.documentIds) {
                bool found_id = false;
                for (size_t i = 0; i < uniqueIds.size(); ++i) {
                    if (uniqueIds[i] == id) {
                        counts[i]++;
                        found_id = true;
                        break;
                    }
                }
                if (!found_id) {
                    uniqueIds.push_back(id);
                    counts.push_back(1);
                }
            }

            std::cout << "Ocorrencias por documento:" << std::endl;
            for (size_t i = 0; i < uniqueIds.size(); ++i) {
                std::cout << "  - Documento " << uniqueIds[i] << ": " << counts[i] << " vez(es)" << std::endl;
            }

        } else {
            std::cout << "Palavra '" << word_to_search << "' nao encontrada." << std::endl;
        }
        std::cout << "(Comparacoes realizadas: " << s_res.numComparisons << ", Profundidade: " << s_res.searchDepth << ")" << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Finalizando. Liberando memoria da arvore..." << std::endl;
    ops.destroy(tree);
    std::cout << "Memoria liberada." << std::endl;
}

void runStats(BinaryTree* tree, const TreeOperations& ops, const std::string& arvore, const std::string& command, int n_docs_inicial, const std::string& filesDir) {
    if (tree != nullptr) {
        ops.destroy(tree); // Destrói a árvore inicial vazia, se houver
        tree = nullptr;
    }

    int n_docs = n_docs_inicial;
    std::vector<std::vector<std::string>> documents_words;
    ReadDataStats readStats;
    IndexStats indexStats;
    bool stats_ready = false;

    // Carrega os arquivos de dados inicialmente
    std::cout << "Carregando " << n_docs << " documento(s) iniciais de " << filesDir << "..." << std::endl;
    try {
        documents_words = DATA::readFiles(filesDir, n_docs, readStats, false);
        std::cout << "Arquivos carregados com sucesso." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro critico ao ler arquivos iniciais: " << e.what() << std::endl;
        return;
    }

    int choice = -1;
    while (choice != 0) {
        displayStatsMenu(arvore, n_docs);
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Entrada invalida. Por favor, insira um numero." << std::endl;
            std::cin.clear();
            std::cin.ignore(4096, '\n'); // Limpa o buffer de entrada
            continue;
        }

        switch (choice) {
            case 1: { // Executar Indexação e Gerar Estatísticas
                if (documents_words.empty()) {
                    std::cout << "Nenhum dado carregado. Use a opcao [4] para carregar os arquivos." << std::endl;
                    break;
                }
                if (tree != nullptr) ops.destroy(tree);
                tree = ops.create();
                if (!tree) {
                    std::cerr << "Erro: Falha ao criar a arvore." << std::endl;
                    break;
                }

                std::cout << "\nIndexando palavras e coletando estatisticas..." << std::endl;
                
                // Reinicia as estatísticas de indexação
                indexStats.indexingStats = IndexingStats{};

                for (int doc_id = 0; doc_id < (int)documents_words.size(); ++doc_id) {
                    for (const std::string& word : documents_words[doc_id]) {
                        if (!word.empty()) {
                            InsertResult i_res = ops.insert(tree, word, doc_id + 1);
                            indexStats.indexingStats.comparisonStats.add(i_res.numComparisons);
                            indexStats.indexingStats.depthStats.add(i_res.insertDepth);
                            indexStats.indexingStats.rotationStats.add(i_res.numRotations);
                            indexStats.indexingStats.recoloringStats.add(i_res.numRecoloring);
                            indexStats.indexingStats.totalIndexingTime += i_res.executionTime;
                        }
                    }
                }
                indexStats.indexingStats.totalWordsProcessed = indexStats.indexingStats.comparisonStats.count;
                
                // Gera as estatísticas completas da árvore e do índice
                indexStats = getIndexStats(tree, indexStats.indexingStats);
                
                stats_ready = true;
                std::cout << "Indexacao e analise concluidas! Use a opcao [2] para ver o relatorio." << std::endl;
                break;
            }
            case 2: { // Exibir Relatório de Estatísticas
                if (!stats_ready) {
                    std::cout << "Nenhuma estatistica foi gerada. Execute a opcao [1] primeiro." << std::endl;
                } else {
                    printStatsReport(indexStats, readStats);
                }
                break;
            }
            case 3: { // Imprimir Árvore
                if (tree == nullptr) {
                    std::cout << "Nenhuma arvore foi criada. Execute a opcao [1] primeiro." << std::endl;
                } else {
                    std::cout << "\n--- Visualizacao da Arvore ---" << std::endl;
                    printTree(tree);
                    std::cout << "------------------------------" << std::endl;
                }
                break;
            }
            case 4: { // Alterar Número de Documentos e Recarregar
                std::cout << "Digite o novo numero de documentos a serem lidos: ";
                int new_n_docs;
                std::cin >> new_n_docs;

                if (std::cin.fail() || new_n_docs < 0) {
                    std::cout << "Entrada invalida. Por favor, insira um numero positivo." << std::endl;
                    std::cin.clear();
                } else {
                    n_docs = new_n_docs;
                    std::cout << "Recarregando " << n_docs << " documento(s) de " << filesDir << "..." << std::endl;
                    try {
                        documents_words = DATA::readFiles(filesDir, n_docs, readStats, false);
                        std::cout << "Arquivos recarregados com sucesso." << std::endl;
                        stats_ready = false; // Os dados mudaram, as estatísticas antigas são inválidas
                        if(tree) ops.destroy(tree);
                        tree = nullptr;
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao recarregar arquivos: " << e.what() << std::endl;
                        documents_words.clear();
                    }
                }
                std::cin.ignore(4096, '\n'); // Limpa o buffer de entrada
                break;
            }
            case 0: { // Sair
                std::cout << "Encerrando modo de estatisticas..." << std::endl;
                break;
            }
            default: {
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                break;
            }
        }
    }

    if (tree != nullptr) {
        ops.destroy(tree);
    }
    std::cout << "Programa finalizado." << std::endl;
}
