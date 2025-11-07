# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Ihelper

# Directories
SRC_DIR := .
HELPER_DIR := helper
OBJ_DIR := obj

# Files
SOURCES := $(SRC_DIR)/main.cpp $(HELPER_DIR)/functions.cpp
OBJECTS := $(OBJ_DIR)/main.o $(OBJ_DIR)/functions.o
TARGET := main

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Object file rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(HELPER_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Run the program
run: all
	./$(TARGET)
