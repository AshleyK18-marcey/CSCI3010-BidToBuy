CXX = g++
CXXFLAGS	= -std=c++2a -Wall
CXXGDB = -ggdb

all: main

main: Conversation.o Users.o Product.o Driver.o main.cpp
	$(CXX) $(CXXFLAGS) Conversation.o Users.o Product.o Driver.o main.cpp -o main

test: Conversation.o Users.o Product.o Driver.o test.cpp
	$(CXX) $(CXXFLAGS) Product.o Users.o Conversation.o Driver.o test.cpp -o test

Driver.o: Driver.cpp
	$(CXX) $(CXXFLAGS) -c Driver.cpp

Product.o: Product.cpp
	$(CXX) $(CXXFLAGS) -c Product.cpp

Users.o: Users.cpp
	$(CXX) $(CXXFLAGS) -c Users.cpp

Conversation.o: Conversation.cpp
	$(CXX) $(CXXFLAGS) -c Conversation.cpp

clean:
	rm -f main test Product.o Users.o Driver.o Conversation.o

clean_temp:
	rm -f Product.o Users.o Driver.o Conversation.o