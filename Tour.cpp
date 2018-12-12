/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#include <iostream>
#include <string>
#include "Tour.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std; 

//Default Constructor
Tour::Tour()
{
	TotalDistance = 0; 
}

//Destructor
Tour::~Tour()
{
}

void Tour::AddNode(Node* node, int distance)
{
	TourNodeCollection.push_back(node);
	TotalDistance += distance; 
}

void Tour::AppendTour(Tour* tour)
{
	TotalDistance = tour->TotalDistance;

	for (Nodes::iterator nIter = tour->TourNodeCollection.begin(); nIter != tour->TourNodeCollection.end(); nIter++)
	{
		TourNodeCollection.push_back(*nIter);
	}
}

//Outputs text file with n+1 lines
void Tour::Save(string outputFile)
{
	ofstream outFile;
	outFile.open(outputFile); 

	//Length of tour
	outFile << this->TotalDistance << endl;
	
	//List of identifiers in order they are visited
	for (int x = 0; x < TourNodeCollection.size() - 1; x++)
	{
		outFile << TourNodeCollection.at(x)->GetId() << endl;
	}

	outFile.close(); 
}

//If we 'optimized' or shuffled the tour, we'll need to walk the collection again and recalculate the  distances
void Tour::RecalculateDistance(Graph* graph)
{
	TotalDistance = 0;

	for (int x = 0; x < TourNodeCollection.size() - 1; x++)
	{
		TotalDistance += graph->GetEdgeDistance(TourNodeCollection[x]->index, TourNodeCollection[x + 1]->index);
	}
}
