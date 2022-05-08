#pragma once

class TileMap;
class GameObject;
class AStarPathFinder;

class AIController
{
public:
	AIController(TileMap* aTileMap, int aMinIndex, int aMaxIndex, GameObject* aNPC);
	~AIController();

	bool GetNextPath();
	void ResetPathFinder();

	SpriteDirection MoveNPC();

	SpriteDirection CalculateNextInput();

	ivec2 SetNPCCurrentPosition(vec2 aNPCPosition);

	ivec2 CalculatedDirection(ivec2 aCurrentIndex, vec2 aDirection);

	int RangeRandomIntAlg(int min, int max);

private:
	ivec2 m_MyNPCindex;
	ivec2 m_MyNewDestination;
	ivec2 m_NextTileColumnRow;
	AStarPathFinder* m_MyPathFinder;
	TileMap* m_MyTileMap;
	GameObject* m_MyNPC;
	int* m_MyPath;
	SpriteDirection m_CurrentDirection;
	int m_MyMaxPathSize;
	int m_MyMinIndex;
	int m_MyMaxIndex;
	int m_MyMapWidth;
	int m_CurrentInput;
	bool m_PathingComplete;
};