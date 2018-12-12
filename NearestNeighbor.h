/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#pragma once
#include "Graph.h"
#include "Node.h"
#include "Tour.h"

class NearestN
{
public:
	NearestN();
	~NearestN(); 

	virtual Tour* Walk(Graph* graph);

};
