#pragma once

#include "Entities/Entity.h"

#include <array>

class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class TownGirl : public Entity
{
public:
	TownGirl(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture);
	~TownGirl() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void OnEvent(Event* anEvent) override {}
	void Move(SpriteDirection dir, float deltatime);
	void Pause();
	void Resume();
	void ResetPathFinder() const;

	void SetStop(bool StopNPC);
	
	[[nodiscard]] bool IsColliding(Vector2Float NPCNewPosition) const;
	[[nodiscard]] int* GetInputSet() const override;
	[[nodiscard]] bool IsNodeClearOnSpecial(int tx, int ty) const override;
	[[nodiscard]] int GetMyMapWidth() const override;
	[[nodiscard]] int GetMaxPathSize() const override;
	SpriteDirection CalculateNextInput(Vector2Int anIndex);
	bool GetNextPath(Vector2Int anIndex);

private:
	std::array<std::string, NUM_DIRECTIONS> myAnimationKeys;
	std::array<int, MAXPATHSIZE_TOWN_NPC> myInputSet;
	std::array<AnimatedSprite*, NUM_DIRECTIONS> myAnimations;
	Vector2Float myNewPosition;
	Vector2Int myNewDestination;
	Vector2Int myIndex;
	TileMap* myTileMap;
	int* myPath;
	int myCurrentInput;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	bool myIsStopped;
	bool myIsFirstInput;
	bool myIsPathingComplete;
};