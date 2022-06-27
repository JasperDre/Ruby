#pragma once

#include "Entities/Entity.h"

#include <array>
#include <string>

class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class ProfessorOak : public Entity
{
public:
	ProfessorOak(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture);
	~ProfessorOak() override;

	void Update(float deltatime) override;
	void PathingUpdate(float delatime);
	void WalkingUpdate(float deltatime);
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void Move(SpriteDirection dir, float deltatime);
	void Pause() const;
	void Resume() const;
	void ResetPathFinder() const;
	void OnEvent(Event* anEvent) override {}
	void ResetInputSet() override;
	void NPCSeekStartPath() override;

	void SetMyState(AIStates aState) override;
	void SetInputSet(int* aPath) override;
	void SetCurrentInput(int aCurrentInput) override;
	void SetMyDirection(SpriteDirection aDirection) override;

	bool GetNextPath(Vector2Int anIndex);
	SpriteDirection CalculateNextInput(Vector2Int anIndex);
	[[nodiscard]] AIStates GetMyState() const override { return myState; }
	[[nodiscard]] bool IsNodeClearOnSpecial(int tx, int ty) const override;
	[[nodiscard]] bool IsColliding(Vector2Float NPCNewPosition) const;
	[[nodiscard]] int* GetInputSet() const override { return myPath; }
	[[nodiscard]] int GetCurrentInput() const override { return myCurrentInput; }
	[[nodiscard]] int GetNextTileFromSet(int aCurrentInput) const override { return myInputSet[aCurrentInput]; }
	[[nodiscard]] Vector2Int GetMyMinIndex() const override;
	[[nodiscard]] Vector2Int GetMyMaxIndex() const override;
	[[nodiscard]] int GetMyMapWidth() const override;
	[[nodiscard]] int GetMaxPathSize() const override;

private:
	std::array<std::string, Directions> myAnimationKeys;
	std::array<int, OakMaxPathSize> myInputSet;
	std::array<AnimatedSprite*, Directions> myAnimations;
	Vector2Float myNewPosition;
	Vector2Int myNewDestination;
	Vector2Int myIndex;
	TileMap* myTileMap;
	int* myPath;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	AIStates myState;
	int myCurrentInput;
	bool myIsPathingComplete;
	bool myIsFirstInput;
};