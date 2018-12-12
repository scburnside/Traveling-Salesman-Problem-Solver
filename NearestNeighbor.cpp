/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#include "NearestNeighbor.h"
#include <limits>

//Default Constructor
NearestN::NearestN()
{
}

NearestN::~NearestN()
{
}

Tour* NearestN::Walk(Graph* graph)
{
	Tour* solution = new Tour();

	Nodes* nodes = graph->GetNodes();
	int graphSize = (int)nodes->size(); 

	//Start with first node
	Node* startNode = nodes->at(0); 
	Node* currentNode = startNode;
	int nodeIndex = 0;
	int count = 1; //Nodes added to solution
	solution->AddNode(currentNode, 0);
	
	while (count < graphSize) //Count down all nodes in the graph
	{
		int next = -1;
		int nextDistance = std::numeric_limits<int>::max(); //Highest potential value
		for (int x = 1; x < graphSize; x++)
		{
			//If neighboring nodes haven't been visited
			if (!nodes->at(x)->IsVisited())
			{
				int maybeEdge = graph->GetEdgeDistance(nodeIndex, x);
				if (maybeEdge < nextDistance)
				{
					//Add to tour
					next = x;
					nextDistance = maybeEdge; 
				}
			}
		}
		nodeIndex = next;
		currentNode = nodes->at(nodeIndex);
		currentNode->SetVisited(); //Mark current Node as visited

		solution->AddNode(currentNode, nextDistance);

		count++; 
	}
	int finalDistance = graph->GetEdgeDistance(0, nodeIndex);
	
	//Add startNode to solution & complete tour home
	solution->AddNode(startNode, finalDistance);

	return solution;
}
