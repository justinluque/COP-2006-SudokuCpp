# Compiler
CXX := g++

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
EXAMPLES_DIR := examples

# Output executable names
TARGET := Sudoku.exe
EXAMPLE1_TARGET := Example1.exe

# Compiler flags
CXXFLAGS := -Wall -I$(INCLUDE_DIR)

# Source files and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Separate out main.o and the other objects for the example targets
MAIN_OBJ := $(BUILD_DIR)/main.o
DEP_OBJS := $(filter-out $(MAIN_OBJ), $(OBJS))

# Default rule
all: $(TARGET)

# Main target for Sudoku
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Example target for creating_class_objects.cpp
example1: $(DEP_OBJS) $(EXAMPLES_DIR)/creating_class_objects.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(EXAMPLES_DIR)/creating_class_objects.cpp $(DEP_OBJS) -o $(EXAMPLE1_TARGET)

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run targets to build and execute programs
run: $(TARGET)
	./$(TARGET)

run_example1: example1
	./$(EXAMPLE1_TARGET)

# Clean rule to remove generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(EXAMPLE1_TARGET)

# Phony targets
.PHONY: all clean example1