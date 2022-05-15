#pragma once

class TileMap;
class Entity;

enum class PathNodeStatus
{
	Unchecked,
	Open,
	Closed
};

struct PathNode
{
	int parentNodeIndex;
	PathNodeStatus Status;

	float F; // Current sum.
	float G; // Cost to get to current node.
	float H; // Heuristic: Manhatten distance to destination.
};

class AStarPathFinder
{
public:
	AStarPathFinder(TileMap* aTileMap, Entity* aNPC);
	virtual ~AStarPathFinder();

	void Reset();

	// Start a search, supply the starting tile x,y and ending tile x,y.
	// Returns true if path found, false otherwise.
	bool FindPath(int sx, int sy, int ex, int ey);
	// Retrieve the final path, pass a nullptr for "path" to just get length of the path.
	int* GetPath(int* path, int maxdistance, int ex, int ey) const;
	[[nodiscard]] int FindNodeIndexWithLowestFInOpen() const;
	[[nodiscard]] int CalculateNodeIndex(int tx, int ty) const;
	[[nodiscard]] int CheckIfNodeIsClearAndReturnNodeIndex(int tx, int ty) const;
	[[nodiscard]] int CalculateH(int nodeIndex, int endNodeIndex) const;

private:
	void AddToOpen(int nodeindex);
	void RemoveFromOpen(int nodeindex);
	void AddNeighboursToOpenList(int nodeIndex, int endNodeIndex);

	TileMap* m_pMyTileMap;
	Entity* m_MyNPC;
	PathNode* m_Nodes;
	int* m_OpenNodes;
	int m_MapWidth;
	int m_MapHeight;
	int m_NumNodes;
	int m_NumOpen;
};