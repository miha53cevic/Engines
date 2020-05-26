# Makefile for simpleSDL

# Includes & Libraries for SDL2
INCLUDES = -I"./SDL2/include"
LIB = -L"./SDL2/lib/x86"
LIBS = -lSDL2main -lSDL2

# C++ settings
CXX = g++
CXXFLAGS = -Wall -o2 -std=c++17 -g $(INCLUDES)

# Source
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

app: $(obj)
	$(CXX) $(CXXFLAGS) -o build/$@ $^ $(LIB) $(LIBS)
	build/./app.exe
	rm -f $(obj)

.Phony clean:
	rm -f $(obj)