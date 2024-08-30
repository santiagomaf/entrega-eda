# Compiler
CXX = g++

# Compiler flags


# Name of the source file (without the extension)
TARGET = tarea1

# Source file
SRC = $(TARGET).cpp

# Default target to build and run
all: $(TARGET)
	./$(TARGET)

# Rule to compile the source file into an executable
$(TARGET): $(SRC)
	$(CXX) -o $(TARGET) $(SRC)

# Clean up the executable
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
