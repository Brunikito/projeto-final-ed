#include "bst.h"
#include "iostream"
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>


namespace fs = std::filesystem;
std::vector<BST::InsertResult> insertFilesInTree(BST::BinaryTree* tree, const std::string& dataPath, const int numDocs, bool verbose = false) {
  // criar um vector pra armazenar os resultados de inserção
  std::vector<BST::InsertResult> results;

  std::vector<fs::directory_entry> files;
  for (const auto& entry : fs::directory_iterator(dataPath)) {
    if (entry.is_regular_file()) {
      if (std::stoi(entry.path().filename().string()) < numDocs) {
      files.push_back(entry);
      }
    }
  }

  // 2. Ordenar pelo nome convertido para inteiro
  std::sort(files.begin(), files.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
    return std::stoi(a.path().filename().string()) < std::stoi(b.path().filename().string());
  });

  // 3. Ler os arquivos na ordem correta
  int docID = 0;
  for (const auto& entry : files) {
    if (verbose) std::cout << "Lendo arquivo: " << entry.path().string() << " (docID: " << docID << ")" << std::endl;
    std::ifstream file(entry.path());
    if (!file.is_open()) {
      std::cerr << "Erro ao abrir o arquivo: " << entry.path().string() << std::endl;
      continue;
    }
    std::string word;
    while (file >> word) {
      results.push_back(BST::insert(tree, word, docID));
    }
    file.close();
    docID++;
  }
  return results;
}



int main(int argc, char* argv[]) {
  // LEITURA DE ARQUIVOS
  if (argc > 3) {
    std::cerr << "Uso: " << argv[0] << " [numero_de_documentos]" << std::endl;
    return 1;
  }
  int numDocs = std::stoi(argv[1]); // Defina o número máximo de documentos a serem lidos
  if (numDocs <= 0) {
    std::cerr << "Numero de documentos deve ser maior que zero." << std::endl;
    return 1;
  }
  bool verbose = false; // Defina se deseja exibir mensagens detalhadas
  if (argc == 3 && std::string(argv[2]) == "--verbose") {
    verbose = true;
  }

  // FUNÇÃO EM SI
  BST::BinaryTree* tree = BST::create();

  if (!tree) {
    std::cerr << "Falha ao criar a arvore." << std::endl;
    return 1;
  }

  std::string dataPath = "./data";

  if (!fs::exists(dataPath) || !fs::is_directory(dataPath)) {
    std::cerr << "Diretorio '" << dataPath << "' nao encontrado." << std::endl;
    BST::destroy(tree);
    return 1;
  }

  std::vector<BST::InsertResult> results = insertFilesInTree(tree, dataPath, numDocs, verbose);

  BST::destroy(tree);
  return 0;
}