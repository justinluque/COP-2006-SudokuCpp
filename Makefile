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
EXAMPLE2_TARGET := Example2.exe

# Compiler flags
CXXFLAGS := -Wall -I$(INCLUDE_DIR) -lncurses -DNCURSES_STATIC

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
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)

# Example target for creating_class_objects.cpp
example1: $(DEP_OBJS) $(EXAMPLES_DIR)/creating_class_objects.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/creating_class_objects.cpp $(DEP_OBJS) -o $(EXAMPLE1_TARGET) $(CXXFLAGS) 

example2: $(DEP_OBS) $(EXAMPLES_DIR)/curses_menu.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/curses_menu.cpp $(DEP_OBJS) -o $(EXAMPLE2_TARGET) $(CXXFLAGS)

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run targets to build and execute programs
run: $(TARGET)
	./$(TARGET)

run_example1: example1
	./$(EXAMPLE1_TARGET)

run_example2: example2
	./$(EXAMPLE2_TARGET)

# Clean rule to remove generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(EXAMPLE1_TARGET) $(EXAMPLE2_TARGET)

# Phony targets
.PHONY: all clean example1 example2
