# Makefile
# Compiler and flags
CXX = g++                   # Use g++ for C++ compilation
CXXFLAGS = -Wall -g         # Compiler flags (enable warnings, debugging symbols)

# Libraries
LIBS = -lfltk -lfltk_images -lX11 -lXext -lpthread -lm  # Libraries to link against

# Output file
TARGET = tuxy                # The output executable name

# Source files
SRC = tuxy.cpp               # The source file

# Object files
OBJ = $(SRC:.cpp=.o)         # The corresponding object file

# Default target to build the project
$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LIBS)  # Link object files and libraries

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@   # Compile the C++ source file

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)          # Remove object files and executable

# Rebuild everything (clean and then build)
rebuild: clean $(TARGET)

