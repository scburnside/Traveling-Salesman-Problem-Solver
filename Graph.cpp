/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

//Default Constructor
Graph::Graph()
{
	EdgeDistances = nullptr; 
}

//Destructor
Graph::~Graph()
{
	//For EdgeDistancse[] contains a pointer to a second array.. i.e. the EdgeDiostances**
	if (EdgeDistances != nullptr)
	{
		int arraySize = (int)NodeCollection.size();

		for (int i = 0; i < arraySize; i++)
		{
			delete[] EdgeDistances[i];
		}
		delete[] EdgeDistances; 
	}
	
	//The graph *owns* the nodes, so when the graph gets destroyed, delete them.  The graph has to be
	//deleted after the tour though.
	for (Nodes::iterator Iter = NodeCollection.begin(); Iter != NodeCollection.end(); Iter++)
	{
		delete *Iter; 
	}
}

//Create and fill the EdgeDistances[][] with all the length between the two nodes
void Graph::CalculateDistance()
{
	int arraySize = (int)NodeCollection.size(); 

	//If the edge distances already exist and we're re-calculating. 
	//delete the old 2-d array and re-build it.
	if (EdgeDistances != nullptr)
	{
		int arraySize = (int)NodeCollection.size();

		for (int i = 0; i < arraySize; i++)
		{
			delete[] EdgeDistances[i];
		}
		delete[] EdgeDistances;
	}


	//Make array half the size - like a triangle to eliminate the duplicates
	EdgeDistances = new int*[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		EdgeDistances[i] = new int[arraySize - i]; 
	}

	//Fill array
	for (int j = 0; j < arraySize; j++)
	{
		Node* xCoordNode = NodeCollection[j]; 

		for (int k = 0; k < arraySize - j; k++)
		{
			Node* yCoordNode = NodeCollection[k + j]; 

			EdgeDistances[j][k] = Node::Distance(xCoordNode, yCoordNode); 
		}
	}
}

void Graph::AddNode(int id, int xCoord, int yCoord, int index)
{
	NodeCollection.push_back(new Node(id, xCoord, yCoord, index));
}

Nodes* Graph::GetNodes()
{
	return &NodeCollection; 
}


int Graph::GetEdgeDistance(int firstNodeIndex, int secondNodeIndex)
{
	//Since the array is 'triangular' we only have the distances from 
	//nodeA to nodeB.. so if we lookup by nodeB to nodeA, we need to do
	//some min/max swapping so we can index the 2-d array correctly
	int minIndex = min(firstNodeIndex, secondNodeIndex); 
	int maxIndex = max(firstNodeIndex, secondNodeIndex); 
	return EdgeDistances[minIndex][maxIndex - minIndex]; 
}

void Graph::ResetGraph()
{
	//If we're resetting the graph for another run, reset all the nodes to not visited.  
	//We also might have rotated the vector of nodes, so their index might be wrong in 
	//the edge distances, so update the index
	int index = 0;
	for (Nodes::iterator Iter = NodeCollection.begin(); Iter != NodeCollection.end(); Iter++)
	{
		(*Iter)->SetVisited(false);
		(*Iter)->index = index;
		index++;
	}

	//We might have rotated the vector of nodes, so the Edge Distances 2-d array is all
	//wrong, we need to delete it and re-generate.
	CalculateDistance();
}



//Load input into graph
Graph* Graph::Load(string infile)
{
	//New up graph
	Graph* graph = new Graph();

	ifstream stream(infile);

	int id, xcoor, ycoor, index = 0;
	while (stream >> id >> xcoor >> ycoor)
	{
		//Add all the nodes to the graph
		graph->AddNode(id, xcoor, ycoor, index); 
		index++;
	}
	
	//Close file
	stream.close();

	//Calculate all the edge distances
	graph->CalculateDistance(); 

	return graph;
}

