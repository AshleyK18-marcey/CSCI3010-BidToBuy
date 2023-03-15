CXX = g++
CXXFLAGS	= -std=c++2a -Wall
CXXGDB = -ggdb

all: main

main: Users.o Conversation.o Product.o Driver.o main.cpp
	$(CXX) $(CXXFLAGS) Users.o Product.o Conversation.o Driver.o main.cpp -o main

test: Users.o Conversation.o Product.o Driver.o test.cpp
	$(CXX) $(CXXFLAGS)  Users.o Conversation.o Product.o Driver.o test.cpp -o test

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