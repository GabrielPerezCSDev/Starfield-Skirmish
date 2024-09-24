# Compiler and linker configurations
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iinclude
LDFLAGS = -lncurses

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INC_DIR := include

# Target executable
TARGET := $(BIN_DIR)/starfield_skirmish

# Find all cpp files in the src directory and its subdirectories
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
# Replace the src directory with the obj directory and change the file extension to .o
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Pattern rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)