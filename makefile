CXX = g++
CXXFLAGS	= -std=c++2a -Wall
CXXGDB = -ggdb

all: main

main: main.cpp Driver.o
	$(CXX) $(CXXFLAGS) main.cpp Driver.o -o main

test: Driver.o test.cpp
	$(CXX) $(CXXFLAGS) test.cpp Driver.o -o test

Driver.o: Users.o Product.o Driver.cpp
	$(CXX) $(CXXFLAGS) -c Product.o Users.o Driver.cpp

Product.o: Product.cpp
	$(CXX) $(CXXFLAGS) -c Product.cpp

Users.o: Product.o Users.cpp
	$(CXX) $(CXXFLAGS) -c Users.cpp Product.o

clean:
	rm -f main test Product.o Users.o Driver.o