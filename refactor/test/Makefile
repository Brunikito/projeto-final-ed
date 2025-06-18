CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../src -I.
SRC_DIR = ../src

# BST Test
test_bst: test_bst.cpp treetest.cpp $(SRC_DIR)/bst.cpp
	$(CXX) $(CXXFLAGS) -o test_bst.exe test_bst.cpp treetest.cpp $(SRC_DIR)/bst.cpp

# AVL Test  
test_avl: test_avl.cpp treetest.cpp $(SRC_DIR)/avl.cpp
	$(CXX) $(CXXFLAGS) -o test_avl.exe test_avl.cpp treetest.cpp $(SRC_DIR)/avl.cpp

# Run BST Tests
run_bst: test_bst
	./test_bst.exe

# Run AVL Tests
run_avl: test_avl
	./test_avl.exe

# Clean
clean:
	rm -f *.exe

.PHONY: run_bst run_avl clean
