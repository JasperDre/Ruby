#include "GamePCH.h"
#include "AStarPathFinder.h"

#include "Entities/Entity.h"
#include "GameplayHelpers/TileMap.h"

AStarPathFinder::AStarPathFinder(TileMap* aTileMap, Entity* aNPC)
{
	m_pMyTileMap = aTileMap;
	m_MapWidth = m_pMyTileMap->GetMapWidth();
	m_MapHeight = m_pMyTileMap->GetMapHeight();
	m_NumNodes = m_MapWidth * m_MapHeight;
	m_Nodes = new PathNode[m_NumNodes];
	m_OpenNodes = new int[m_NumNodes];
	m_MyNPC = aNPC;
	m_NumOpen = 0;

	for (int i = 0; i < m_NumNodes; i++)
	{
		(m_Nodes + i)->parentNodeIndex = -1;
		(m_Nodes + i)->Status = PathNodeStatus::Unchecked;

		(m_Nodes + i)->F = 0;
		(m_Nodes + i)->G = FLT_MAX; // Set G to be highest cost possible, so any comparison will be better.
		(m_Nodes + i)->H = -1; // -1 indicates the heuristic hasn't been calculated yet.
	}

	Reset();
}

AStarPathFinder::~AStarPathFinder()
{
	delete[] m_Nodes;
	delete[] m_OpenNodes;
}

void AStarPathFinder::Reset()
{
	m_NumOpen = 0;

	for (int i = 0; i < m_NumNodes; i++)
	{
		m_Nodes[i].parentNodeIndex = -1;
		m_Nodes[i].Status = PathNodeStatus::Unchecked;

		m_Nodes[i].F = 0;
		m_Nodes[i].G = FLT_MAX; // Set G to be highest cost possible, so any comparison will be better.
		m_Nodes[i].H = -1; // -1 indicates the heuristic hasn't been calculated yet.
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
	m_Nodes[startingIndex].G = 0.0f;
	m_Nodes[startingIndex].H = static_cast<float>(CalculateH(startingIndex, destinationIndex));
	m_Nodes[startingIndex].F = m_Nodes[startingIndex].G + m_Nodes[startingIndex].H;

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
		m_Nodes[lowestFNodeIndex].Status = PathNodeStatus::Closed;
		// Add neighbours to open list.
		AddNeighboursToOpenList(lowestFNodeIndex, destinationIndex);
		// If we're out of nodes to check, then we're done without finding the end node.
		if (m_NumOpen == 0)
			return false;
	}
}

int* AStarPathFinder::GetPath(int* path, int maxdistance, int ex, int ey)
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

		nodeIndex = m_Nodes[nodeIndex].parentNodeIndex;
		if (nodeIndex == -1)
			return path;
	}
}

void AStarPathFinder::AddToOpen(int nodeindex)
{
	assert(m_Nodes[nodeindex].Status != PathNodeStatus::Closed);

	// If the node isn't already open, then add it to the list.
	if (m_Nodes[nodeindex].Status != PathNodeStatus::Open)
	{
		m_OpenNodes[m_NumOpen] = nodeindex;
		m_NumOpen++;
		m_Nodes[nodeindex].Status = PathNodeStatus::Open;
	}
}

void AStarPathFinder::RemoveFromOpen(int nodeindex)
{
	// Remove the node from the open list, since we don't care about order, replace the node we're removing with the last node in list.
	for (int i = 0; i < m_NumOpen; i++)
	{
		if (m_OpenNodes[i] == nodeindex)
		{
			m_NumOpen--;
			m_OpenNodes[i] = m_OpenNodes[m_NumOpen];
			return;
		}
	}
}

int AStarPathFinder::FindNodeIndexWithLowestFInOpen()
{
	float LowestF = FLT_MAX;
	int IndexofLowest = 0;

	// Loop through the nodes in the open list, then find and return the node with the lowest F score.
	for (int i = 0; i < m_NumOpen; i++)
	{
		int anIndex = m_OpenNodes[i];
		if (m_Nodes[anIndex].F < LowestF)
		{
			LowestF = m_Nodes[anIndex].F;
			IndexofLowest = anIndex;
		}
	}

	return IndexofLowest;
}

int AStarPathFinder::CalculateNodeIndex(int tx, int ty)
{
	assert(ty >= 0 && ty <= m_MapHeight && tx >= 0 && tx <= m_MapWidth);

	// Calculate the node index based on the tiles x/y.
	return (m_MapWidth * ty) + tx;
}

int AStarPathFinder::CheckIfNodeIsClearAndReturnNodeIndex(int tx, int ty)
{
	// If the node is out of bounds, return -1 (an invalid tile index).

	if (!m_MyNPC->GetNodeIsClearOnSpecial(tx, ty))
		return -1;

	//If the node is already closed, return -1 (an invalid tile index).
	int anIndex = CalculateNodeIndex(tx, ty);

	if (m_Nodes[anIndex].Status == PathNodeStatus::Closed)
		return -1;

	// If the node can't be walked on, return -1 (an invalid tile index).

	TileInfo aNodeTile = m_pMyTileMap->GetTileAtIndex(ty * m_MapWidth + tx);

	if (aNodeTile.IsWalkable == false)
	{
		return -1;
	}

	// Return a valid tile index.
	return CalculateNodeIndex(tx, ty);
}

void AStarPathFinder::AddNeighboursToOpenList(int nodeIndex, int endNodeIndex)
{
	// Calculate the tile x/y based on the nodeIndex.
	int TileColumn = nodeIndex % m_MapWidth;
	int TileRow = nodeIndex / m_MapWidth;

	// Fill an array with the four neighbour tile indices. (use CheckIfNodeIsClearAndReturnNodeIndex() for each to see if it's valid).
	int NeighbourNodes[4];

	for (int i = 0; i < 4; i++)
		NeighbourNodes[i] = CheckIfNodeIsClearAndReturnNodeIndex(TileColumn + DIRECTIONVECTOR[i].myX, TileRow + DIRECTIONVECTOR[i].myY);

	// Loop through the array.
	for (int i = 0; i < 4; i++)
	{
		// Check if the node to add has a valid node index.
		if (NeighbourNodes[i] != -1)
		{
			int cost = 1; // Assume a travel cost of 1 for each tile.

			// Add the node to the open list.
			AddToOpen(NeighbourNodes[i]);

			// If the cost to get there from here (new G) is less than the previous cost (old G) to get there, then overwrite the values.
			if (m_Nodes[NeighbourNodes[i]].G > m_Nodes[nodeIndex].G)
			{
				// Set the parent node.
				(m_Nodes + NeighbourNodes[i])->parentNodeIndex = nodeIndex;
				// Set the new cost to travel to that node.
				(m_Nodes + NeighbourNodes[i])->G = (m_Nodes + nodeIndex)->G + cost;
				// If we haven't already calculated the heuristic, calculate it.
				(m_Nodes + NeighbourNodes[i])->H = CalculateH(NeighbourNodes[i], endNodeIndex);
				// Calculate the final value.
				(m_Nodes + NeighbourNodes[i])->F = m_Nodes[NeighbourNodes[i]].G + m_Nodes[NeighbourNodes[i]].H;
			}
		}
	}
}

int AStarPathFinder::CalculateH(int nodeIndex, int endNodeIndex) const
{
	// Calculate the h score using the Manhatten distance
	const ivec2 nodeColumnRow = ivec2(nodeIndex % m_MapWidth, nodeIndex / m_MapWidth);
	const ivec2 endNodeColumnRow = ivec2(endNodeIndex % m_MapWidth, endNodeIndex / m_MapWidth);
	return std::abs(nodeColumnRow.x - endNodeColumnRow.y) + abs(nodeColumnRow.y - endNodeColumnRow.x);
}