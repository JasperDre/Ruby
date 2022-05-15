#pragma once

class TileMap;
class Entity;
class AStarPathFinder;

class AIController
{
public:
	AIController(TileMap* aTileMap, int aMinIndex, int aMaxIndex, Entity* aNPC);
	~AIController();

	void ResetPathFinder() const;

	SpriteDirection MoveNPC();
	SpriteDirection CalculateNextInput();
	static Vector2Int SetNPCCurrentPosition(Vector2Float aNPCPosition);
	static Vector2Int CalculatedDirection(Vector2Int aCurrentIndex, Vector2Float aDirection);
	bool GetNextPath();

private:
	Vector2Int m_MyNPCindex;
	Vector2Int m_MyNewDestination;
	Vector2Int m_NextTileColumnRow;
	AStarPathFinder* m_MyPathFinder;
	TileMap* m_MyTileMap;
	Entity* m_MyNPC;
	int* m_MyPath;
	SpriteDirection m_CurrentDirection;
	int m_MyMaxPathSize;
	int m_MyMinIndex;
	int m_MyMaxIndex;
	int m_MyMapWidth;
	int m_CurrentInput;
	bool m_PathingComplete;
};