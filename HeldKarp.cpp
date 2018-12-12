/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#include "HeldKarp.h"
#include <limits>

HeldKarp::HeldKarp()
{
	workingGraph = nullptr;
}


HeldKarp::~HeldKarp()
{
}

Tour* HeldKarp::Walk(Graph* graph)
{
	workingGraph = graph;
	Nodes* nodes = graph->GetNodes();

	//Copy the first subset 
	Node* currentNode = nodes->at(0);
	Nodes* unvisitedNodes = SkipCopy(currentNode, nodes);

	//We need to build our tour along the way
	Tour* solution = new Tour();
	solution->AddNode(currentNode, 0);

	//Call the recursive Cost() function and append it to the tour
	solution->AppendTour(Cost(currentNode, currentNode, unvisitedNodes));

	//Add the last node back to the start to complete the tour
	int distance = workingGraph->GetEdgeDistance(solution->TourNodeCollection.rbegin().operator*()->index, 0);
	solution->AddNode(currentNode, distance);

	return solution;
}

void HeldKarp::Shuffle(Graph* graph, Tour* tour, int span, int step)
{
	//We can't run Held-Karp Dynamic Programming on the graph because its not performant, but we can
	//run it on smaller subsets of it.  We'll perform the DP solution on a span (a subset of the results)
	//and do that repeatedly on the graph, moving the span window along by 'step' units.  
	//So..  span = 10, step 3:   Cost( tour[0..9] ), Cost( tour[3..12] ), Cost( tour[6..15] )...
	workingGraph = graph;
	int startSpan = span;
	int tourSize = (int)tour->TourNodeCollection.size();
	int index = 0;
	bool lastRun = false;
	while (index < tourSize && !lastRun)
	{
		Node* startNode = tour->TourNodeCollection[index];
		Node* endNode = tour->TourNodeCollection[index + span - 1];

		//Grab our base unmodified sub-tour
		Tour* baseTour = new Tour();
		for (int a = 0; a < span - 1; a++)
		{
			baseTour->AddNode(tour->TourNodeCollection[index + a + 1], graph->GetEdgeDistance(tour->TourNodeCollection[index + a]->index, tour->TourNodeCollection[index + a + 1]->index));
		}

		//Copy the sub-tour so we can perform a walk on it
		Nodes* unvisitedNodes = new Nodes();
		for (int x = 1; x < span - 1; x++)
		{
			unvisitedNodes->push_back(tour->TourNodeCollection[index + x]);
		}

		//Walk the sub-tour to see if we can beat the nearest neighbor tour
		Tour* subTour = Cost(startNode, endNode, unvisitedNodes);

		//if we beat the nearest neighbor tour, replace this span with it.
		if (subTour->TotalDistance < baseTour->TotalDistance)
		{
			for (int swap = 1; swap < subTour->TourNodeCollection.size(); swap++)
			{
				tour->TourNodeCollection[index + swap] = subTour->TourNodeCollection[subTour->TourNodeCollection.size() - swap];
			}
		}

		//Step the window forward by step.  if we've hit the end.. update span so we don't blow an index
		index += step;
		if ((tourSize - index) < span)
		{
			//If we're in the last block of a span and the tour array is shorter,
			//decrease the span so we don't exceed the bounds
			lastRun = true;
			span = tourSize - index;
		}
		delete baseTour;
		delete subTour;
	}

	//Run it in reverse!  We should probably get rid of the duplicate code but I'm tired
	span = startSpan;
	index = tourSize - span;
	lastRun = false;
	while (index > 0 && !lastRun)
	{
		Node* startNode = tour->TourNodeCollection[index];
		Node* endNode = tour->TourNodeCollection[index + span - 1];

		//Grab our base unmodified sub-tour
		Tour* baseTour = new Tour();
		for (int a = 0; a < span - 1; a++)
		{
			baseTour->AddNode(tour->TourNodeCollection[index + a + 1], graph->GetEdgeDistance(tour->TourNodeCollection[index + a]->index, tour->TourNodeCollection[index + a + 1]->index));
		}

		//Copy the sub-tour so we can perform a walk on it
		Nodes* unvisitedNodes = new Nodes();
		for (int x = 1; x < span - 1; x++)
		{
			unvisitedNodes->push_back(tour->TourNodeCollection[index + x]);
		}

		//Walk the sub-tour to see if we can beat the nearest neighbor tour
		Tour* subTour = Cost(startNode, endNode, unvisitedNodes);

		//if we beat the nearest neighbor tour, replace this span with it.
		if (subTour->TotalDistance < baseTour->TotalDistance)
		{
			for (int swap = 1; swap < subTour->TourNodeCollection.size(); swap++)
			{
				tour->TourNodeCollection[index + swap] = subTour->TourNodeCollection[subTour->TourNodeCollection.size() - swap];
			}
		}

		//Step the window forward by step.  if we've hit the end.. update span so we don't blow an index
		index -= step;
		if ((index - span) < 0)
		{
			//If we're in the last block of a span and the tour array is shorter,
			//decrease the span so we don't exceed the bounds
			lastRun = true;
			span = index - 0;
		}
		delete baseTour;
		delete subTour;
	}
}

//Held-Carp recursive cost function from the pseudo-algorithm on: 
// https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/
//  If size of S is 2, then S must be {1, i},
//  C(S, i) = dist(1, i)
//  Else if size of S is greater than 2.
//  C(S, i) = min{ C(S - {i}, j) + dis(j, i) } where j belongs to S, j != i and j != 1.
Tour* HeldKarp::Cost(Node* currentNode, Node* lastNode, Nodes* unvisitedNodes)
{
	int minDistance = std::numeric_limits<int>::max();
	Tour* minRoute = new Tour();

	if (unvisitedNodes->size() == 0)
	{
		//recursive base case... satisfying: 
		//  If size of S is 2, then S must be {1, i},
		//  C(S, i) = dist(1, i)
		//Normally the lastNode is the start node, but this is a small modification to pass in a different lastNode so
		//we can work on shorter runs of a tour
		int distance = workingGraph->GetEdgeDistance(currentNode->index, lastNode->index);
		minRoute->AddNode(lastNode, distance);
	}
	else
	{
		//  Else if size of S is greater than 2.
		//  C(S, i) = min{ C(S - {i}, j) + dis(j, i) } where j belongs to S, j != i and j != 1.
		for (Nodes::iterator nIter = unvisitedNodes->begin(); nIter != unvisitedNodes->end(); nIter++)
		{
			Node* nextNode = *nIter;
			Nodes* nextUnvisited = SkipCopy(nextNode, unvisitedNodes);

			//C(S - {i}, j)  RECURSIVE CALL
			Tour* subRoute = Cost(nextNode, lastNode, nextUnvisited);
			
			//dis(j, i)
			int nodeDistance = workingGraph->GetEdgeDistance(currentNode->index, nextNode->index);

			//Add them together
			int subDistance = nodeDistance + subRoute->TotalDistance;

			//If its a potential min(), replace the last min and keep iterating over the nodes
			if (subDistance < minDistance)
			{
				minDistance = subDistance;
				if (minRoute != nullptr)
				{
					delete minRoute;
				}
				minRoute = subRoute;
				minRoute->AddNode(nextNode, nodeDistance);
			}
			else
			{
				delete subRoute;
			}
			delete nextUnvisited;
		}
	}
	return minRoute;

}

//This is super inefficient, we should come up with a better way of splitting the collection
Nodes* HeldKarp::SkipCopy(Node* skipNode, Nodes* unvisitedNodes)
{
	//This just copies a list of Nodes, but subtracts the next on from the set so the recursion
	//can work on smaller and smaller sets until we hit the base case.
	Nodes* newUnvisitedNodes = new Nodes();

	//For each node
	for (Nodes::iterator nIter = unvisitedNodes->begin(); nIter != unvisitedNodes->end(); nIter++)
	{
		if ((*nIter) != skipNode)
		{
			//Add it if its not the skipNode
			newUnvisitedNodes->push_back((*nIter));
		}
	}

	//return a subset of the last set of unvistedNodes
	return newUnvisitedNodes;
}
