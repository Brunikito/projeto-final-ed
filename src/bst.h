    #ifndef BST_H
    #define BST_H

    #include <string>
    #include <vector>
    #include <chrono>

    namespace BST {

/**
 * @struct Node
 * @brief Nó da Árvore Binária de Busca.
 */
	struct Node
	{
		std::string word;
		std::vector<int> documentIds;
		Node *parent;
		Node *left;
		Node *right;
		int height; // não usado na BST (usado na AVL)
		int isRed;	// não usado na BST (usado na RBT)
	};

/**
 * @struct BinaryTree
 * @brief Estrutura raiz que contém a árvore.
 */
	struct BinaryTree
	{
		Node *root;
		Node *NIL; // não usado na BST
	};

/**
 * @struct InsertResult
 * @brief Estatisticas retornadas pela função ::BST::insert.
 */
	struct InsertResult
	{
		int numComparisons; // Conta tanto comparações de igualdade quanto de ordenação
		double executionTime; // Duração da operação em microssegundos
	};

/**
 * @struct SearchResult
 * @brief Resultado detalhado da função ::BST::search.
 */
	struct SearchResult
	{
		int found; // 1 = palavra encontrada, 0 = não encontrada
		std::vector<int> documentIds; // IDs dos documentos onde a palavra ocorre
		double executionTime;
		int numComparisons;
	};
	/**
	 * @brief Cria e devolve uma BST vazia.
	 *
	 * @return Ponteiro para ::BST::BinaryTree recém-criada ou nullptr se
	 *         não houver memória suficiente.
	 */
	BinaryTree *create();
	/**
	 * @brief Insere uma palavra na árvore.
	 *
	 * Se a palavra já existir, @p documentId é anexado ao vetor
	 * correspondente; caso contrário, um novo nó é criado no local
	 * ordenado adequado.
	 *
	 * @param tree        Ponteiro para a árvore
	 * @param word        Palavra a ser inserida.
	 * @param documentId  Identificador do documento onde a palavra se encontra.
	 * @return Estrutura ::BST::InsertResult.
	 */
	InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);
	/**
	 * @brief Busca uma palavra na árvore.
	 *
	 * @param tree  Ponteiro para a árvore.
	 * @param word  Palavra a ser procurada.
	 * @return Estrutura ::BST::SearchResult.
	 */
	SearchResult search(BinaryTree *tree, const std::string &word);
	/**
	 * @brief Libera toda a memória associada a uma árvore BST.
	 *
	 * A função percorre a árvore em pós-ordem e deleta todos os nós,
	 * em seguida deleta também a própria estrutura ::BST::BinaryTree.
	 *
	 * @param tree Ponteiro para a árvore previamente criada por ::BST::create.
	 */
	void destroy(BinaryTree *tree);

} // namespace BST

#endif // BST_H
