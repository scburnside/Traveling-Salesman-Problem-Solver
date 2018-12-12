/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#pragma once
#include "Graph.h"
#include "Node.h"
#include "Tour.h"

class HeldKarp
{
public:
	HeldKarp();
	~HeldKarp();

	Tour* Walk(Graph* graph);
	void Shuffle(Graph* graph, Tour* tour, int span, int step);

private:
	Tour* Cost(Node* currentNode, Node* lastNode, Nodes* unvisitedNodes);
	Nodes* SkipCopy(Node* skipNode, Nodes* unvisitedNodes);
	Graph* workingGraph;
};

