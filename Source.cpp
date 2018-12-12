/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#include <iostream>
#include <string>
#include "Graph.h"
#include "Tour.h"
#include "Node.h"
#include <chrono>
#include "NearestNeighbor.h"
#include "HeldKarp.h"
#include "NNOptimized.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc >= 1)
	{
		//Start clock ticks
		clock_t timerStart = clock(); 
		
		//Read in the file as as an arguement in the command line at run time.
		string infile = string(argv[1]);

		//Load input into graph
		Graph* graph = Graph::Load(infile);

		if (graph != nullptr)
		{
			int graphSize = (int)graph->GetNodes()->size();
			int solverRuns = 0;

			Tour* tour = nullptr;
			int minDistance = std::numeric_limits<int>::max();

			double worstRunTime = 0;
			double timeElapsed = 0;

			bool run = true;
			while (run)
			{
				clock_t runStart = clock();

				//Pass in choice of optimizer - None, TwoSwap, ThreeSwap, HeldKarpShuffle)
				NNOptimized nnoSolver(NNOptimized::HeldKarpShuffle, 7, 5);
				Tour* potentialTour = nnoSolver.Walk(graph);
				//cout << "Start Node: " << (*graph->GetNodes()->begin())->GetId() << " Distance " << potentialTour->TotalDistance << endl;

				if (potentialTour->TotalDistance < minDistance)
				{
					if (tour != nullptr)
					{
						delete tour;
					}
					tour = potentialTour;
					minDistance = potentialTour->TotalDistance;
				}
				else
				{
					delete potentialTour;
				}

				clock_t runEnd = clock();

				if ((runEnd - runStart) > worstRunTime)
				{
					worstRunTime = (runEnd - runStart);
				}

				solverRuns++;
				timeElapsed = runEnd - timerStart;

				if ((solverRuns < graphSize) && (((timeElapsed + (1.5 * worstRunTime)) * 1000. / CLOCKS_PER_SEC) < 160000))  //We can run another iteration
				{
					if (solverRuns > 0)
					{
						Nodes* nodes = graph->GetNodes();
						nodes->push_back(*nodes->begin());
						nodes->erase(nodes->begin());
						graph->ResetGraph();
					}
				}
				else
				{
					run = false;
				}
			}

			clock_t timerEnd = clock();
			double timeInMs = (double)(timerEnd - timerStart) * 1000. / CLOCKS_PER_SEC;
			cout << "Total Time: " << timeInMs << " Distance: " << tour->TotalDistance << endl;

			//Write output to text file
			string outFile = string(infile); //Make copy
			outFile.append(".tour");
			tour->Save(outFile);

			//Free memory
			delete tour;
			delete graph;
		}
		else
		{
			//If no input
			cout << "Error, no path available";
		}
	}
	else
	{
		//If file can't be opened
		cout << "Error, no input file";
	}
	//system("pause"); 
	return 0;
}