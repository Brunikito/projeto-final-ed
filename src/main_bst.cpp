#include <iostream>
#include <string>
#include <vector>

#include "bst.h"
#include "data.h"

#include "utils/tree_utils.h"
#include "utils/cli_utils.h"

void printUsage() {
    std::cerr << "Uso: ./bst <search\\stats> <n_docs> <diretorio>" << std::endl;
    std::cerr << "Onde:" << std::endl;
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

	std::string command = argv[1];
	int n_docs;
	std::string filesDir = argv[3];

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

    if (command != "search" && command != "stats") {
        std::cerr << "Erro: Comando '" << command << "' desconhecido." << std::endl;
        printUsage();
        return 1;
    }

	std::cout << "Criando arvore BST..." << std::endl;
    BinaryTree* tree = BST::create();
    if (!tree) {
        std::cerr << "Erro: Falha ao criar a arvore BST." << std::endl;
        return 1;
    }

	TreeOperations bst_ops = TreeOperations{BST::create, BST::destroy, BST::insert, BST::search};

    // Decida qual função chamar com base no comando
    if (command == "search") {
        searchTree(tree, bst_ops, "BST", command, n_docs, filesDir);
        return 0;
    }
    runStats(tree, bst_ops, "BST", command, n_docs, filesDir);
	return 0;
}