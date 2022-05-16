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
	int myParentNodeIndex;
	PathNodeStatus myStatus;

	float mySum; // Current sum.
	float myCost; // Cost to get to current node.
	float myDistance; // Heuristic: Manhatten distance to destination.
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

	TileMap* myTileMap;
	Entity* myNPC;
	PathNode* myNodes;
	int* myOpenNodes;
	int myMapWidth;
	int myMapHeight;
	int myNumNodes;
	int myNumOpen;
};