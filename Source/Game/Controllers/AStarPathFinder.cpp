#include "AStarPathFinder.h"

#include <cassert>

#include "Entities/Entity.h"
#include "GameplayHelpers/TileMap.h"

AStarPathFinder::AStarPathFinder(TileMap* aTileMap, Entity* aNPC)
{
	myTileMap = aTileMap;
	myMapWidth = myTileMap->GetMapWidth();
	myMapHeight = myTileMap->GetMapHeight();
	myNumNodes = myMapWidth * myMapHeight;
	myNodes = new PathNode[myNumNodes];
	myOpenNodes = new int[myNumNodes];
	myNPC = aNPC;
	myNumOpen = 0;

	for (int i = 0; i < myNumNodes; i++)
	{
		(myNodes + i)->myParentNodeIndex = -1;
		(myNodes + i)->myStatus = PathNodeStatus::Unchecked;

		(myNodes + i)->mySum = 0;
		(myNodes + i)->myCost = FLT_MAX; // Set G to be highest cost possible, so any comparison will be better.
		(myNodes + i)->myDistance = -1; // -1 indicates the heuristic hasn't been calculated yet.
	}

	Reset();
}

AStarPathFinder::~AStarPathFinder()
{
	delete[] myOpenNodes;
	delete[] myNodes;
}

void AStarPathFinder::Reset()
{
	myNumOpen = 0;

	for (int i = 0; i < myNumNodes; i++)
	{
		myNodes[i].myParentNodeIndex = -1;
		myNodes[i].myStatus = PathNodeStatus::Unchecked;

		myNodes[i].mySum = 0;
		myNodes[i].myCost = FLT_MAX; // Set G to be highest cost possible, so any comparison will be better.
		myNodes[i].myDistance = -1; // -1 indicates the heuristic hasn't been calculated yet.
	}
}

bool AStarPathFinder::FindPath(int sx, int sy, int ex, int ey)
{
	// Reset the pathfinder.
	Reset();

	//Get the starting tile index and the destination tile index;
	const int startingIndex = CalculateNodeIndex(sx, sy);
	const int destinationIndex = CalculateNodeIndex(ex, ey);

	// Set starting node cost to zero, then add it to the open list to start the process.
	myNodes[startingIndex].myCost = 0.0f;
	myNodes[startingIndex].myDistance = static_cast<float>(CalculateH(startingIndex, destinationIndex));
	myNodes[startingIndex].mySum = myNodes[startingIndex].myCost + myNodes[startingIndex].myDistance;

	AddToOpen(startingIndex);

	while (true)
	{
		// Find the lowest F and remove it from the open list.
		const int lowestFNodeIndex = FindNodeIndexWithLowestFInOpen();
		RemoveFromOpen(lowestFNodeIndex);

		// If we found the end node, we're done.
		if (lowestFNodeIndex == destinationIndex)
			return true;

		// Mark the node as closed.
		myNodes[lowestFNodeIndex].myStatus = PathNodeStatus::Closed;
		// Add neighbours to open list.
		AddNeighboursToOpenList(lowestFNodeIndex, destinationIndex);
		// If we're out of nodes to check, then we're done without finding the end node.
		if (myNumOpen == 0)
			return false;
	}
}

int* AStarPathFinder::GetPath(int* path, int maxdistance, int ex, int ey) const
{
	int nodeIndex = CalculateNodeIndex(ex, ey);

	int length = 0;
	while (true)
	{
		if (path != nullptr && length >= maxdistance)
			return nullptr; // Path didn't fit in size.

		if (path != nullptr) // If no path array is passed in, just get the length.
		{
			*(path + length) = nodeIndex;
			length++;
		}

		nodeIndex = myNodes[nodeIndex].myParentNodeIndex;
		if (nodeIndex == -1)
			return path;
	}
}

void AStarPathFinder::AddToOpen(int nodeindex)
{
	assert(myNodes[nodeindex].myStatus != PathNodeStatus::Closed);

	// If the node isn't already open, then add it to the list.
	if (myNodes[nodeindex].myStatus != PathNodeStatus::Open)
	{
		myOpenNodes[myNumOpen] = nodeindex;
		myNumOpen++;
		myNodes[nodeindex].myStatus = PathNodeStatus::Open;
	}
}

void AStarPathFinder::RemoveFromOpen(int nodeindex)
{
	// Remove the node from the open list, since we don't care about order, replace the node we're removing with the last node in list.
	for (int i = 0; i < myNumOpen; i++)
	{
		if (myOpenNodes[i] == nodeindex)
		{
			myNumOpen--;
			myOpenNodes[i] = myOpenNodes[myNumOpen];
			return;
		}
	}
}

int AStarPathFinder::FindNodeIndexWithLowestFInOpen() const
{
	float lowestF = FLT_MAX;
	int indexofLowest = 0;

	// Loop through the nodes in the open list, then find and return the node with the lowest F score.
	for (int i = 0; i < myNumOpen; i++)
	{
		const int index = myOpenNodes[i];
		if (myNodes[index].mySum < lowestF)
		{
			lowestF = myNodes[index].mySum;
			indexofLowest = index;
		}
	}

	return indexofLowest;
}

int AStarPathFinder::CalculateNodeIndex(int tx, int ty) const
{
	assert(ty >= 0 && ty <= myMapHeight && tx >= 0 && tx <= myMapWidth);

	// Calculate the node index based on the tiles x/y.
	return (myMapWidth * ty) + tx;
}

int AStarPathFinder::CheckIfNodeIsClearAndReturnNodeIndex(int tx, int ty) const
{
	// If the node is out of bounds, return -1 (an invalid tile index).
	if (!myNPC->IsNodeClearOnSpecial(tx, ty))
		return -1;

	//If the node is already closed, return -1 (an invalid tile index).
	const int index = CalculateNodeIndex(tx, ty);

	if (myNodes[index].myStatus == PathNodeStatus::Closed)
		return -1;

	// If the node can't be walked on, return -1 (an invalid tile index).
	const TileInfo nodeTile = myTileMap->GetTileAtIndex(ty * myMapWidth + tx);
	if (!nodeTile.myIsWalkable)
		return -1;

	// Return a valid tile index.
	return CalculateNodeIndex(tx, ty);
}

void AStarPathFinder::AddNeighboursToOpenList(int aNodeIndex, int anEndNodeIndex)
{
	// Calculate the tile x/y based on the nodeIndex.
	const int tileColumn = aNodeIndex % myMapWidth;
	const int tileRow = aNodeIndex / myMapWidth;

	// Fill an array with the four neighbour tile indices. (use CheckIfNodeIsClearAndReturnNodeIndex() for each to see if it's valid).
	int neighbourNodes[4];

	for (int i = 0; i < 4; i++)
		neighbourNodes[i] = CheckIfNodeIsClearAndReturnNodeIndex(tileColumn + static_cast<int>(DirectionVector[i].myX), tileRow + static_cast<int>(DirectionVector[i].myY));

	// Loop through the array.
	for (const int neighbourNode : neighbourNodes)
	{
		// Check if the node to add has a valid node index.
		if (neighbourNode != -1)
		{
			constexpr int cost = 1; // Assume a travel cost of 1 for each tile.

			// Add the node to the open list.
			AddToOpen(neighbourNode);

			// If the cost to get there from here (new G) is less than the previous cost (old G) to get there, then overwrite the values.
			if (myNodes[neighbourNode].myCost > myNodes[aNodeIndex].myCost)
			{
				// Set the parent node.
				(myNodes + neighbourNode)->myParentNodeIndex = aNodeIndex;
				// Set the new cost to travel to that node.
				(myNodes + neighbourNode)->myCost = (myNodes + aNodeIndex)->myCost + cost;
				// If we haven't already calculated the heuristic, calculate it.
				(myNodes + neighbourNode)->myDistance = static_cast<float>(CalculateH(neighbourNode, anEndNodeIndex));
				// Calculate the final value.
				(myNodes + neighbourNode)->mySum = myNodes[neighbourNode].myCost + myNodes[neighbourNode].myDistance;
			}
		}
	}
}

int AStarPathFinder::CalculateH(int nodeIndex, int endNodeIndex) const
{
	// Calculate the h score using the Manhatten distance
	const Vector2Int nodeColumnRow = Vector2Int(nodeIndex % myMapWidth, nodeIndex / myMapWidth);
	const Vector2Int endNodeColumnRow = Vector2Int(endNodeIndex % myMapWidth, endNodeIndex / myMapWidth);
	return std::abs(nodeColumnRow.x - endNodeColumnRow.y) + abs(nodeColumnRow.y - endNodeColumnRow.x);
}