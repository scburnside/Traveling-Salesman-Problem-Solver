/*****************************************************************************
** Description: Traveling Salesman Implementation using Nearest Neighbor
** and Dynamic Programming with additional optimisations.
*****************************************************************************/

#pragma once
#include "NearestNeighbor.h"


class NNOptimized :
	public NearestN
{
public:
	enum Optimizer : int
	{
		None = 0,
		SwapTwo			= 0x1 << 0,
		SwapThree		= 0x1 << 1,
		HeldKarpShuffle = 0x1 << 2,
		TwoOpt			= 0x1 << 3, 
		ThreeOpt		= 0x1 << 4
	};

	NNOptimized(int optimizers, int optParam1 = 8, int optParam2 = 5);
	~NNOptimized();

	virtual Tour* Walk(Graph* graph);

private:
	int Optimizers;
	int OptParam1;
	int OptParam2;

	void SwapTwo_Optimize(Tour* tour, Graph* graph);
	void SwapThree_Optimize(Tour* tour, Graph* graph);
	void HeldKarpShuffle_Optimize(Tour* tour, Graph* graph);
	void TwoOpt_Optimize(Tour* tour, Graph* graph);
	Tour* TwoOpt_Swap(Tour* tour, int i, int k);
};

