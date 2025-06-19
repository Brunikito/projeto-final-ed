CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../src -I.
SRC_DIR = ../src
UTILS_DIR = $(SRC_DIR)/utils

UTILS_SOURCES = $(wildcard $(UTILS_DIR)/*.cpp)

# BST Test
test_bst: test_bst.cpp treetest.cpp $(SRC_DIR)/bst.cpp $(UTILS_SOURCES)
	$(CXX) $(CXXFLAGS) -o test_bst.exe test_bst.cpp treetest.cpp $(SRC_DIR)/bst.cpp $(UTILS_SOURCES)

# AVL Test  
test_avl: test_avl.cpp treetest.cpp $(SRC_DIR)/avl.cpp $(UTILS_SOURCES)
	$(CXX) $(CXXFLAGS) -o test_avl.exe test_avl.cpp treetest.cpp $(SRC_DIR)/avl.cpp $(UTILS_SOURCES)

# RBT Test
test_rbt: test_rbt.cpp treetest.cpp $(SRC_DIR)/rbt.cpp $(UTILS_SOURCES)
	$(CXX) $(CXXFLAGS) -o test_rbt.exe test_rbt.cpp treetest.cpp $(SRC_DIR)/rbt.cpp $(UTILS_SOURCES)

# Run BST Tests
run_bst: test_bst
	./test_bst.exe

# Run AVL Tests
run_avl: test_avl
	./test_avl.exe

# Run RBT Tests
run_rbt: test_rbt
	./test_rbt.exe

# Clean
clean:
	rm -f *.exe

.PHONY: run_bst run_avl run_rbt clean
