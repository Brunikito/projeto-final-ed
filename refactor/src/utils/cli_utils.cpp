#include <iostream>
#include <vector>

#include "tree_utils.h"
#include "bench_utils.h"
#include "value_utils.h"
#include "cli_utils.h"
#include "../data.h"

void searchTree(const TreeOperations& ops, const std::string& arvore, const std::string& command, int n_docs, const std::string& directoryFiles){
	std::cout << "----------------------------------------" << std::endl;
		std::cout << "Executando: " << arvore << std::endl;
		std::cout << "Operacao: " << command << std::endl;
		std::cout << "Documentos a indexar: " << n_docs << std::endl;
		std::cout << "Diretorio de dados: " << directoryFiles << std::endl;
		std::cout << "----------------------------------------" << std::endl;

		BinaryTree* tree = ops.create();
    if (!tree) {
        std::cerr << "Erro: Falha ao criar a arvore." << std::endl;
        return;
    }

		std::cout << "Lendo e indexando documentos de '" << directoryFiles << "'..." << std::endl;
        std::vector<std::vector<std::string>> documents_words;
        try {
            documents_words = DATA::readFiles(directoryFiles, n_docs, false);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler ou processar arquivos: " << e.what() << std::endl;
            ops.destroy(tree);
            return;
        }

        std::cout << "Iniciando insercao das palavras na BST..." << std::endl;
        
        double total_insertion_time_ms = 0;
        long long total_insertion_comparisons = 0;

		for (int doc_id = 0; doc_id < documents_words.size(); ++doc_id) {
            for (const std::string& word : documents_words[doc_id]) {
                if (!word.empty()) {
                    InsertResult i_res = ops.insert(tree, word, doc_id + 1);
                    total_insertion_time_ms += i_res.executionTime;
                    total_insertion_comparisons += i_res.numComparisons;
                }
            }
        }

		std::cout << "Indexacao concluida." << std::endl;
        std::cout << "Tempo total de insercao: " << total_insertion_time_ms / 1000.0 << " ms (" << total_insertion_time_ms / 1000000.0 << " s)" << std::endl;
        std::cout << "Total de comparacoes durante insercao: " << total_insertion_comparisons << std::endl;

		
		std::cout << std::endl << "----------------------------------------" << std::endl;
		std::cout << "Modo de busca interativa." << std::endl;
		std::string word_to_search;
		
		while (true) {
			std::cout << std::endl << "Digite '/q' para terminar." << std::endl;
            std::cout << "Buscar palavra: ";
            std::cin >> word_to_search;

			if (std::cin.eof() || word_to_search == "/q") {
                std::cout << "Encerrando modo de busca..." << std::endl;
                break; // Sai do loop
            }

			SearchResult s_res = ops.search(tree, word_to_search);
			if (s_res.found) {
				std::cout << "Palavra '" << word_to_search << "' encontrada nos documentos IDs: ";

				// Vetores para armazenar IDs únicos e suas quantidades
				std::vector<int> uniqueIds;
				std::vector<int> counts;

				for (int id : s_res.documentIds) {
					bool found = false;
					for (size_t i = 0; i < uniqueIds.size(); ++i) {
						if (uniqueIds[i] == id) {
							counts[i]++;
							found = true;
							break;
						}
					}
					if (!found) {
						uniqueIds.push_back(id);
						counts.push_back(1);
					}
				}

				for (size_t i = 0; i < uniqueIds.size(); ++i) {
					std::cout << uniqueIds[i];
					if (counts[i] > 1) {
						std::cout << " (x" << counts[i] << ")";
					}
					if (i < uniqueIds.size() - 1) {
						std::cout << ", ";
					}
				}

				std::cout << std::endl;
			} else {
                std::cout << "Palavra '" << word_to_search << "' nao encontrada." << std::endl;
            }
			std::cout << "(Comparacoes: " << s_res.numComparisons << ", Tempo: " << s_res.executionTime / 1000.0 << " ms)" << std::endl;
		}

		std::cout << "----------------------------------------" << std::endl;
        std::cout << "Finalizando. Liberando memoria da BST..." << std::endl;
        ops.destroy(tree);
        std::cout << "Memoria liberada." << std::endl;
}

void runStats(const TreeOperations& ops, const std::string& arvore, const std::string& comand, int n_docs_inicial, const std::string& directoryFiles) {
    
    BinaryTree* tree = nullptr;
    std::vector<std::vector<std::string>> documents_words;
    int n_docs = n_docs_inicial;
    int choice = -1;

    std::cout << "Carregando " << n_docs << " documento(s) iniciais de " << directoryFiles << "..." << std::endl;
    try {
        documents_words = DATA::readFiles(directoryFiles, n_docs, false);
        std::cout << "Arquivos carregados com sucesso." << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Erro critico ao ler arquivos iniciais: " << e.what() << std::endl;
        return; 
    }

    while (true) {
        std::cout << "\n--- Menu Interativo de Estatisticas (" << arvore << ") ---" << std::endl;
        std::cout << "Documentos a serem lidos: " << n_docs << std::endl;
        std::cout << "[1] Executar Estatisticas (Indexar e Gerar Relatorio)" << std::endl;
        std::cout << "[2] Alterar Numero de Documentos" << std::endl;
        std::cout << "[3] Recarregar Arquivos de Dados" << std::endl;
        std::cout << "[4] Imprimir Arvore Atual (se existir)" << std::endl;
        std::cout << "[0] Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: { // Executar Estatísticas
                if (tree != nullptr) {
                    ops.destroy(tree);
                    tree = nullptr;
                }
                
                if (documents_words.empty()){
                    std::cout << "Nenhum dado carregado. Recarregue os arquivos com a opcao [3]." << std::endl;
                    break;
                }

                tree = ops.create();
                if (!tree) {
                    std::cerr << "Erro: Falha ao criar a arvore." << std::endl;
                    break;
                }

                long long total_comparisons = 0;
                double total_time_microseconds = 0;
                long long word_count = 0;

                std::cout << "\nIndexando palavras e coletando estatisticas..." << std::endl;
                auto start_time = std::chrono::high_resolution_clock::now();

                for (const auto& doc : documents_words) {
                    for (const auto& word : doc) {
                        InsertResult i_res = ops.insert(tree, word, 0);
                        total_comparisons += i_res.numComparisons;
                        total_time_microseconds += i_res.executionTime;
                        word_count++;
                    }
                }

                auto end_time = std::chrono::high_resolution_clock::now();
                auto total_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

                std::cout << "\n--- Relatorio de Desempenho ---" << std::endl;
                std::cout << "Arvore utilizada: " << arvore << std::endl;
                std::cout << "Total de palavras inseridas: " << word_count << std::endl;
                std::cout << "Tempo total de indexacao: " << total_duration_ms.count() << " ms" << std::endl;
                std::cout << "Total de comparacoes: " << total_comparisons << std::endl;
                std::cout << "Altura final da arvore: " << getHeight(tree->root) << std::endl;
                
                if (word_count > 0) {
                    std::cout.precision(4);
                    std::cout << "Media de comparacoes por insercao: " << std::fixed << (double)total_comparisons / word_count << std::endl;
                }
                std::cout << "---------------------------------" << std::endl;
                break;
            }
            case 2: { // Alterar Número de Documentos
                std::cout << "Digite o novo numero de documentos a serem lidos: ";
                int new_n_docs;
                std::cin >> new_n_docs;
                 if (std::cin.fail() || new_n_docs < 0) {
                    std::cout << "Entrada invalida. Por favor, insira um numero positivo." << std::endl;
                    std::cin.clear(); // Limpa o estado de erro do cin
                } else {
                    n_docs = new_n_docs;
                    std::cout << "Numero de documentos alterado para " << n_docs << "." << std::endl;
                    std::cout << "Use a opcao [3] para recarregar os arquivos com o novo valor." << std::endl;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            case 3: { // Recarregar Arquivos
                std::cout << "Recarregando " << n_docs << " documento(s) de " << directoryFiles << "..." << std::endl;
                try {
                    documents_words = DATA::readFiles(directoryFiles, n_docs, false);
                    std::cout << "Arquivos recarregados com sucesso." << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Erro ao recarregar arquivos: " << e.what() << std::endl;
                    documents_words.clear();
                }
                break;
            }
            case 4: { // Imprimir Árvore
                if (tree == nullptr) {
                    std::cout << "Nenhuma arvore foi criada ainda. Execute as estatisticas com a opcao [1] primeiro." << std::endl;
                } else {
                    std::cout << "\n--- Visualizacao da Arvore ---" << std::endl;
                    printTree(tree);
                    std::cout << "------------------------------" << std::endl;
                }
                break;
            }
            case 0: { // Sair
                std::cout << "Encerrando modo de estatisticas..." << std::endl;
                if (tree != nullptr) {
                    ops.destroy(tree);
                }
                return; // Sai da função runStats e volta para o main
            }
            default: {
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                break;
            }
        }
    }
}