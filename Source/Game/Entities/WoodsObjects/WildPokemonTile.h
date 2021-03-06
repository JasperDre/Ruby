#pragma once

#include "Entities/Entity.h"

#include <array>

class AStarPathFinder;
class ResourceManager;
class TileMap;

class WildPokemonTile : public Entity
{
public:
	WildPokemonTile(TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture);
	~WildPokemonTile() override;

	void Update(float deltatime) override;
	void OnEvent(Event* anEvent) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	virtual void PathingUpdate(float delatime);
	virtual void WalkingUpdate(float deltatime);
	virtual void TrackToPlayerUpdate(float deltatime) {}
	void Move(SpriteDirection dir, float deltatime);
	void ResetPathFinder() const;
	void ResetInputSet() override;
	void NPCSeekStartPath() override;

	void SetMyState(AIStates aState) override;
	void SetInputSet(int* aPath) override;
	void SetCurrentInput(int aCurrentInput) override;
	void SetMyDirection(SpriteDirection aDirection) override;
	virtual void SetMaxIndex(int anIndex) { myMaxIndex = anIndex; }
	virtual void SetMinIndex(int anIndex) { myMinIndex = anIndex; }

	[[nodiscard]] AIStates GetMyState() const override;
	[[nodiscard]] bool IsNodeClearOnSpecial(int tx, int ty) const override;
	[[nodiscard]] bool IsColliding(Vector2Float NPCNewPosition) const;
	[[nodiscard]] int* GetInputSet() const override;
	[[nodiscard]] int GetCurrentInput() const override;
	[[nodiscard]] int GetNextTileFromSet(int aCurrentInput) const override;
	[[nodiscard]] Vector2Int GetMyMinIndex() const override;
	[[nodiscard]] Vector2Int GetMyMaxIndex() const override;
	[[nodiscard]] int GetMyMapWidth() const override;
	[[nodiscard]] int GetMaxPathSize() const override;
	SpriteDirection CalculateNextInput(Vector2Int anIndex);
	bool GetNextPath(Vector2Int anIndex);

private:
	std::array<int, TownNPCMaxPathSize> myInputSet;
	Vector2Float myNewPosition;
	Vector2Int myNewDestination;
	Vector2Int myIndex;
	TileMap* myTileMap;
	int* myPath;
	int myCurrentInput;
	bool myIsFirstInput;
	bool myPathingComplete;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	AIStates myState;
};