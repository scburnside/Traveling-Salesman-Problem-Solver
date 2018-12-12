/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#pragma once
#include "Graph.h"
#include "Node.h"

using namespace std; 

//Tour Class
class Tour
{
public:
	Tour();
	~Tour(); 

	void AddNode(Node* node, int distance); 
	void AppendTour(Tour* tour);
	void Save(string outfile);
	void RecalculateDistance(Graph* graph);  //For the optimization

	int TotalDistance;
	Nodes TourNodeCollection; 
};
