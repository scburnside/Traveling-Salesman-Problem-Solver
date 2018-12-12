/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.  
*****************************************************************************/

#pragma once
#include <string>
#include <vector>
#include "Node.h"

using namespace std; 

//For graph class
class Graph
{
public:
	Graph();
	~Graph();

	//Three parameters
	void AddNode(int id, int xCoord, int yCoord, int index);
	Nodes* GetNodes();
	void CalculateDistance(); 
	void ResetGraph();

	//int uses 2bytes vs 4 bytes
	int GetEdgeDistance(int firstNode, int secondNode); 

	//Load file into Graph
	static Graph* Load(string infile);

	//implemented min/max so we can avoid using alogirthm.h
	inline int min(int first, int second) 
	{
		if (first < second)
		{
			return first; 
		}
		else
		{
			return second; 
		}
	}
	inline int max(int first, int second)  
	{
		if (first > second)
		{
			return first;
		}
		else
		{
			return second;
		}
	}

private:
	//Collection of all the nodes in the graph
	Nodes NodeCollection;
	//2-dimension array of all the edge distances
	int** EdgeDistances; 
};


