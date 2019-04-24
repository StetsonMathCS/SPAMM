CXX=g++
CXX_FLAGS = -Wall -pedantic -g -O2 -ltelnet

all: main 

game_server.o: game_server.cpp game_server.cpp
	$(CXX) $(CXX_FLAGS) -c  game_server.cpp

main: game_server.o main.cpp
	$(CXX) $(CXX_FLAGS) -o main game_server.o main.cpp 

.PHONY: clean
clean:
	rm *.o main
