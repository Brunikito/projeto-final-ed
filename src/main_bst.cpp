#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "bst.h"
#include "tree_utils.h"
#include "data.h"

void printUsage() {
    std::cerr << "Uso: ./<arvore> search\\stats <n_docs> <diretorio>" << std::endl;
    std::cerr << "Onde:" << std::endl;
    std::cerr << "  <arvore>    : nome do executavel da extrutura (ex: bst, avl, rbt)" << std::endl;
    std::cerr << "  search      : comando que permite realizar buscas por palavras" << std::endl;
    std::cerr << "  stats       : comando que gera estatisticas de desempenho durante a indexacao" << std::endl;
    std::cerr << "  <n_docs>    : numero de documentos a indexar" << std::endl;
    std::cerr << "  <diretorio> : caminho para a pasta contendo os arquivos .txt" << std::endl;
}

int main(int argc, char* argv[]){
	if (argc != 4){
		std::cerr << "Erro: Numero incorreto de argumentos." << std::endl;
		printUsage();
		return 1;
	}

	std::string arvore = argv[0];
	std::string command = argv[1];
	int n_docs;
	std::string directoryFiles = argv[3];

	try {
		n_docs = std::stoi(argv[2]);
		if (n_docs <= 0) {
			std::cerr << "Erro: <n_docs> deve ser um numero positivo" << std::endl;
			printUsage();
			return 1;
		}
	} catch (const std::invalid_argument& ia) {
        std::cerr << "Erro: <n_docs> invalido. '" << argv[2] << "' não é um número." << std::endl;
        printUsage();
        return 1;
	}
	
	
    std::vector<std::string> comands = {"search", "stats"};

    if (std::find(comands.begin(), comands.end(), command) == comands.end()) {
        std::cerr << "Erro: Comando '" << command << "' desconhecido ou não suportado para BST nesta entrega." << std::endl;
        printUsage();
        return 1;
    }

	// search
	if (command == comands[0]){
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Executando: " << arvore << std::endl;
		std::cout << "Operacao: " << command << std::endl;
		std::cout << "Documentos a indexar: " << n_docs << std::endl;
		std::cout << "Diretorio de dados: " << directoryFiles << std::endl;
		std::cout << "----------------------------------------" << std::endl;

		std::cout << "Criando arvore BST..." << std::endl;
        BinaryTree* tree = BST::create();
        if (!tree) {
            std::cerr << "Erro: Falha ao criar a arvore BST." << std::endl;
            return 1;
        }

		std::cout << "Lendo e indexando documentos de '" << directoryFiles << "'..." << std::endl;
        std::vector<std::vector<std::string>> documents_words;
        try {
            documents_words = DATA::readFiles(directoryFiles, n_docs, false);
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler ou processar arquivos: " << e.what() << std::endl;
            BST::destroy(tree);
            return 1;
        }

        std::cout << "Iniciando insercao das palavras na BST..." << std::endl;
        
        double total_insertion_time_ms = 0;
        long long total_insertion_comparisons = 0;

		for (int doc_id = 0; doc_id < documents_words.size(); ++doc_id) {
            for (const std::string& word : documents_words[doc_id]) {
                if (!word.empty()) {
                    InsertResult i_res = BST::insert(tree, word, doc_id + 1);
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

			SearchResult s_res = BST::search(tree, word_to_search);
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
        BST::destroy(tree); // Libera todos os nós e a árvore
        std::cout << "Memoria liberada." << std::endl;

	} else if ( command == comands[1]) {
		
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Executando: " << arvore << std::endl;
		std::cout << "Operacao: " << command << std::endl;
		std::cout << "Documentos a indexar: " << n_docs << std::endl;
		std::cout << "Diretorio de dados: " << directoryFiles << std::endl;
		std::cout << "----------------------------------------" << std::endl;

        BinaryTree* tree = BST::create();
        if (!tree) {
            std::cerr << "Erro critico: Falha ao criar a arvore BST." << std::endl;
            return 1;
        }
        std::vector<std::vector<std::string>> documents_words;
        try {
            // verbose = false para não poluir a saída do stats
            documents_words = DATA::readFiles(directoryFiles, n_docs, false); // Usando directoryFiles e n_docs
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler ou processar arquivos: " << e.what() << std::endl;
            BST::destroy(tree);
            return 1;
        }
        int num_docs_actually_processed = documents_words.size();

        // 3. Indexar e Acumular Estatísticas (sem logs verbosos aqui)
        double total_indexing_execution_time_microseconds = 0;
        long long total_indexing_comparisons = 0;
        long long total_words_processed_for_insertion = 0; // Total de chamadas a insert

        for (int doc_id = 0; doc_id < num_docs_actually_processed; ++doc_id) {
            for (const std::string& word : documents_words[doc_id]) {
                if (!word.empty()) {
                    total_words_processed_for_insertion++;
                    InsertResult single_insert_result = BST::insert(tree, word, doc_id + 1);
                    total_indexing_execution_time_microseconds += single_insert_result.executionTime;
                    total_indexing_comparisons += single_insert_result.numComparisons;
                }
            }
        }
		
        std::cout << std::endl;
        std::cout << "Operacoes de Insercao (palavras): " << total_words_processed_for_insertion << std::endl;
        
        // Formatando o tempo para segundos e milissegundos
        double total_time_seconds = total_indexing_execution_time_microseconds / 1000000.0;
        double total_time_milliseconds = total_indexing_execution_time_microseconds / 1000.0;
        std::cout << "  Tempo Total: " << total_time_seconds << " s (" << total_time_milliseconds << " ms)" << std::endl;
        std::cout << "  Comparacoes Totais: " << total_indexing_comparisons << std::endl;

        if (total_words_processed_for_insertion > 0) {
            std::cout << "  Tempo Medio/Operacao: " << (total_indexing_execution_time_microseconds / total_words_processed_for_insertion) << " us" << std::endl;
            std::cout << "  Comparacoes Medias/Operacao: " << static_cast<double>(total_indexing_comparisons) / total_words_processed_for_insertion << std::endl;
        }
        
        // Adicionando a chamada para printIndex
        std::cout << "Indice Invertido da Arvore (em ordem):" << std::endl;
        printIndex(tree); // Chamada da função de tree_utils.h
        std::cout << std::endl; // Adiciona uma linha em branco para separação
        std::cout << "--------------------------------------------" << std::endl;

        // Adicionando a chamada para printTree
        std::cout << "Visualizacao da Estrutura da Arvore:" << std::endl;
        printTree(tree);  // Chamada da função de tree_utils.h
        std::cout << "--------------------------------------------" << std::endl;
        
        std::vector<std::string> sample_search_words = {"a", "casa", "algoritmo", "estrutura", "naoexiste"};
        for (const std::string& sample_word : sample_search_words) {
            SearchResult sr = BST::search(tree, sample_word);
            std::cout << "  - Palavra '" << sample_word << "': " << (sr.found ? "Encontrada" : "Nao Encontrada") << " (Tempo: " << sr.executionTime << " us, Comp: " << sr.numComparisons << ")" << std::endl;
        }
       
        std::cout << std::endl;

        BST::destroy(tree);
    }


	return 0;
}