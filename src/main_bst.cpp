#include "bst.h"
#include "iostream"
#include <filesystem>
#include <fstream>

using namespace BST;
namespace fs = std::filesystem;

int main()
{
	BinaryTree *tree = create();

	std::string dataPath = "./data";
	int docID = 0;
	for (std::filesystem::directory_entry entry : fs::directory_iterator(dataPath))
	{
		if (entry.is_regular_file())
		{
			std::ifstream file(entry.path());
			std::string word;
			while (file >> word)
			{
				insert(tree, docID, word);
			}
			docID++;
		}
	}
}
