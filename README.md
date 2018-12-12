# Traveling Salesman Problem Solver

The traveling salesman problem is a well-known NP-complete problem that has no known polynomial time solution. 
The problem states that we have a salesman that starts at a city and needs to travel around to different cities, 
visiting each city once, and returning home to his or her starting city. The problem asks to find the minimum 
distance (cost) tour to accomplish this.

The Traveling Salesman Problem Solver finds the best solution possible to one or more test instances within a fixed 
amount of time. The default is 3 minutes.  

Completed: June 5, 2018 by Samantha Burnside.  Tested by Cody Kelley. 

# Held-Karp algorithm
TSP can be solved using a dynamic programming approach known as the Held-Karp algorithm, also known as the 
Bellman-Held-Karp algorithm. Because the traveling salesman must visit each city exactly once and end up as his 
starting city, this problem is an extension of the Hamiltonian cycle problem.  This solution gives an optimal tour. 

# Nearest Neighbor
Nearest Neighbor is an approximation algorithm that can be used to solve the Traveling salesman problem. It works 
by selecting the nearest, least costly node. The node is marked as visited and then ignored. The program runs 
until all the nodes are visited.  When all nodes are visited, add the starting node to complete the tour home.

# This solution
To meet the time constraint of 3 minutes or less, we chose to implement the Nearest Neighbor algorithm along with 
the Held-Karp algorithm as an optimizer. Nearest Neighbor was selected as a base method because of 
its speed. When tested, it resulted in the fastest running calculations. Because it’s a heuristic algorithm it 
doesn’t produce an exact solution, but on average produces an OPT-1.25 result. We also chose the Held-Karp 
algorithm because of its accuracy. It produces an exact result but at the cost of speed. When tested, it resulted 
in the slowest running calculations. In cases where the Held-Karp algorithm is run on a small set, the algorithm 
runs in a feasible amount of time. We made the best of both algorithms by first running the Nearest Neighbor 
method on the entire set, which quickly gave us a close approximation to the optimal path. We then broke that path
into multiple subpaths to run the Held-Karp method on. The Held-Karp method optimizes the subpath lengths but because 
the subpaths are smaller sets the algorithm doesn’t take as long to execute. 

# Modified Held-Karp
We couldn’t run Held-Karp Dynamic Programming on the graph because its not performant. If the graph has more than 
~11 nodes the O(n​^2​^​n​) is so slow it is completely unusable. So the algorithm was performed on smaller subsets of 
the tour after Nearest Neighbor.  The DP solution is performed on a span (a subset of the results) repeatedly on 
the tour, moving the span window along by 'step' units. (i.e. span = 10, step 3: Cost( tour[0..9] ), 
Cost( tour[3..12] ), Cost( tour[6..15] )...) This achieves the best possible subtour for the ‘span’ nodes. 
By overlapping the span with a small step, some number of nodes is allowed to ‘bubble’ out into the next subtour. 
Instead of O(n​^2​^​n​) we have O(n/step * 2^​span​). 

# Input specifications:
A problem instance will always be given to you as a text file.
Each line defines a city and each line has three numbers separated by white space.
	- The first number is the city identifier
	- The second number is the city’s x-coordinate
	- The third number is the city’s y-coordinate

#  Output specifications:
Solution is outputted into another text file with n+1 lines, where n is the number of
cities.
	- The first line is the length of the tour the solution computes.
	- The next n lines should contain the city identifiers in the order they are visited by the tour.
	- Each city must be listed exactly once in this list. 
	
# Project files:
1) README.txt
2) Makefile
3) Source.cpp
4) Source.h
5) Graph.cpp
6) Graph.h
7) Node.cpp
8) Node.h
9) NearestNeighbor.cpp
10) NearestNeighbor.h
11) HeldKarp.cpp
12) HeldKarp.h
13) NNOptimized.cpp
14) NNOptimized.h
15) Solution files (*.txt.tour)

# Usage

To compile:
        make all

Once compiled:
        ./source <name of text file to read>
	example: ./source tsp_example_1.txt

Solutions are created in a .txt with same name as input file with .tour appended.
	example:	input file is "tsp_example_1.txt"
			solution file is "tsp_example_1.txt.tour"

To clean up:
	make clean

# Contributing

Please feel free to contribute!

# License

The MIT License (MIT) 2018 - Samantha Burnside. Please have a look at the LICENSE.md for more details.