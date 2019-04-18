all: QuantumLeap

main.o: main.cpp parser.h room.h gamemap.h player.h
	g++ -Wall -std=c++11 -g -c main.cpp

parser.o: parser.cpp parser.h
	g++ -Wall -std=c++11 -g -c parser.cpp

item.o: item.cpp item.h
	g++ -Wall -std=c++11 -g -c item.cpp

container.o: container.cpp container.h item.h
	g++ -Wall -std=c++11 -g -c container.cpp

player.o: player.h player.h gamemap.h
	g++ -Wall -std=c++11 -g -c player.cpp

room.o: room.h container.h
	g++ -Wall -std=c++11 -g -c room.cpp

QuantumLeap: main.o parser.o item.o container.o room.o player.o
	g++ -Wall -std=c++11 -g -o QuantumLeap main.o parser.o item.o container.o room.o player.o

.PHONY: clean
clean:
	rm -f *.o QuantumLeap

