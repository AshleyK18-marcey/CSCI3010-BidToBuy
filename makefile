CXX = g++
CXXFLAGS	= -std=c++2a -Wall
CXXGDB = -ggdb

all: main

main: main.cpp Driver.o
	$(CXX) $(CXXFLAGS) main.cpp Driver.o -o main

test: Users.o Driver.o test.cpp
	$(CXX) $(CXXFLAGS) Users.o Driver.o test.cpp -o test

Driver.o: Driver.cpp
	$(CXX) $(CXXFLAGS) -c Driver.cpp

Product.o: Product.cpp
	$(CXX) $(CXXFLAGS) -c Product.cpp

Users.o: Users.cpp
	$(CXX) $(CXXFLAGS) -c Users.cpp

clean:
	rm -f main test Product.o Users.o Driver.o