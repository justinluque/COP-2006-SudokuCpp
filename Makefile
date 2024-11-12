# Compiler
CXX := g++

# Directories
SRC_DIR := src
SRC_APP_DIR := src/App
SRC_SUDOKU_DIR := src/Sudoku
SRC_UTILITY_DIR := src/Utility

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
EXAMPLE5_TARGET := Example5.exe

# Compiler flags
CXXFLAGS := -Wall -Wextra -pedantic \
						-I$(INCLUDE_DIR) -I$(INCLUDE_APP_DIR) \
						-I$(INCLUDE_SUDOKU_DIR) -I$(INCLUDE_UTILITY_DIR) \
						-lncurses -DNCURSES_STATIC -O2

# Debug-specific flags
DEBUG_FLAGS := -g -O0  # Include debugging symbols, disable optimization

# Source files and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_APP_DIR)/*.cpp) $(wildcard $(SRC_SUDOKU_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp)) \
        $(patsubst $(SRC_APP_DIR)/%.cpp,$(BUILD_DIR)/App_%.o,$(wildcard $(SRC_APP_DIR)/*.cpp)) \
        $(patsubst $(SRC_SUDOKU_DIR)/%.cpp,$(BUILD_DIR)/Sudoku_%.o,$(wildcard $(SRC_SUDOKU_DIR)/*.cpp)) \
				$(patsubst $(SRC_UTILITY_DIR)/%.cpp,$(BUILD_DIR)/Utility_%.o,$(wildcard $(SRC_UTILITY_DIR)/*.cpp))

# Separate out main.o and the other objects for the example targets
MAIN_OBJ := $(BUILD_DIR)/main.o
DEP_OBJS := $(filter-out $(MAIN_OBJ), $(OBJS))

# Default rule
all: $(TARGET)

# Main target for Sudoku
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)

# Debug target
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

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

# Example target for solving_puzzles.cpp
example5: $(DEP_OBJS) $(EXAMPLES_DIR)/solving_puzzles.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/solving_puzzles.cpp $(DEP_OBJS) -o $(EXAMPLE5_TARGET) $(CXXFLAGS)

# Example target for creating_class_objects.cpp
debug_example1: $(DEP_OBJS) $(EXAMPLES_DIR)/creating_class_objects.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/creating_class_objects.cpp $(DEP_OBJS) -o $(EXAMPLE1_TARGET) $(CXXFLAGS) $(DEBUG_FLAGS)

# Example target for curses_interaction.cpp
debug_example2: $(DEP_OBJS) $(EXAMPLES_DIR)/curses_interaction.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/curses_interaction.cpp $(DEP_OBJS) -o $(EXAMPLE2_TARGET) $(CXXFLAGS) $(DEBUG_FLAGS)

# Example target for using_screens.cpp
debug_example3: $(DEP_OBJS) $(EXAMPLES_DIR)/using_screens.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/using_screens.cpp $(DEP_OBJS) -o $(EXAMPLE3_TARGET) $(CXXFLAGS) $(DEBUG_FLAGS)

# Example target for using_screens.cpp
debug_example4: $(DEP_OBJS) $(EXAMPLES_DIR)/check_term_size.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/check_term_size.cpp $(DEP_OBJS) -o $(EXAMPLE4_TARGET) $(CXXFLAGS) $(DEBUG_FLAGS)

# Example target for solving_puzzles.cpp
debug_example5: $(DEP_OBJS) $(EXAMPLES_DIR)/solving_puzzles.cpp | $(BUILD_DIR)
	$(CXX) $(EXAMPLES_DIR)/solving_puzzles.cpp $(DEP_OBJS) -o $(EXAMPLE5_TARGET) $(CXXFLAGS) $(DEBUG_FLAGS)

# Compilation rules for each source directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/App_%.o: $(SRC_APP_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/Sudoku_%.o: $(SRC_SUDOKU_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/Utility_%.o: $(SRC_UTILITY_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

examples: example1 example2 example3 example4 example5

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

run_example5: example5
	./$(EXAMPLE5_TARGET)

# Clean rule to remove generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(EXAMPLE1_TARGET) $(EXAMPLE2_TARGET) $(EXAMPLE3_TARGET) $(EXAMPLE4_TARGET) $(EXAMPLE5_TARGET)

# Phony targets
.PHONY: all clean example1 example2 example3 example4 example5 debug debuf_flags debug_example1 debug_example2 debug_example3 debug_example4 debug_example5
