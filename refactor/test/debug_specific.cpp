#include "../src/rbt.h"
#include <iostream>
#include <vector>
#include <string>

using namespace RBT;

int main() {
    BinaryTree* tree = create();
    
    if (tree != nullptr) {
        // Inserir as palavras exatamente como no teste
        std::vector<std::string> words = {
            "word01", "word02", "word03", "word04", "word05",
            "word06", "word07", "word08", "word09", "word10",
            "word11", "word12", "word13", "word14", "word15"
        };
        
        std::cout << "=== INSERÇÕES ===" << std::endl;
        for (size_t i = 0; i < words.size(); i++) {
            InsertResult result = insert(tree, words[i], i + 1);
            std::cout << "Inseriu " << words[i] << " (doc " << (i+1) << ") - Comparações: " << result.numComparisons << std::endl;
        }
        
        std::cout << "\n=== BUSCAS ===" << std::endl;
        
        // Testar word01
        SearchResult r1 = search(tree, "word01");
        std::cout << "word01 - Encontrado: " << r1.found << ", Comparações: " << r1.numComparisons << std::endl;
        
        // Testar word15 (que estava falhando)
        SearchResult r15 = search(tree, "word15");
        std::cout << "word15 - Encontrado: " << r15.found << ", Comparações: " << r15.numComparisons << std::endl;
        
        // Testar palavra no meio
        SearchResult r08 = search(tree, "word08");
        std::cout << "word08 - Encontrado: " << r08.found << ", Comparações: " << r08.numComparisons << std::endl;
        
        // Testar inexistente
        SearchResult rNone = search(tree, "nonexistent");
        std::cout << "nonexistent - Encontrado: " << rNone.found << ", Comparações: " << rNone.numComparisons << std::endl;
        
        destroy(tree);
    }
    
    return 0;
}
