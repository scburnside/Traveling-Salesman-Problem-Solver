/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#include "Node.h"

using namespace std;

//Parameters for each Node
Node::Node( int id, int xCoor, int yCoor, int index)
{
	this->id = id; 
	this->xCoord = xCoor;
	this->yCoord = yCoor; 
	this->hasBeenVisited = false; 
	this->index = index;
}

//Free memory
Node::~Node()
{
}

int Node::GetId() const
{
	return id; 
}

int Node::GetXCoord() const
{
	return xCoord;
}

int Node::GetYCoord() const
{
	return yCoord; 
}

void Node::SetVisited(bool isVisited)
{
	hasBeenVisited = isVisited;
}

bool Node::IsVisited() const
{
	return hasBeenVisited;
}
