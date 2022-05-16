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
	Vector2Int myNPCindex;
	Vector2Int myNewDestination;
	Vector2Int myNextTileColumnRow;
	AStarPathFinder* myPathFinder;
	TileMap* myTileMap;
	Entity* myNPC;
	int* myPath;
	SpriteDirection myCurrentDirection;
	int myMaxPathSize;
	int myMinIndex;
	int myMaxIndex;
	int myMapWidth;
	int myCurrentInput;
	bool myIsPathingComplete;
};