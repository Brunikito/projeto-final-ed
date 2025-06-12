CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I./src -I./test
TARGET = complete_test_avl
SOURCES = test/complete_test_avl.cpp src/avl.cpp

# Windows-specific settings
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    CXXFLAGS += -mconsole
endif

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
