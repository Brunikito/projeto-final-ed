#include "bst.h"
#include "iostream" // É mais comum usar <iostream>
#include <filesystem>
#include <fstream>

// using namespace bst; // É preferível usar BST:: ou especificar cada função
namespace fs = std::filesystem;

int main() {
  BST::BinaryTree* tree = BST::create(); // Usando o namespace explicitamente

  if (!tree) {
    std::cerr << "Falha ao criar a arvore." << std::endl;
    return 1;
  }

  std::string dataPath = "./data"; // Certifique-se que este diretório existe e contém os arquivos de texto
  int docID = 0;
  // Verifica se o diretório existe
  if (!fs::exists(dataPath) || !fs::is_directory(dataPath)) {
    std::cerr << "Diretorio '" << dataPath << "' nao encontrado." << std::endl;
    BST::destroy(tree); // Não se esqueça de liberar a memória da árvore
    return 1;
  }

  for (const auto& entry : fs::directory_iterator(dataPath)) { // Usar const auto& é uma boa prática
    if (entry.is_regular_file()) {
      std::cout << "Lendo arquivo: " << entry.path().string() << " (docID: " << docID << ")" << std::endl;
      std::ifstream file(entry.path());
      if (!file.is_open()) { // Verificar se o arquivo abriu corretamente
        std::cerr << "Erro ao abrir o arquivo: " << entry.path().string() << std::endl;
        continue; // Pula para o próximo arquivo
      }
      std::string word;
      while (file >> word) {
        // Converter a palavra para minúsculas ou fazer outro pré-processamento, se necessário
        BST::insert(tree, word, docID); // Chamada corrigida
      }
      file.close(); // Boa prática fechar o arquivo
      docID++;
    }
  }

  // Adicionar aqui a lógica para usar a árvore (buscar palavras, imprimir, etc.)

  BST::destroy(tree); // Lembre-se de destruir a árvore para liberar memória
  return 0; // Adicionar retorno 0 para indicar sucesso
}