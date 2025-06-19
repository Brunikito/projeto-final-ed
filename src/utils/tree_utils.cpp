#include <vector>
#include <string>
#include <iostream>

#include "tree_utils.h"

// Impressão do índice (palavra -> ids de documento) em ordem.
void recursivePrintIndex(Node* node, int& counter){
    if (node == nullptr) return;

    recursivePrintIndex(node->left, counter); // esquerda
    std::cout << ++counter << ". " << node->word << ": ";

    // Construir lista de ids únicos + contagem de repetição
	std::vector<int> uniqueIds;
    std::vector<int> counts;

    for (int id : node->documentIds) {
        bool found = false;
        for (size_t i = 0; i < uniqueIds.size(); ++i) {
            if (uniqueIds[i] == id) {           // id já visto → incrementa
                counts[i]++;
                found = true;
                break;
            }
        }
        if (!found) {           // id novo
            uniqueIds.push_back(id);
            counts.push_back(1);
        }
    }

    // Exibe ids, marcando multiplicidade quando > 1
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
    recursivePrintIndex(node->right, counter);  // direita
}

// Desenho ASCII da árvore.
void recursivePrintTree(Node* node, const std::string& prefix, bool isLeft){
    if (node == nullptr) return;
    std::cout << prefix;
    std::cout << (isLeft ? "|-- " : "\\-- ");
    std::cout << node->word << std::endl;

    bool hasLeft = node->left != nullptr;
    bool hasRight = node->right != nullptr;

    if (hasLeft || hasRight) {
        std::string newPrefix = prefix + (isLeft ? "|   " : "    ");
        if (node->left) recursivePrintTree(node->left, newPrefix, true);
        if (node->right) recursivePrintTree(node->right, newPrefix, false);
    }
}

// Wrappers públicos de impressão
void printIndex(BinaryTree* tree){
    int counter = 0;
    if (tree && tree->root)
        recursivePrintIndex(tree->root, counter);
}

void printTree(BinaryTree* tree){
    if (tree && tree->root)
        std::cout << tree->root->word << std::endl;
    if (tree && tree->root) {
        if (tree->root->left) recursivePrintTree(tree->root->left, "", true);
        if (tree->root->right) recursivePrintTree(tree->root->right, "", false);
    }
}

// Métricas simples: altura, nós, largura, folhas, memória.
int calculateTreeHeight(BinaryTree* tree) {
    if (tree == nullptr) return -1;
    if (tree->root == tree->NIL) return 0;
    return tree->root->height;
}
int calculateTotalNodes(Node* node, Node* NIL){
    if (node == NIL) return 0;
    return 1 + calculateTotalNodes(node->left, NIL) + calculateTotalNodes(node->right, NIL);
}
int calculateMaxWidth(BinaryTree* tree){
    if (tree == nullptr) return -1;
    if (tree->root == tree->NIL) return 0;
    std::vector<Node*> currentLevel;
    std::vector<Node*> nextLevel;
    
    currentLevel.push_back(tree->root);
    int maxWidth = 0;
    while (!currentLevel.empty()) {
        maxWidth = std::max(maxWidth, static_cast<int>(currentLevel.size()));

        for (Node* node : currentLevel) {
            if (node->left != tree->NIL) nextLevel.push_back(node->left);
            if (node->right != tree->NIL) nextLevel.push_back(node->right);
        }

        // Avança para o próximo nível
        currentLevel = std::move(nextLevel);
        nextLevel.clear();  // Limpa o próximo nível
    }

    return maxWidth;
}
GroupedStats calculateLeavesDepth(Node* node, Node* NIL, int currentDepth){
    GroupedStats stats;
    if (node == NIL) return stats;

    if (node->left == NIL && node->right == NIL) {
        stats.add(currentDepth);
    }

    GroupedStats leftStats = calculateLeavesDepth(node->left, NIL, currentDepth + 1);
    GroupedStats rightStats = calculateLeavesDepth(node->right, NIL, currentDepth + 1);

    stats.merge(leftStats);
    stats.merge(rightStats);

    return stats;
}
MemoryUsage calculateMemoryUsage(BinaryTree* tree) {
    // Aproximação: soma tamanhos dos nós + cabeçalho da árvore.
    MemoryUsage memUsage;
    memUsage.numBytes = sizeof(BinaryTree);
    if (tree == nullptr) {
        memUsage.scaleMultiplier = memUsage.numBytes;
        memUsage.scale = "B";
        return memUsage;
    }
    if (tree->root == nullptr) {
        memUsage.numBytes += sizeof(tree->root) + sizeof(tree->NIL);
        memUsage.scaleMultiplier = memUsage.numBytes;
        memUsage.scale = "B";
        return memUsage;
    }
    memUsage.numBytes += sizeof(tree->NIL);
    std::vector<Node*> nodesToVisit; // DFS
    nodesToVisit.push_back(tree->root);
    while (!nodesToVisit.empty()) {
        Node* node = nodesToVisit.back();
        nodesToVisit.pop_back();

        if (node != tree->NIL) {
            memUsage.numBytes += sizeof(Node);
            if (node->left != tree->NIL) nodesToVisit.push_back(node->left);
            if (node->right != tree->NIL) nodesToVisit.push_back(node->right);
        }
    }
    // Calcula escala (KB / MB / GB) se necessário.
    memUsage.scale = "B";
    memUsage.scaleMultiplier = memUsage.numBytes;
    if (memUsage.numBytes > 1024) {
        memUsage.scale = "KB";
        memUsage.scaleMultiplier /= 1024;
    }
    if (memUsage.numBytes > 1024) {
        memUsage.scale = "MB";
        memUsage.scaleMultiplier /= 1024;
    }
    if (memUsage.numBytes > 1024) {
        memUsage.scale = "GB";
        memUsage.scaleMultiplier /= 1024;
    }
    
    return memUsage;
}

// Funções de verificação estrutural
bool isBalanced(Node* node, Node* NIL) {
    if (node == NIL) return true;
    if (ValueUtils::abs(node->left->height - node->right->height) > 1) return false;
    return isBalanced(node->left, NIL) && isBalanced(node->right, NIL);
}
bool isPerfect(Node* node, Node* NIL, int depth, int level) {
    // folha -> confere profundidade desejada
    if (node == nullptr) return true;
    if (node->left == nullptr && node->right == nullptr)
        return (depth == level + 1);
    if (node->left == nullptr || node->right == nullptr) {
        return false;
    }
    return isPerfect(node->left, NIL, depth, level + 1) && isPerfect(node->right, NIL, depth, level + 1);
}
bool isFull(Node* node, Node* NIL) {
    if (node == NIL) return true;
    if ((node->left == NIL && node->right != NIL) || (node->left != NIL && node->right == NIL)) {
        return false; // 1 filho
    }
    return isFull(node->left, NIL) && isFull(node->right, NIL);
}
bool isComplete(Node* node, Node* NIL, int index, int totalNodes) {
    if (node == NIL) return true;
    if (index >= totalNodes) return false;  // buraco na representação
    return isComplete(node->left, NIL, 2 * index + 1, totalNodes) && isComplete(node->right, NIL, 2 * index + 2, totalNodes);
}

TreeFlags calculateTreeFlags(BinaryTree* tree) {
    TreeFlags flags = {false, false, false, false};    
    if (tree == nullptr) return flags;
    if (tree->root == tree->NIL) return flags;

    int totalNodes = calculateTotalNodes(tree->root, tree->NIL);
    int height = calculateTreeHeight(tree);

    flags.isBalanced = isBalanced(tree->root, tree->NIL);
    flags.isPerfect = isPerfect(tree->root, tree->NIL, height);
    flags.isFull = isFull(tree->root, tree->NIL);
    flags.isComplete = isComplete(tree->root, tree->NIL, 0, totalNodes);

    return flags;
}
WordsStats getWordsStats(BinaryTree* tree) { // Mais um DFS
    WordsStats wordsStats;
    if (tree == nullptr) {
        return wordsStats;
    }
    if (tree->root == tree->NIL) {
        return wordsStats;
    }
    std::vector<Node*> nodesToVisit; // DFS
    nodesToVisit.push_back(tree->root);
    while (!nodesToVisit.empty()) {
        Node* node = nodesToVisit.back();
        nodesToVisit.pop_back();

        if (node != tree->NIL) {
            int num_ocurrences = static_cast<int>(node->documentIds.size());
            wordsStats.wordOcurrences.push_back({node->word, num_ocurrences});
            wordsStats.ocurrenceStats.add(num_ocurrences);

            if (node->left != tree->NIL) nodesToVisit.push_back(node->left);
            if (node->right != tree->NIL) nodesToVisit.push_back(node->right);
        }
    }
    return wordsStats;
}

TreeStats getTreeStats(BinaryTree* tree) {
    TreeStats stats;
    stats.height = calculateTreeHeight(tree);
    stats.totalNodes = calculateTotalNodes(tree->root, tree->NIL);
    stats.maxWidth = calculateMaxWidth(tree);
    stats.leavesDepth = calculateLeavesDepth(tree->root, tree->NIL);
    stats.memoryUsage = calculateMemoryUsage(tree);
    stats.flags = calculateTreeFlags(tree);
    return stats;
}
IndexStats getIndexStats(BinaryTree* tree, IndexingStats& indexingStats){
    IndexStats stats;
    stats.indexingStats = indexingStats;
    stats.treeStats = getTreeStats(tree);
    stats.wordStats = getWordsStats(tree);
    return stats;
}
