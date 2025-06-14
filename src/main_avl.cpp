#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "avl.h"
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

	std::cout << "Criando arvore BST..." << std::endl;
        BinaryTree* tree = AVL::create();
        if (!tree) {
            std::cerr << "Erro: Falha ao criar a arvore BST." << std::endl;
            return 1;
        }

	TreeOperations avl_ops;
    avl_ops.create = AVL::create;
    avl_ops.destroy = AVL::destroy;
    avl_ops.insert = AVL::insert;
    avl_ops.search = AVL::search;

    if (command == "search") {
        searchTree(avl_ops, arvore, command, n_docs, directoryFiles);
    } else if (command == "stats") {
        runStats(avl_ops, arvore, command, n_docs, directoryFiles);
    } else {
        std::cerr << "Erro: Comando '" << command << "' desconhecido." << std::endl;
        printUsage();
        return 1;
    }


	return 0;
}