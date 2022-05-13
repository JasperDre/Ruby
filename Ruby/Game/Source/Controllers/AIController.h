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
	ivec2 SetNPCCurrentPosition(Vector2Float aNPCPosition);
	ivec2 CalculatedDirection(ivec2 aCurrentIndex, Vector2Float aDirection);
	bool GetNextPath();
	int RangeRandomIntAlg(int min, int max);

private:
	ivec2 m_MyNPCindex;
	ivec2 m_MyNewDestination;
	ivec2 m_NextTileColumnRow;
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