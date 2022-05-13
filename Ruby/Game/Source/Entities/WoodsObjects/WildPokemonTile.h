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
	virtual void TrackToPlayerUpdate(float deltatime);
	void Move(SpriteDirection dir, float deltatime);
	void ResetPathFinder() const;
	void ResetInputSet() override;
	void NPCSeekStartPath() override;

	void SetMyState(AI_States aState) override;
	void SetInputSet(int* aPath) override;
	void SetCurrentInput(int aCurrentInput) override;
	void SetMyDirection(SpriteDirection aDirection) override;
	virtual void SetMaxIndex(int anIndex) { myMaxIndex = anIndex; }
	virtual void SetMinIndex(int anIndex) { myMinIndex = anIndex; }

	[[nodiscard]] AI_States GetMyState() const override;
	[[nodiscard]] bool GetNodeIsClearOnSpecial(int tx, int ty) const override;
	[[nodiscard]] bool CheckForCollision(Vector2Float NPCNewPosition) const;
	[[nodiscard]] int* GetInputSet() const override;
	[[nodiscard]] int GetCurrentInput() const override;
	[[nodiscard]] int GetNextTileFromSet(int aCurrentInput) const override;
	[[nodiscard]] ivec2 GetMyMinIndex() const override;
	[[nodiscard]] ivec2 GetMyMaxIndex() const override;
	[[nodiscard]] int GetMyMapWidth() const override;
	[[nodiscard]] int GetMaxPathSize() const override;
	[[nodiscard]] int RangeRandomIntAlg(int min, int max) const override;
	SpriteDirection CalculateNextInput(ivec2 anIndex);
	bool GetNextPath(ivec2 anIndex);

private:
	std::array<int, MAXPATHSIZE_TOWN_NPC> m_MyInputSet;
	Vector2Float NewPosition;
	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;
	TileMap* m_MyTileMap;
	int* m_MyPath;
	int m_CurrentInput;
	bool m_IsFirstInput;
	bool m_PathingComplete;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	AI_States m_MyState;
};