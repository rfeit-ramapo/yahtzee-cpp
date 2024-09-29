# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -I include

# Source files
SRC = $(wildcard cpp/*.cpp)

# Object files
OBJ = $(patsubst cpp/%.cpp, bin/%.o, $(SRC))

# Executable name
TARGET = yahtzee

# Build rules
all: $(TARGET)

$(TARGET): yahtzee.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

bin/%.o: cpp/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) yahtzee
