/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#include "NNOptimized.h"
#include "HeldKarp.h"

NNOptimized::NNOptimized(int optimizers, int optParam1, int optParam2)
{
	Optimizers = optimizers;
	OptParam1 = optParam1;
	OptParam2 = optParam2;
}

NNOptimized::~NNOptimized()
{
}

Tour * NNOptimized::Walk(Graph * graph)
{
	//We derive from NearestNeighbor, so just call the base class's implementation
	Tour* solution = NearestN::Walk(graph);

	//Lets see if we can run a post-walk optimizer on the result
	//These can be 'stacked' because the enum is a bitfield
	if ((Optimizers & Optimizer::SwapTwo) == Optimizer::SwapTwo)
	{
		SwapTwo_Optimize(solution, graph);
		solution->RecalculateDistance(graph);
	}
	
	if ((Optimizers & Optimizer::SwapThree) == Optimizer::SwapThree)
	{
		SwapThree_Optimize(solution, graph);
		solution->RecalculateDistance(graph);
	}
	
	if ((Optimizers & Optimizer::HeldKarpShuffle) == Optimizer::HeldKarpShuffle)
	{
		HeldKarpShuffle_Optimize(solution, graph);
		solution->RecalculateDistance(graph);
	}
	
	if ((Optimizers & Optimizer::TwoOpt) == Optimizer::TwoOpt)
	{
		TwoOpt_Optimize(solution, graph);
		solution->RecalculateDistance(graph);
	}

	return solution;
}

void NNOptimized::SwapTwo_Optimize(Tour * tour, Graph * graph)
{
	//This actually performs just like the 2-OPT implementation 
	//before I knew what 2-OPT was..
	bool hadImprovement = true;
	while (hadImprovement)
	{
		hadImprovement = false;
		//walk the calculated tour
		int tourSize = (int)tour->TourNodeCollection.size();
		for (int index = 0; index < tourSize - 4; index++)
		{
			//for each 4 node block, see if the middle two nodes 
			//cross paths and would be better swapped. 
			Node* startNode = tour->TourNodeCollection[index];
			Node* swapA = tour->TourNodeCollection[index + 1];
			Node* swapB = tour->TourNodeCollection[index + 2];
			Node* endNode = tour->TourNodeCollection[index + 3];

			int currentDistance = graph->GetEdgeDistance(startNode->index, swapA->index) +
				graph->GetEdgeDistance(swapA->index, swapB->index) +
				graph->GetEdgeDistance(swapB->index, endNode->index);

			int swapDistance = graph->GetEdgeDistance(startNode->index, swapB->index) +
				graph->GetEdgeDistance(swapB->index, swapA->index) +
				graph->GetEdgeDistance(swapA->index, endNode->index);

			if (swapDistance < currentDistance)
			{
				hadImprovement = true;
				tour->TourNodeCollection[index + 1] = swapB;
				tour->TourNodeCollection[index + 2] = swapA;
			}
		}
	}
}

void NNOptimized::SwapThree_Optimize(Tour * tour, Graph * graph)
{
	//This is the same as SwapTwo_Optimize but compares the middle 
	//three nodes in a 5 node collection..  This is technically known
	//as 3-OPT.
	int tourSize = (int)tour->TourNodeCollection.size();

	bool hadImprovement = true;
	while (hadImprovement)
	{
		hadImprovement = false;
		for (int index = 0; index < tourSize - 5; index++)
		{
			Node* startNode = tour->TourNodeCollection[index];
			Node* swapA = tour->TourNodeCollection[index + 1];
			Node* swapB = tour->TourNodeCollection[index + 2];
			Node* swapC = tour->TourNodeCollection[index + 3];
			Node* endNode = tour->TourNodeCollection[index + 4];

			int currentDistance = graph->GetEdgeDistance(startNode->index, swapA->index) +
				graph->GetEdgeDistance(swapA->index, swapB->index) +
				graph->GetEdgeDistance(swapB->index, swapC->index) +
				graph->GetEdgeDistance(swapC->index, endNode->index);

			int swapFirst = graph->GetEdgeDistance(startNode->index, swapA->index) +
				graph->GetEdgeDistance(swapA->index, swapC->index) +
				graph->GetEdgeDistance(swapC->index, swapB->index) +
				graph->GetEdgeDistance(swapB->index, endNode->index);

			int swapSecond = graph->GetEdgeDistance(startNode->index, swapB->index) +
				graph->GetEdgeDistance(swapB->index, swapA->index) +
				graph->GetEdgeDistance(swapA->index, swapC->index) +
				graph->GetEdgeDistance(swapC->index, endNode->index);

			int swapThird = graph->GetEdgeDistance(startNode->index, swapB->index) +
				graph->GetEdgeDistance(swapB->index, swapC->index) +
				graph->GetEdgeDistance(swapC->index, swapA->index) +
				graph->GetEdgeDistance(swapA->index, endNode->index);

			int swapFourth = graph->GetEdgeDistance(startNode->index, swapC->index) +
				graph->GetEdgeDistance(swapC->index, swapB->index) +
				graph->GetEdgeDistance(swapB->index, swapA->index) +
				graph->GetEdgeDistance(swapA->index, endNode->index);

			int swapFifth = graph->GetEdgeDistance(startNode->index, swapC->index) +
				graph->GetEdgeDistance(swapC->index, swapA->index) +
				graph->GetEdgeDistance(swapA->index, swapB->index) +
				graph->GetEdgeDistance(swapB->index, endNode->index);

			if (swapFirst < currentDistance && swapFirst < swapSecond && swapFirst < swapThird && swapFirst < swapFourth && swapFirst < swapFifth)
			{
				tour->TourNodeCollection[index + 1] = swapA;
				tour->TourNodeCollection[index + 2] = swapC;
				tour->TourNodeCollection[index + 3] = swapB;
				hadImprovement = true;
			}
			else if (swapSecond < currentDistance && swapSecond < swapFirst && swapSecond < swapThird && swapSecond < swapFourth && swapSecond < swapFifth)
			{
				tour->TourNodeCollection[index + 1] = swapB;
				tour->TourNodeCollection[index + 2] = swapA;
				tour->TourNodeCollection[index + 3] = swapC;
				hadImprovement = true;
			}
			else if (swapThird < currentDistance && swapThird < swapFirst && swapThird < swapSecond && swapThird < swapFourth && swapThird < swapFifth)
			{
				tour->TourNodeCollection[index + 1] = swapB;
				tour->TourNodeCollection[index + 2] = swapC;
				tour->TourNodeCollection[index + 3] = swapA;
				hadImprovement = true;
			}
			else if (swapFourth < currentDistance && swapFourth < swapFirst && swapFourth < swapSecond && swapFourth < swapThird && swapFourth < swapFifth)
			{
				tour->TourNodeCollection[index + 1] = swapC;
				tour->TourNodeCollection[index + 2] = swapB;
				tour->TourNodeCollection[index + 3] = swapA;
				hadImprovement = true;
			}
			else if (swapFifth < currentDistance && swapFifth < swapFirst && swapFifth < swapSecond && swapFifth < swapThird && swapFifth < swapFourth)
			{
				tour->TourNodeCollection[index + 1] = swapC;
				tour->TourNodeCollection[index + 2] = swapA;
				tour->TourNodeCollection[index + 3] = swapB;
				hadImprovement = true;
			}
		}
	}
	
}

//This re-uses an implementation of the Held-Karp dynamic programming solution
//If the graph has more than ~11 nodes the O(n^2 * 2^n) is so slow its completely
//not useable..  so instead we'll try walking it on subsects of the nearest neighbor 
//tour.
void NNOptimized::HeldKarpShuffle_Optimize(Tour * tour, Graph * graph)
{
	HeldKarp hk;
	//This 10 is the number of nodes in the set.  Exceeding 10 is a mistake
	//the step size is how many nodes we should step forward when the shuffle
	//reruns.  A lower number has a larger overlap so results can bubble further
	//but more iterations of a slow algorithm
	hk.Shuffle(graph, tour, OptParam1, OptParam2);
}

//This is the 2-OPT described in pseudocode on wikipedia 
//https://en.wikipedia.org/wiki/2-opt  
void NNOptimized::TwoOpt_Optimize(Tour * tour, Graph * graph)
{
	int eligibleToSwap = 5;
	bool hadImprovement = true;
	while (hadImprovement)
	{
		int minDistance = tour->TotalDistance;

		for (int i = 1; i < eligibleToSwap - 1; i++)
		{
			for (int k = i + 1; k < eligibleToSwap; k++)
			{
				Tour* possibleTour = TwoOpt_Swap(tour, i, k);
				possibleTour->RecalculateDistance(graph);

				if (possibleTour->TotalDistance < minDistance)
				{
					hadImprovement = true;

					for (int m = 0; m < tour->TourNodeCollection.size(); m++)
					{
						tour->TourNodeCollection[m] = possibleTour->TourNodeCollection[m];
					}
				}
				else
				{
					hadImprovement = false;
				}
				delete possibleTour;
			}
		}
	}
}

//2-OPT helper
Tour * NNOptimized::TwoOpt_Swap(Tour * tour, int i, int k)
{
	//swaps reverses a block in the tour to see if its more optimal if its connected backwards
	Tour* possibleTour = new Tour();
	for (int a = 0; a <= i - 1; a++)
	{
		possibleTour->TourNodeCollection.push_back(tour->TourNodeCollection[a]);
	}
	for (int b = k; b >= i; b--)
	{
		possibleTour->TourNodeCollection.push_back(tour->TourNodeCollection[b]);
	}
	for (int c = k + 1; c < tour->TourNodeCollection.size(); c++)
	{
		possibleTour->TourNodeCollection.push_back(tour->TourNodeCollection[c]);
	}

	return possibleTour;
}


