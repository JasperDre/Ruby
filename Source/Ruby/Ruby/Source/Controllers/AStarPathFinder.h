#pragma once
class TileMap;
class GameObject;

struct PathNode
{
	enum PathNodeStatus
	{
		Unchecked,
		Open,
		Closed
	};
	
	int parentNodeIndex;
	PathNodeStatus Status;

	float F; // Current sum.
	float G; // Cost to get to current node.
	float H; // Heuristic: Manhatten distance to destination.
};
class AStarPathFinder
{
protected:

	int m_MapWidth;
	int m_MapHeight;
	int m_MyMinIndex;
	int m_MyMaxIndex;

	TileMap* m_pMyTileMap;
	GameObject* m_MyNPC;

	PathNode* m_Nodes;
	int m_NumNodes;

	int* m_OpenNodes;
	int m_NumOpen;

	// Internal methods.
	void AddToOpen(int nodeindex);
	void RemoveFromOpen(int nodeindex);
	int FindNodeIndexWithLowestFInOpen();

	int CalculateNodeIndex(int tx, int ty);
	int CheckIfNodeIsClearAndReturnNodeIndex(int tx, int ty);
	void AddNeighboursToOpenList(int nodeIndex, int endNodeIndex);

	float CalculateH(int nodeIndex, int endNodeIndex);

public:

	AStarPathFinder(TileMap* aTileMap, GameObject* aNPC);
	virtual ~AStarPathFinder();

	void Reset();

	// Start a search, supply the starting tile x,y and ending tile x,y.
	// Returns true if path found, false otherwise.
	bool FindPath(int sx, int sy, int ex, int ey);

	// Retrieve the final path, pass a nullptr for "path" to just get length of the path.
	int* GetPath(int* path, int maxdistance, int ex, int ey);

	GetForNodeIsClearOnSpecial m_GetNodeIsClearSpecial;

};