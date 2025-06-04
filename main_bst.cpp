#include "bst.h"
#include "iostream"
#include <filesystem>
#include <fstream>


using namespace bst;
namespace fs = std::filesystem;

int main() {
  BinaryTree* tree = create();

  if (!tree) {
    std::cerr << "Falha ao criar a arvore." << std::endl;
    return 1;
  }

  std::string dataPath = "./data";
  int docID = 0;
  for (std::filesystem::directory_entry entry : fs::directory_iterator(dataPath)) {
    if (entry.is_regular_file()) {
      std::cout << "Lendo arquivo: " << entry.path().string() << " (docID: " << docID << ")" << std::endl;
      std::ifstream file(entry.path());
      std::string word;
      while (file >> word) {
          insert(tree, docID, word);
      }
      docID++;
    }
  }

}






