# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -I./src -I./src/utils
LDFLAGS :=

# Source directories
SRC_DIR := src
UTILS_DIR := $(SRC_DIR)/utils
BENCH_DIR := benchmark
TEST_DIR := test

# Build directory
BUILD_DIR := build

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(UTILS_DIR)/*.cpp)
BENCH_FILES := $(wildcard $(BENCH_DIR)/*.cpp)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter-out $(wildcard $(SRC_DIR)/main_*.cpp),$(SRC_FILES)))
UTILS_OBJ_FILES := $(patsubst $(UTILS_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(wildcard $(UTILS_DIR)/*.cpp))

# Executables
EXECS := bst avl rbt bench_bst bench_avl bench_rbt test_bst test_avl test_rbt
TARGETS := $(addprefix $(BUILD_DIR)/,$(EXECS))

.PHONY: all clean

all: $(TARGETS)

# Create build directory
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Rule to build executables
$(BUILD_DIR)/bst: $(BUILD_DIR)/main_bst.o $(BUILD_DIR)/bst.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/avl: $(BUILD_DIR)/main_avl.o $(BUILD_DIR)/avl.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/rbt: $(BUILD_DIR)/main_rbt.o $(BUILD_DIR)/rbt.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/bench_bst: $(BUILD_DIR)/bench_bst.o $(BUILD_DIR)/bst.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/bench_avl: $(BUILD_DIR)/bench_avl.o $(BUILD_DIR)/avl.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/bench_rbt: $(BUILD_DIR)/bench_rbt.o $(BUILD_DIR)/rbt.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/test_bst: $(BUILD_DIR)/test_bst.o $(BUILD_DIR)/treetest.o $(BUILD_DIR)/bst.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/test_avl: $(BUILD_DIR)/test_avl.o $(BUILD_DIR)/treetest.o $(BUILD_DIR)/avl.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/test_rbt: $(BUILD_DIR)/test_rbt.o $(BUILD_DIR)/treetest.o $(BUILD_DIR)/rbt.o $(BUILD_DIR)/data.o $(UTILS_OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(BENCH_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -rf $(BUILD_DIR)