#pragma once

#include "Entities/Entity.h"

#include <array>
#include <string>

class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class TownBoy : public Entity
{
public:
	TownBoy(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~TownBoy() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void OnEvent(Event* anEvent) override {}
	void Move(SpriteDirection dir, float deltatime);
	void Pause() const;
	void Resume() const;
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
	std::array<std::string, Directions> myAnimationKeys;
	std::array<int, TownNPCMaxPathSize> myInputSet;
	std::array<AnimatedSprite*, Directions> myAnimations;
	Vector2Float myNewPosition;
	Vector2Int myNewDestination;
	Vector2Int myIndex;
	TileMap* myTileMap;
	int* myPath;
	SpriteDirection myNewDirection;
	SpriteDirection myDirection;
	int myCurrentInput;
	bool myIsFirstInput;
	bool myIsPathingComplete;
	bool myIsStopped;
};
