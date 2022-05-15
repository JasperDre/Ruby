#pragma once

#include "Entities/Entity.h"

#include <array>

class AnimatedSprite;
class AStarPathFinder;
class ResourceManager;
class TileMap;

class TownBoy : public Entity
{
public:
	TownBoy(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture);
	~TownBoy() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
	void OnEvent(Event* anEvent) override {}
	void Move(SpriteDirection dir, float deltatime);
	void Pause() const;
	void Resume() const;
	void ResetPathFinder() const;

	void SetStop(bool StopNPC);

	[[nodiscard]] bool CheckForCollision(Vector2Float NPCNewPosition) const;
	[[nodiscard]] int* GetInputSet() const override;
	[[nodiscard]] bool GetNodeIsClearOnSpecial(int tx, int ty) const override;
	[[nodiscard]] int GetMyMapWidth() const override;
	[[nodiscard]] int GetMaxPathSize() const override;
	SpriteDirection CalculateNextInput(Vector2Int anIndex);
	bool GetNextPath(Vector2Int anIndex);

private:
	std::array<std::string, NUM_DIRECTIONS> AnimationKeys;
	std::array<int, MAXPATHSIZE_TOWN_NPC> m_MyInputSet;
	std::array<AnimatedSprite*, NUM_DIRECTIONS> m_Animations;
	Vector2Float NewPosition;
	Vector2Int m_MyNewDestination;
	Vector2Int m_MyIndex;
	TileMap* m_MyTileMap;
	int* m_MyPath;
	SpriteDirection myNewDirection;
	SpriteDirection myDirection;
	int m_CurrentInput;
	bool m_IsFirstInput;
	bool m_PathingComplete;
	bool m_Stop;
};
