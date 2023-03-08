CXX = g++
CXXFLAGS	= -std=c++2a -Wall
CXXGDB = -ggdb

all: main

main: main.cpp Product.o
	$(CXX) $(CXXFLAGS) main.cpp Product.o -o main

Product.o: Product.cpp
	$(CXX) $(CXXFLAGS) -c Product.cpp

clean:
	rm -f main