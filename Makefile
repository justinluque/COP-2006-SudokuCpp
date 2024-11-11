# Compiler
CXX := g++

# Directories
SRC_DIR := src
SRC_APP_DIR := src/App
SRC_SUDOKU_DIR := src/Sudoku

INCLUDE_DIR := include
INCLUDE_APP_DIR := include/App
INCLUDE_SUDOKU_DIR := include/Sudoku
INCLUDE_UTILITY_DIR := include/Utility

BUILD_DIR := build
EXAMPLES_DIR := examples

# Output executable names
TARGET := Sudoku.exe
EXAMPLE1_TARGET := Example1.exe
EXAMPLE2_TARGET := Example2.exe
EXAMPLE3_TARGET := Example3.exe
EXAMPLE4_TARGET := Example4.exe

# Compiler flags
CXXFLAGS := -Wall -I$(INCLUDE_DIR) -I$(INCLUDE_APP_DIR) \
						-I$(INCLUDE_SUDOKU_DIR) -I$(INCLUDE_UTILITY_DIR) \
						-lncurses -DNCURSES_STATIC

# Source files and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_APP_DIR)/*.cpp) $(wildcard $(SRC_SUDOKU_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp)) \
        $(patsubst $(SRC_APP_DIR)/%.cpp,$(BUILD_DIR)/App_%.o,$(wildcard $(SRC_APP_DIR)/*.cpp)) \
        $(patsubst $(SRC_SUDOKU_DIR)/%.cpp,$(BUILD_DIR)/Sudoku_%.o,$(wildcard $(SRC_SUDOKU_DIR)/*.cpp))

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

# Example target for curses_interaction.cpp
example2: $(DEP_OBJS) $(EXAMPLES_DIR)/curses_interaction.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/curses_interaction.cpp $(DEP_OBJS) -o $(EXAMPLE2_TARGET) $(CXXFLAGS)

# Example target for using_screens.cpp
example3: $(DEP_OBJS) $(EXAMPLES_DIR)/using_screens.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/using_screens.cpp $(DEP_OBJS) -o $(EXAMPLE3_TARGET) $(CXXFLAGS)

# Example target for using_screens.cpp
example4: $(DEP_OBJS) $(EXAMPLES_DIR)/check_term_size.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/check_term_size.cpp $(DEP_OBJS) -o $(EXAMPLE4_TARGET) $(CXXFLAGS)

# Compilation rules for each source directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/App_%.o: $(SRC_APP_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/Sudoku_%.o: $(SRC_SUDOKU_DIR)/%.cpp | $(BUILD_DIR)
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

run_example3: example3
	./$(EXAMPLE3_TARGET)

run_example4: example4
	./$(EXAMPLE4_TARGET)

# Clean rule to remove generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(EXAMPLE1_TARGET) $(EXAMPLE2_TARGET) $(EXAMPLE3_TARGET) $(EXAMPLE4_TARGET)

# Phony targets
.PHONY: all clean example1 example2 example3
