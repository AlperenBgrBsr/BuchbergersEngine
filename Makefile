# Compiler settings
CXX = clang++
CXXFLAGS = -std=c++14 -Wall -g

# Target executable name
TARGET = main

# Source files
SRCS = main.cpp Buchbergers.cpp Polynomial.cpp Term.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files (for dependency tracking)
HDRS = Buchbergers.hpp Polynomial.hpp Term.hpp

# Default rule
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf *.dSYM
