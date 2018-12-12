/*********************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*********************************************************************/

#pragma once
#include <vector>
#include <string>
#include <cmath>

using namespace std;

//Node Class
class Node
{
public:
	Node(int id, int xCoor, int yCoor, int index);
	~Node();

	int GetId() const;
	int GetXCoord() const;
	int GetYCoord() const; 
	void SetVisited(bool isVisited = true);
	bool IsVisited() const; 
	
	inline static int Distance(Node* firstNode, Node* secondNode)
	{
		int xDiff = firstNode->GetXCoord() - secondNode->GetXCoord(); 
		//int xSubTotal = xDiff * xDiff; 

		int yDiff = firstNode->GetYCoord() - secondNode->GetYCoord();
		//int ySubtotal = yDiff * yDiff;
		//int total = xSubTotal + ySubtotal; 
		//int val = (int)abs(sqrt((float) total));

		int val = (int)round(hypot(xDiff, yDiff));

		return (int)val;
	}

	int index;  //quick lookup for its index in the edge distance matrix
	int id; 
	int xCoord;
	int yCoord;
	bool hasBeenVisited; 
};

typedef vector<Node*>Nodes;





