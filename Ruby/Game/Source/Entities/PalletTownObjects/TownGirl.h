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

	[[nodiscard]] int RangeRandomIntAlg(int min, int max) const override;
	[[nodiscard]] bool CheckForCollision(Vector2Float NPCNewPosition) const;
	[[nodiscard]] int* GetInputSet() const override;
	[[nodiscard]] bool GetNodeIsClearOnSpecial(int tx, int ty) const override;
	[[nodiscard]] int GetMyMapWidth() const override;
	[[nodiscard]] int GetMaxPathSize() const override;
	SpriteDirection CalculateNextInput(ivec2 anIndex);
	bool GetNextPath(ivec2 anIndex);

private:
	std::array<std::string, NUM_DIRECTIONS> AnimationKeys;
	std::array<int, MAXPATHSIZE_TOWN_NPC> m_MyInputSet;
	std::array<AnimatedSprite*, NUM_DIRECTIONS> m_Animations;
	Vector2Float NewPosition;
	ivec2 m_MyNewDestination;
	ivec2 m_MyIndex;
	TileMap* m_MyTileMap;
	int* m_MyPath;
	int m_CurrentInput;
	SpriteDirection myDirection;
	SpriteDirection myNewDirection;
	bool m_Stop;
	bool m_IsFirstInput;
	bool m_PathingComplete;
};