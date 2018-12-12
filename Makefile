# Makefile

all: source

source: Source.cpp graph.o node.o tour.o nearestneighbor.o optNN.o heldkarp.o
	g++ -std=c++0x -o source Source.cpp graph.o node.o tour.o nearestneighbor.o optNN.o heldkarp.o -lm

graph.o: Graph.h Graph.cpp
	g++ -std=c++0x -c Graph.cpp -o graph.o -lm

node.o: Node.h Node.cpp
	g++ -std=c++0x -c Node.cpp -o node.o -lm

tour.o: Tour.h Tour.cpp
	g++ -std=c++0x -c Tour.cpp -o tour.o

nearestneighbor.o: NearestNeighbor.h NearestNeighbor.cpp
	g++ -std=c++0x -c NearestNeighbor.cpp -o nearestneighbor.o

optNN.o: NNOptimized.h NNOptimized.cpp
	g++ -std=c++0x -c NNOptimized.cpp -o optNN.o

heldkarp.o: HeldKarp.h HeldKarp.cpp
	g++ -std=c++0x -c HeldKarp.cpp -o heldkarp.o

clean:
	rm *.o
	rm source
	rm *.tour
