# Diretórios
SRC_DIR = ../src
UTILS_DIR = $(SRC_DIR)/utils
BUILD_DIR = build

# Arquivos fonte
BENCH_SRC = bench_bst.cpp
BST_SRC = $(SRC_DIR)/bst.cpp
DATA_SRC = $(SRC_DIR)/data.cpp
UTILS_SRC = $(wildcard $(UTILS_DIR)/*.cpp)

# Cabeçalhos
INCLUDES = -I$(SRC_DIR) -I$(UTILS_DIR)

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 $(INCLUDES)

# Alvo final
TARGET = $(BUILD_DIR)/bench_bst

# Objetos
OBJS = $(BUILD_DIR)/bench_bst.o $(BUILD_DIR)/bst.o $(BUILD_DIR)/data.o $(patsubst $(UTILS_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(UTILS_SRC))

# Regra padrão
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/bench_bst.o: bench_bst.cpp $(SRC_DIR)/data.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/bst.o: $(SRC_DIR)/bst.cpp $(SRC_DIR)/data.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/data.o: $(SRC_DIR)/data.cpp $(SRC_DIR)/data.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.cpp $(SRC_DIR)/data.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean